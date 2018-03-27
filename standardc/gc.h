#ifndef STANDARD_GC
#define STANDARD_GC

#include <stddef.h> 
// size_t

void destroy_nothing(void*);
typedef void (*Destructor)(void*);

void* new(size_t bytes, Destructor destructor);
void del(void* ptr);
void incref(void* ptr);
void decref(void* ptr);

#endif
