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

void incref(void* ptr) {
    ++(*(((int*) ptr)-1));
}

void decref(void* ptr) {
    int ref = --(*(((int*) ptr)-1));
    assert(ref >= 0);
    if (ref == 0) {
        del(ptr);
    }
}

void del(void* ptr) {
    int* intPtr = (int*) ptr;
    Destructor* dstPtr = (Destructor*) --intPtr;
    Destructor destructor = *(--dstPtr);
    destructor(ptr);
    free(dstPtr);
}
