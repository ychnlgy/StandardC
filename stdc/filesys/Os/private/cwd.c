#ifdef STDC_FILESYS_OS_PRIVATE

#include <assert.h>

static CStr cwd_Os(MemoryObject* mem) {
    char* buf = Memory.alloc(mem, sizeof(char)*BUFSIZE);
    // getcwd returns NULL if BUFSIZE is inadequate.
    assert(getcwd(buf, BUFSIZE) != NULL);
    return buf;
}

#endif
