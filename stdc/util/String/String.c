#include <string.h>
// strncpy, strlen, strcmp

#include <stdio.h>
// vsnprintf

#include <stdarg.h>
// va_list, va_start, va_end

#include <assert.h>

#include "String_private.h"

StringVtable String = {

    // Construction/destruction
    .new        = &new_String,
    .init       = &init_String,
    .del        = &del_String,
    
    // Object
    .equals     = &equals_String,
    .cstr       = &cstr_String,
    .copy       = &copy_String,
    
    // Hashable
    .hash       = &hash_String,
    
    // Numeric
    .add        = &add_String,

    // Container
    .size       = &size_String,
    .contains   = &contains_String,
    
    // Accessor
    .set        = &set_String,
    .getitem    = &getitem_String,
    .at         = &at_String,
    .slice      = &slice_String,
    .index      = &index_String,
    
    // String
    .eqCStr     = &eqCStr_String,
    .format     = &format_String,
    .startswith = &startswith_String,
    .endswith   = &endswith_String,
    .rstrip     = &rstrip_String,
    .lstrip     = &lstrip_String,
    .strip      = &strip_String,
    .split      = &split_String,
    .splitstr   = &splitstr_String,
    .replace    = &replace_String,
    .replacestr = &replacestr_String,
    .join       = &join_String,
    .joinstr    = &joinstr_String,
    .merge      = &merge_String

};

// Helpers

static bool compareCStr(bool a0, bool b0, CStr a, CStr b) {
    if (a0 & b0)
        return true;
    else if (a0 ^ b0)
        return false;
    else
        return strcmp(a, b) == 0;
}

static char* copyCStr(CStr src, int len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

static long getFormattedSize(StringObject* this, va_list args) {
    return vsnprintf(
        NULL,
        0,
        this->cstr,
        args
    );
}

static char* getFormattedCStr(StringObject* this, va_list args, long size) {
    char* cstr = malloc(sizeof(char)*(++size));
    vsnprintf(
        cstr,
        size,
        this->cstr,
        args
    );
    return cstr;
}

static bool isWithin(StringObject* this, long i) {
    return i < this->size && this->size != 0;
}

static long fitWithin(StringObject* this, long i) {
    return MOD(i, this->size);
}

static bool match(StringObject* this, StringObject* other, long i) {
    long k, p;
    for (
        k=i, p=0;
        p < other->size;
        k++, p++
    ) {
        if (this->cstr[k] != other->cstr[p])
            return false;
    }
    return true;
}

/*
 * White space characters (6) that Python checks for.
 */

static bool isWhiteSpace(char c) {
    switch (c) {
        case ' ':       // 1
        case '\t':      // 2
        case '\n':      // 3
        case '\r':      // 4
        case '\x0b':    // 5
        case '\x0c':    // 6
            return true;
        default:
            return false;
    }
}

static long countWhiteSpace(StringObject* this, long start, long step) {
    long i;
    long n = this->size + 1;
    for (i = start; --n > 0; i += step)
        if (!isWhiteSpace(this->cstr[i]))
            break;
    return i;
}

static ListObject* split(
    StringObject* this, 
    Ptr ptr, 
    long size, 
    bool (*fn)(StringObject*, StringObject*, long),
    MemoryObject* mem
) {
    ListObject* out = Memory.make(mem, List.new);
    long start = 0;
    long i;
    for (i=0; i<this->size-size+1; i++) {
        if (fn(this, ptr, i)) {
            List.push(out, slice_String(this, start, i, mem));
            start = i + size;
            i += size -1;
        }
    }
    if (start <= this->size)
        List.push(out, slice_String(this, start, this->size, mem));
    return out;
}

static bool matchChar(StringObject* this, StringObject* delim, long i) {
    return this->cstr[i] == *((char*) delim);
}

static long getStringSizeOfList(ListObject* liststr, long n) {
    long size = 0;
    long i;
    for (i=0; i<List.size(liststr); i++)
        size += size_String(List.getitem(liststr, i));
    size += (List.size(liststr) - 1)*n; // number of delimiter chars
    return size;
}

static char* getCStrFromList(ListObject* liststr, char* cstr, long n, long size) {
    char* out = malloc(sizeof(char) * (size+1));
    
    StringObject* item0 = List.getitem(liststr, 0);
    
    long i, j, k;
    for (i=0; i<item0->size; i++)
        out[i] = item0->cstr[i];
    for (k=1; k<List.size(liststr); k++) {
        for (j=0; j<n; j++)
            out[i++] = cstr[j];
        StringObject* item = List.getitem(liststr, k);
        for (j=0; j<item->size; j++)
            out[i++] = item->cstr[j];
    }
    out[i] = '\0';
    
    return out;
}

static StringObject* join(char* cstr, long n, ListObject* liststr, MemoryObject* mem) {
    StringObject* out = Memory.make(mem, &new_String);

    if (List.size(liststr) == 0)
        return out;
    
    long size = getStringSizeOfList(liststr, n);
    
    out->size = size;
    out->cstr = getCStrFromList(liststr, cstr, n, size);
    out->hash = calculateHash(out);
    return out;
}

/*
 * FNV-1a algorithm copied from:
 * http://isthe.com/chongo/tech/comp/fnv/
 * April 1, 2018.
 */

static long FNV_PRIME    = 16777619;
static long OFFSET_BASIS = 2166136261;

static long calculateHash(StringObject* this) {
    long hash = OFFSET_BASIS;
    long i;
    for (i=0; i<this->size; i++)
        hash = (this->cstr[i] ^ hash) * FNV_PRIME;
    return hash;
}

// Hashable

static long hash_String(StringObject* this) {
    return this->hash;
}

// Object

static void del_String(Ptr this) {
    free(((StringObject*) this)->cstr);
}

static Ptr new_String() {
    StringObject* this = new(sizeof(StringObject), &del_String);
    init_String(this);
    return this;
}

static void init_String(StringObject* this) {
    this->size = 0;
    this->cstr = NULL;
    this->hash = calculateHash(this);
}

static bool equals_String(StringObject* this, StringObject* other) {
    return compareCStr(this->size == 0, other->size == 0, this->cstr, other->cstr);
}

static CStr cstr_String(StringObject* this) {
    return this->cstr;
}

static StringObject* copy_String(StringObject* this, MemoryObject* mem) {
    StringObject* copy = Memory.make(mem, &new_String);
    copy->size = this->size;
    copy->cstr = copyCStr(this->cstr, this->size);
    copy->hash = this->hash;
    return copy;
}

// Numeric

static StringObject* add_String(StringObject* this, StringObject* other, MemoryObject* mem) {
    StringObject* nstr = Memory.make(mem, String.new);
    long size = this->size + other->size;
    if (size == 0)
        return nstr;
    nstr->size = size;
    nstr->cstr = malloc(sizeof(char)*(size+1));
    long i;
    for (i=0; i<this->size; i++)
        nstr->cstr[i] = this->cstr[i];
    for (i=0; i<other->size; i++)
        nstr->cstr[i+this->size] = other->cstr[i];
    nstr->cstr[size] = '\0';
    nstr->hash = calculateHash(nstr);
    return nstr;
}

// String

static bool eqCStr_String(StringObject* this, CStr cstr) {
    return compareCStr(this->size == 0, (cstr == NULL || *cstr == '\0'), this->cstr, cstr);
}

static StringObject* format_String(StringObject* this, MemoryObject* mem, ...) {
    va_list args;
    
    StringObject* s = Memory.make(mem, &new_String);
    
    va_start(args, mem);
    long size = getFormattedSize(this, args);
    va_end(args);
    
    // I don't know how to test this in a portable way.
    // if (size < 0) // encoding error
    //    return NULL;
    assert(size >= 0);
    
    s->size = size;
    
    va_start(args, mem);
    s->cstr = getFormattedCStr(this, args, size);
    s->hash = calculateHash(s);
    va_end(args);
    
    return s;
}

static bool startswith_String(StringObject* this, StringObject* substring) {
    if (substring->size > this->size)
        return false;
    return match(this, substring, 0);
}

static bool endswith_String(StringObject* this, StringObject* substring) {
    if (substring->size > this->size)
        return false;
    return match(this, substring, this->size-substring->size);
}

static StringObject* rstrip_String(StringObject* this, MemoryObject* mem) {
    long end = countWhiteSpace(this, this->size-1, -1);
    return slice_String(this, 0, end+1, mem);
}

static StringObject* lstrip_String(StringObject* this, MemoryObject* mem) {
    long start = countWhiteSpace(this, 0, 1);
    return slice_String(this, start, this->size, mem);
}

static StringObject* strip_String(StringObject* this, MemoryObject* mem) {
    long start = countWhiteSpace(this, 0, 1);
    if (start == this->size)
        return Memory.make(mem, &new_String);
    
    long end = countWhiteSpace(this, this->size-1, -1);
    return slice_String(this, start, end+1, mem);
}

static ListObject* split_String(StringObject* this, char delim, MemoryObject* mem) {
    return split(this, &delim, 1, &matchChar, mem);
}

static ListObject* splitstr_String(StringObject* this, StringObject* substr, MemoryObject* mem) {
    if (substr->size == 0)
        return NULL;
    else
        return split(this, substr, substr->size, &match, mem);
}

static StringObject* replace_String(StringObject* this, char oldc, char newc, MemoryObject* mem) {
    ListObject* parts = split_String(this, oldc, mem);
    return join_String(newc, parts, mem);
}

static StringObject* replacestr_String(StringObject* this, StringObject* oldSubstr, StringObject* newSubstr, MemoryObject* mem) {
    if (oldSubstr->size == 0)
        return NULL;
    ListObject* parts = splitstr_String(this, oldSubstr, mem);
    return joinstr_String(newSubstr, parts, mem);
}

static StringObject* join_String(char c, ListObject* liststr, MemoryObject* mem) {
    return join(&c, 1, liststr, mem);
}

static StringObject* joinstr_String(StringObject* this, ListObject* liststr, MemoryObject* mem) {
    return join(this->cstr, this->size, liststr, mem);
}

static StringObject* merge_String(ListObject* liststr, MemoryObject* mem) {
    return join(NULL, 0, liststr, mem);
}

// Container

static long size_String(StringObject* this) {
    return this->size;
}

static bool contains_String(StringObject* this, StringObject* substr) {
    return index_String(this, substr) > -1;
}

// Accessor

static void set_String(StringObject* this, CStr cstr) {
    free(this->cstr);
    this->size = cstr? strlen(cstr) : 0;
        
    if (this->size <= 0) {
        init_String(this);
    } else {
        this->cstr = copyCStr(cstr, this->size);
        this->hash = calculateHash(this);
    }
}

static char* getitem_String(StringObject* this, long i) {
    return this->cstr + i;
}

static char* at_String(StringObject* this, long i) {
    if (isWithin(this, i))
        return this->cstr + fitWithin(this, i);
    else
        return NULL;
}

static StringObject* slice_String(StringObject* this, long i, long j, MemoryObject* mem) {
    if (i > j || i < 0 || j > this->size)
        return NULL;
    
    StringObject* substr = Memory.make(mem, String.new);
    
    long size = j - i;
    if (size == 0)
        return substr;
    
    substr->size = size;
    substr->cstr = copyCStr(this->cstr+i, size);
    substr->hash = calculateHash(substr);
    return substr;
}

static long index_String(StringObject* this, StringObject* substr) {
    if (substr->size > this->size)
        return -1;
    long i;
    for (i=0; i < this->size-substr->size+1; i++)
        if (match(this, substr, i))
            return i;
    return -1;
}


