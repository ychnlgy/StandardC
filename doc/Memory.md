# Memory

Local memory scope to reduce the use of free/decref. 

A memory scope is responsible for any memory blocks it allocates or tracks, 
calling decref on their pointers upon destruction.

## Files
 * [stdc/memory/Memory/Memory.h](../stdc/memory/Memory/Memory.h)
 * [stdc/memory/Memory/Memory_protected.h](../stdc/memory/Memory/Memory_protected.h)
 * [stdc/memory/Memory/Memory.c](../stdc/memory/Memory/Memory.c)
 * [stdc/memory/Memory/Memory_test.c](../stdc/memory/Memory/Memory_test.c)

## General usage
```c
#include "stdc/lib.h"

void foo() {
  Memory* mem = new_Memory();
  
  // do stuff
  // ...
  
  decref(mem); // deletes the memory scope
               // all memory allocated or tracked by mem
               // will be decref'd.
}
```

## Memory.alloc(_this_, _typesize_)
```c
Ptr Memory.alloc(Memory* this, size_t typesize);
```
Allocates a block of memory of size **typesize**. 
The newly allocated memory now belongs to this memory scope
and will be decref'd when this memory scope is destroyed.

```c
#include "stdc/lib.h"

void bar() {
  Memory* mem = new_Memory();
  
  int* i1 = mem->_->alloc(mem, sizeof(int));
  int* i2 = mem->_->alloc(mem, sizeof(int));
  int* i3 = mem->_->alloc(mem, sizeof(int));
  
  incref(i3); // allow i3 to survive beyond the memory scope.
  decref(mem); // i1 and i2 will be free'd here.
  decref(i3); // i3 will be free'd here.
}
```

## Memory.make(_this_, _maker_)
```c
Ptr Memory.alloc(Memory* this, Maker maker);
```
Constructs the class specified by **maker**.
See [types](../stdc/util/types.h) for the declaration of ```Maker```.
The newly allocated memory now belongs to this memory scope
and will be decref'd when this memory scope is destroyed.
```c
#include "stdc/lib.h"

void hen() {
  Memory* mem = new_Memory();
  
  List* i1 = mem->_->make(mem, &new_List);
  List* i2 = mem->_->make(mem, &new_List);
  List* i3 = mem->_->make(mem, &new_List);
  
  incref(i3); // allow i3 to survive beyond the memory scope.
  decref(mem); // i1 and i2 will be free'd here.
  decref(i3); // i3 will be free'd here.
}
```

## Memory.track(_this_, _ptr_)
```c
void Memory.track(Memory* this, Ptr ptr);
```
Assign the **ptr** to this memory scope.
The memory block of **ptr** now belongs to this memory scope
and will be decref'd when this memory scope is destroyed.
```c
#include "stdc/lib.h"
#include <stdio.h>

List* createRange(int n) {
  Memory* mem = new_Memory();
  
  List* list = mem->_->make(mem, &new_List);
  
  int i;
  for (i=0; i<=n; i++) {
    int* ni = mem->_->alloc(mem, sizeof(int));
    *ni = i;
    list->_->push(list, ni);
  }
  
  incref(list); // return heap-allocated memory
  decref(mem);
  return list;
}

int sumRange(int n) {
  Memory* mem = new_Memory();
  
  List* range = createRange(n);
  mem->_->track(mem, range); // since range is heap-allocated memory
                          // it will need to be tracked by the
                          // current memory scope.
  
  int out = 0;
  int i;
  for (i=0; i<range->_->size(range); i++)
    out += *((int*) range->_->getitem(range, i));
  
  decref(mem); // range is free'd
  return out;
}

int main() {
  printf("%d\n", sumRange(100)); // prints 5050
  return 0;
}
```
