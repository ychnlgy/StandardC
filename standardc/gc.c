#include <stdlib.h> 
// malloc
#include <assert.h>

#include "gc.h"

void destroy_nothing(void* ptr){}

void* new(size_t bytes, Destructor destructor) {
    Destructor* ptr = malloc(sizeof(Destructor) + sizeof(int) + bytes);
    *ptr = destructor;
    int* intPtr = (int*) ++ptr;
    *intPtr = 1;
    return ++intPtr;
}

void incref(void* ptrptr) {
    ++(*((*((int**) ptrptr))-1));
}

void decref(void* ptrptr) {
    int ref = --(*((*((int**) ptrptr))-1));
    assert(ref >= 0);
    if (ref == 0) {
        del(ptrptr);
    }
}

void del(void* ptrptr) {
    void** vptrptr = (void**) ptrptr;
    int* intPtr = *vptrptr;
    Destructor* dstPtr = (Destructor*) --intPtr;
    Destructor destructor = *(--dstPtr);
    destructor(*vptrptr);
    free(dstPtr);
    *vptrptr = NULL;
}
