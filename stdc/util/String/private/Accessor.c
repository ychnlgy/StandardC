#ifdef STDC_UTIL_STRING_PRIVATE

#include <string.h>
// strlen

static void set_String(StringObject* this, CStr cstr) {
    free(this->cstr);
    this->size = strlen(cstr);
    this->cstr = copyCStr(cstr, this->size);
    this->hash = calculateHash(this);
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

static StringObject* slice_String(StringObject* this, MemoryObject* mem, long i, long j) {
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

#endif
