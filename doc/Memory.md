# Memory

Local memory scope to reduce the use of free/decref. 

A memory scope is responsible for any memory blocks it allocates or tracks, 
calling decref on their pointers upon destruction.

## Methods chart
| Interface | Method |
|-----------|--------|
| Object | ```Ptr Memory.new();``` |
| Memory | ```Ptr Memory.alloc(MemoryObject* this, size_t typesize);``` |
|        | ```Ptr Memory.make(MemoryObject* this, Maker maker);``` |
|        | ```void Memory.track(MemoryObject* this, Ptr ptr);``` |

## Files
 * [stdc/memory/Memory/Memory.h](../stdc/memory/Memory/Memory.h)
 * [stdc/memory/Memory/Memory_protected.h](../stdc/memory/Memory/Memory_protected.h)

## General usage
```c
#include "stdc/lib.h"

void foo() {
  MemoryObject* mem = Memory.new();
  
  // do stuff
  // ...
  
  decref(mem); // deletes the memory scope
               // all memory allocated or tracked by mem
               // will be decref'd.
}
```
## Object
#### Memory.new()
```c
Ptr Memory.new();
```
Returns a pointer to the newly allocated memory for the memory scope.

## Memory
#### Memory.alloc(_this_, _typesize_)
```c
Ptr Memory.alloc(MemoryObject* this, size_t typesize);
```
Allocates a block of memory of size **typesize**. 
The newly allocated memory now belongs to this memory scope
and will be decref'd when this memory scope is destroyed.

```c
#include "stdc/lib.h"

void bar() {
  MemoryObject* mem = Memory.new();
  
  int* i1 = Memory.alloc(mem, sizeof(int));
  int* i2 = Memory.alloc(mem, sizeof(int));
  int* i3 = Memory.alloc(mem, sizeof(int));
  
  incref(i3); // allow i3 to survive beyond the memory scope.
  decref(mem); // i1 and i2 will be free'd here.
  decref(i3); // i3 will be free'd here.
}
```

#### Memory.make(_this_, _maker_)
```c
Ptr Memory.alloc(MemoryObject* this, Maker maker);
```
Constructs the class specified by **maker**.
See [types](../stdc/util/types.h) for the declaration of ```Maker```.
The newly allocated memory now belongs to this memory scope
and will be decref'd when this memory scope is destroyed.
```c
#include "stdc/lib.h"

void hen() {
  MemoryObject* mem = Memory.new();
  
  ListObject* i1 = Memory.make(mem, &new_List);
  ListObject* i2 = Memory.make(mem, &new_List);
  ListObject* i3 = Memory.make(mem, &new_List);
  
  incref(i3); // allow i3 to survive beyond the memory scope.
  decref(mem); // i1 and i2 will be free'd here.
  decref(i3); // i3 will be free'd here.
}
```

#### Memory.track(_this_, _ptr_)
```c
void Memory.track(MemoryObject* this, Ptr ptr);
```
Assign the **ptr** to this memory scope.
The memory block of **ptr** now belongs to this memory scope
and will be decref'd when this memory scope is destroyed.
```c
#include "stdc/lib.h"
#include <stdio.h>

ListObject* createRange(int n) {
  MemoryObject* mem = Memory.new();
  
  ListObject* list = Memory.make(mem, &new_List);
  
  int i;
  for (i=0; i<=n; i++) {
    int* ni = Memory.alloc(mem, sizeof(int));
    *ni = i;
    List.push(list, ni);
  }
  
  incref(list); // return heap-allocated memory
  decref(mem);
  return list;
}

int sumRange(int n) {
  MemoryObject* mem = Memory.new();
  
  ListObject* range = createRange(n);
  Memory.track(mem, range); // since range is heap-allocated memory
                          // it will need to be tracked by the
                          // current memory scope.
  
  int out = 0;
  int i;
  for (i=0; i<List.size(range); i++)
    out += *((int*) List.getitem(range, i));
  
  decref(mem); // range is free'd
  return out;
}

int main() {
  printf("%d\n", sumRange(100)); // prints 5050
  return 0;
}
```
