#ifdef STDC_FILESYS_OS_PRIVATE

#include <assert.h>

static char* cwd_Os(MemoryObject* mem) {
    char* buf;
    if (mem)
        buf = Memory.alloc(mem, sizeof(char)*BUFSIZE);
    else
        buf = malloc(sizeof(char) * BUFSIZE);
    // getcwd returns NULL if BUFSIZE is inadequate.
    assert(getcwd(buf, BUFSIZE) != NULL);
    return buf;
}

#endif
