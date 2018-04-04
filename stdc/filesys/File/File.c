#include <stdio.h>

#include "File.h"
#include "protected.h"

static long BUFSIZE = 1024;

static Ptr new_File();
static void init_File(FileObject*);
static void del_File(Ptr);

static void name_File(FileObject*, CStr);
static void namestr_File(FileObject*, StringObject*);
static void namepath_File(FileObject*, PathObject*);

static bool exists_File(FileObject*);
static bool readable_File(FileObject*);
static bool writable_File(FileObject*);

static void write_File(FileObject*, long, CStr);
static void writestr_File(FileObject*, StringObject*);
static StringObject* read_File(FileObject*, MemoryObject*);
static long flush_File(FileObject*);

FileVtable File = {
    .new = &new_File,
    .init = &init_File,
    .del = &del_File,
    
    .name = &name_File,
    .namestr = &namestr_File,
    .namepath = &namepath_File,
    
    .exists = &exists_File,
    .readable = &readable_File,
    .writable = &writable_File,
    
    .write = &write_File,
    .writestr = &writestr_File,
    .read = &read_File,
    .flush = &flush_File
};

typedef struct {
    long n;
    char* d;
} _FileData;

static Ptr new_File() {
    FileObject* this = new(sizeof(FileObject), &del_File);
    init_File(this);
    return this;
}

static void init_File(FileObject* this) {
    this->path = Path.new();
    this->list = List.new();
}

static void del_File(Ptr ptr) {
    FileObject* this = ptr;
    decref(this->path);
    decref(this->list);
}

static void name_File(FileObject* this, CStr name) {
    Path.setrel(this->path, name);
}

static void namestr_File(FileObject* this, StringObject* name) {
    Path.setrelstr(this->path, name);
}

static void namepath_File(FileObject* this, PathObject* path) {
    decref(this->path);
    this->path = path;
    incref(path);
}

static bool exists_File(FileObject* this) {
    return Path.isfile(this->path);
}

static bool readable_File(FileObject* this) {
    return Os.readable(Path.cstr(this->path));
}

static bool writable_File(FileObject* this) {
    return Os.writable(Path.cstr(this->path));
}

static void del_FileData(Ptr ptr) {
    free(((_FileData*) ptr)->d);
}

static _FileData* new_FileData(long n) {
    _FileData* d = new(sizeof(_FileData), &del_FileData);
    d->n = n;
    d->d = malloc(n);
    return d;
}

static _FileData* allocFileData(long n, CStr data) {
    _FileData* s = new_FileData(n);
    long i;
    for (i=0; i<n; i++)
        s->d[i] = data[i];
    return s;
}

static void write_File(FileObject* this, long n, CStr data) {
    if (n > 0 && data != NULL) {
        _FileData* fd = allocFileData(n, data);
        List.push(this->list, fd);
        decref(fd);
    }
}

static void writestr_File(FileObject* this, StringObject* data) {
    write_File(this, String.size(data), String.cstr(data));
}

/*
 * Adapted from:
 * https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
 * "C library function - fread()"
 */

static StringObject* read_File(FileObject* this, MemoryObject* mem) {
    // NOTE: String.merge is not used for this algorithm
    // because there may be early '\0' in the file.
    CStr name = Path.cstr(this->path);
    if (name == NULL)
        return NULL;
    
    FILE* f = fopen(name, "rb");
    if (f == NULL)
        return NULL;
    
    ListObject* datalist = List.new();
    char buf[BUFSIZE];
    fseek(f, 0, SEEK_SET);
    long totalchars = 0;
    long numchars = fread(buf, 1, BUFSIZE, f);
    while (numchars == BUFSIZE) {
        _FileData* fd = allocFileData(BUFSIZE, buf);
        List.push(datalist, fd);
        decref(fd);
        totalchars += numchars;
        numchars = fread(buf, 1, BUFSIZE, f);
    }
    fclose(f);
    
    if (numchars > 0) {
        _FileData* fd = allocFileData(numchars, buf);
        List.push(datalist, fd);
        decref(fd);
        totalchars += numchars;
    }
    
    char goodBuf[totalchars+1];
    long i, j;
    long k = 0;
    for (i=0; i<List.size(datalist); i++) {
        _FileData* fd = List.getitem(datalist, i);
        for (j=0; j<fd->n; j++)
            goodBuf[k++] = fd->d[j];
    }
    decref(datalist);
    goodBuf[totalchars] = '\0';
    
    StringObject* out = Memory.make(mem, String.new);
    String.set(out, goodBuf);
    
    return out;
}

/*
 * Adapted from:
 * https://stackoverflow.com/questions/11573974
 * "Write to .txt file?"
 */

static long flush_File(FileObject* this) {
    CStr name = Path.cstr(this->path);
    if (name == NULL)
        return -1;
    
    FILE* f = fopen(Path.cstr(this->path), "wb");
    if (f == NULL)
        return -1;
    long total = 0;
    long i;
    for (i=0; i<List.size(this->list); i++) {
        _FileData* d = List.getitem(this->list, i);
        fwrite(d->d, 1, d->n, f);
        total += d->n;
    }
    fclose(f);
    List.clear(this->list);
    return total;
}
