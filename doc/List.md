# List

Dynamically resizable array-list.

All elements of the list are pointers to the original data.

## Files
 * [stdc/util/List/List.h](../stdc/util/List/List.h)
 * [stdc/util/List/List_protected.h](../stdc/util/List/List_protected.h)
 * [stdc/util/List/List.c](../stdc/util/List/List.c)
 * [stdc/util/List/List_test.c](../stdc/util/List/List_test.c)

## Demonstration
```c
#include "stdc/lib.h"

int main() {
  MemoryObject* mem = Memory.new();
  
  ListObject* list = Memory.make(mem, List.new);
  
  int* i1 = Memory.alloc(mem, sizeof(int));
  int* i2 = Memory.alloc(mem, sizeof(int));
  *i1 = 20;
  *i2 = 40;
  
  List.push(list, i1);
  List.push(list, i2);
  // list is now [20, 40]
  
  List.set(list, 0, i2);
  // list is now [40, 40]
  
  List.set(list, -1, i1);
  // list is now [40, 20]
  
  *i1 = 60;
  // list is now [40, 60]
  
  int* j1 = List.at(list, -1);
  // *j1 == *i1 == 60
  
  int n = List.size(list);
  // n == 2
  
  int* k1 = List.pop(list);
  Memory.track(mem, k1); // IMPORTANT:
                       // List.pop does not decref popped items.
                       // Since the block of memory pointed to
                       // by k1 is no longer referenced by the list,
                       // it needs to be tracked by the memory scope.

  int m = List.size(list);
  // m == 1
  
  decref(mem); // all memory is free'd - no leaks!
  return 0;
}
```

## List.size(_this_)
```c
long List.size(ListObject* this);
```
Returns the number of elements in the list.

## List.getitem(_this_, _i_)
```c
Ptr List.getitem(ListObject* this, long i);
```
Returns the pointer to the element at position **i**.
It does not check if **i** is within the list boundaries,
so this method should only be used in loops for safety.

```c
#include "stdc/lib.h"

void fn(char* c) {
  // do something
}

int main() {
  MemoryObject* mem = Memory.new();
  
  ListObject* list = Memory.make(mem, List.new);
  
  char* c1 = Memory.alloc(mem, sizeof(char));
  char* c2 = Memory.alloc(mem, sizeof(char));
  
  int i;
  for (i=0; i<List.size(list); i++)
    fn(List.getitem(list, i));
  
  decref(mem);
}
```

## List.setitem(_this_, _i_, _ptr_)
```c
void List.setitem(ListObject* this, long i, Ptr ptr);
```
Replaces the pointer at index **i** with **ptr**.
It does not check if **i** is within the list boundaries,
so this method should only be used in loops for safety.

The **ptr** must be either ```NULL``` or allocated by [```new```](gc.md) at some point.
Ideally, **ptr** is allocated by the [memory scope](Memory.md).

Automatically incref's **ptr** if it is not ```NULL``` and 
decref's the original pointer at that index if it is not ```NULL```.

## List.at(_this_, _i_)
```c
Ptr List.at(ListObject* this, long i);
```
Returns the pointer to the element at position **i**.
This is the safer alternative to ```List.getitem``` because
it will return ```NULL``` if **i** is outside list boundaries.

It also supports negative indexing: 
```i = -1``` means the back of the list,
```i = -2``` means the second last item, etc.


## List.set(_this_, _i_, _ptr_)
```c
bool List.set(ListObject* this, long i, Ptr ptr);
```
Replaces the pointer at index **i** with **ptr**.
This is the safer alternative to ```List.setitem``` because
it will do nothing and return ```false``` if **i** is outside list boundaries.

It also supports negative indexing: 
```i = -1``` means the back of the list,
```i = -2``` means the second last item, etc.

The **ptr** must be either ```NULL``` or allocated by [```new```](gc.md) at some point.
Ideally, **ptr** is allocated by the [memory scope](Memory.md).

Automatically incref's **ptr** if it is not ```NULL``` and 
decref's the original pointer at that index if it is not ```NULL```.

## List.push(_this_, _ptr_)
```c
void List.push(ListObject* this, Ptr ptr);
```
Appends the **ptr** to the back of the list, resizing if needed. 

The **ptr** must be either ```NULL``` or allocated by [```new```](gc.md) at some point.
Ideally, **ptr** is allocated by the [memory scope](Memory.md).

Automatically incref's **ptr**.

## List.pop(_this_)
```c
Ptr List.pop(ListObject* this);
```
Removes and returns the last element of the list. 

**The returned pointer is not decref'd so it needs to be tracked by the local memory scope.**

This is intentional. Consider the case when the list contains the very last reference to an element.
If it decrefs every element it pops, then it will return the pointer to free'd memory in this case.
```c
// Here is an example demonstrating the problem
// if List.pop decrefs the element pointer.

#include "stdc/lib.h"

ListObject* foo() {
  MemoryObject* mem = Memory.new();
  
  ListObject* list = Memory.make(mem, List.new);
  
  int* i = Memory.alloc(mem, sizeof(int));
  // i has refcount 1
  
  List.push(list, i);
  // i now has refcount 2
  
  incref(list);
  // incref on the list does not incref its elements.
  // therefore i still has refcount 2
  
  decref(mem);
  // i now has refcount 1
  
  return list;
}

int main() {
  MemoryObject* mem = Memory.new();
  
  ListObject* list = foo();
  Memory.track(mem, list);
  
  int* j = List.pop(list);  // if List.pop were to decref the pointers
                             // it pops, j will point to free'd memory,
  Memory.track(mem, j);
  
  decref(mem); // all blocks of memory in this scope are free'd
  return 0;
}
```

