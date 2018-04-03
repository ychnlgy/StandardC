# List

Dynamically resizable array-list.

All elements of the list are pointers to the original data.

## Methods chart
| Interface | Method |
|-----------|--------|
| Object | ```Ptr List.new();``` |
|        | ```bool List.equals(ListObject* this, ListObject* other);``` |
|        | ```ListObject* List.copy(ListObject* this, MemoryObject* mem);``` |
| Container | ```long List.size(ListObject* this);``` |
|           | ```void List.clear(ListObject* this);``` |
|           | ```bool List.isEmpty(ListObject* this);``` |
| Stack | ```void List.push(ListObject* this, Ptr ptr);``` |
|       | ```void List.pushes(ListObject* this, long n, ...);``` |
|       | ```Ptr List.pop(ListObject* this, MemoryObject* mem);``` |
|       | ```Ptr List.back(ListObject* this);``` |
|       | ```void List.extend(ListObject* this, ListObject* other);``` |
| Accessor | ```Ptr List.getitem(ListObject* this, long i);``` |
|          | ```void List.setitem(ListObject* this, long i, Ptr ptr);``` |
|          | ```Ptr List.at(ListObject* this, long i);``` |
|          | ```void List.set(ListObject* this, long i, Ptr ptr);``` |
|          | ```ListObject* List.slice(ListObject* this, MemoryObject* mem, long i, long j);``` |
| List | ```ListObject* List.concat(ListObject* this, ListObject* other, MemoryObject* mem);``` |

## Files
 * [stdc/util/List/List.h](../stdc/util/List/List.h)
 * [stdc/util/List/protected.h](../stdc/util/List/protected.h)

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
  
  int* k1 = List.pop(list, mem);

  int m = List.size(list);
  // m == 1
  
  decref(mem); // all memory is free'd - no leaks!
  return 0;
}
```
## Object

#### List.new()
```c
Ptr List.new();
```
Returns a pointer to the newly allocated memory for a ```ListObject```.

#### List.equals(_this_, _other_)
```c
bool List.equals(ListObject* this, ListObject* other);
```
Returns true if the two lists have the same length and 
corresponding elements are equal.

#### List.copy(_this_, _mem_)
```c
ListObject* List.copy(ListObject* this, MemoryObject* mem);
```
Makes a copy of **this** list on heap memory.

## Container

#### List.size(_this_)
```c
long List.size(ListObject* this);
```
Returns the number of elements in the list.

#### List.clear(_this_)
```c
void List.clear(ListObject* this);
```
Removes all elements in the list.

#### List.isEmpty(_this_)
```c
bool List.isEmpty(ListObject* this);
```
Returns true if **this** list is empty.

## Stack

#### List.push(_this_, _ptr_)
```c
void List.push(ListObject* this, Ptr ptr);
```
Appends the **ptr** to the back of the list, resizing if needed. 

The **ptr** must be either ```NULL``` or allocated by [```new```](gc.md) at some point.
Ideally, **ptr** is allocated by the [memory scope](Memory.md).

#### List.pushes(_this_, _n_, ...)
```c
void List.pushes(ListObject* this, long n, ...);
```
Calls ```List.push``` on the **n** pointers passed as parameters.
```c
#include "stdc/lib.h"
#include <assert.h>

int main() {
  MemoryObject* mem = Memory.new();
  
  ListObject* list = Memory.make(mem, List.new);
  
  int* i1 = Memory.alloc(mem, sizeof(int));
  int* i2 = Memory.alloc(mem, sizeof(int));
  int* i3 = Memory.alloc(mem, sizeof(int));
  
  *i1 = 20;
  *i2 = 40;
  *i3 = 60;
  
  List.pushes(list, 3, i1, i2, i3);
  // The list is now  [20, 40, 60]
  
  int* j1 = List.at(list, 0);
  assert(*j1 == *i1);
  
  decref(mem);
}
```

#### List.pop(_this_, _mem_)
```c
Ptr List.pop(ListObject* this, MemoryObject* mem);
```
Removes and returns the last element of the list. 

#### List.back(_this_)
```c
Ptr List.back(ListObject* this);
```
Returns the pointer to the last element in the list.

#### List.extend(_this_, _otherlist_)
```c
void List.extend(ListObject* this, ListObject* otherlist);
```
Appends the other list to the end of this list.

## Accessor

#### List.getitem(_this_, _i_)
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
#### List.setitem(_this_, _i_, _ptr_)
```c
void List.setitem(ListObject* this, long i, Ptr ptr);
```
Replaces the pointer at index **i** with **ptr**.
It does not check if **i** is within the list boundaries,
so this method should only be used in loops for safety.

The **ptr** must be either ```NULL``` or allocated by [```new```](gc.md) at some point.
Ideally, **ptr** is allocated by the [memory scope](Memory.md).

#### List.at(_this_, _i_)
```c
Ptr List.at(ListObject* this, long i);
```
Returns the pointer to the element at position **i**.
This is the safer alternative to ```List.getitem``` because
it will return ```NULL``` if **i** is outside list boundaries.

It also supports negative indexing: 
```i = -1``` means the back of the list,
```i = -2``` means the second last item, etc.

#### List.set(_this_, _i_, _ptr_)
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

#### List.slice(_this_, _mem_, _i_, _j_)
```c
ListObject* List.slice(ListObject* this, MemoryObject* mem, long i, long j);
```
Creates a new list consisting of elements **i** up to but not including **j**.
The returned ```ListObject*``` is ```NULL``` if **j** is less than **i** or
if any of the two indices are outside the bounds of the list.

```c
#include "stdc/lib.h"

int main() {
  MemoryObject* mem = Memory.new();
  
  int* i1 = Memory.alloc(mem, sizeof(int));
  int* i2 = Memory.alloc(mem, sizeof(int));
  int* i3 = Memory.alloc(mem, sizeof(int));
  int* i4 = Memory.alloc(mem, sizeof(int));
  *i1 = 20;
  *i2 = 30;
  *i3 = 40;
  *i4 = 50;
  
  ListObject list = Memory.make(mem, List.new);
  List.pushes(list, 4, i1, i2, i3, i4);
  // list is [20, 30, 40, 50]
  
  ListObject* sublist1 = List.slice(list, mem, 1, 3);
  // sublist1 is [30, 40]
  
  ListObject* sublist2 = List.slice(list, mem, List.size(list), 0);
  // sublist2 is NULL
  
  ListObject* sublist3 = List.slice(list, mem, 0, List.size(list));
  // sublist3 is a copy of list
  
  decref(mem);
}
```

## List
#### List.concat(_this_, _otherlist_, _mem_)
```c
ListObject* List.concat(ListObject* this, ListObject* otherlist, MemoryObject* mem);
```
Makes a new list consisting of elements of this list followed by the elements of the other list.
```c
#include "stdc/lib.h"

int main() {
    MemoryObject* mem = Memory.new();
    
    int* i1 = Memory.alloc(mem, sizeof(int));
    int* i2 = Memory.alloc(mem, sizeof(int));
    int* i3 = Memory.alloc(mem, sizeof(int));
    int* i4 = Memory.alloc(mem, sizeof(int));
    
    *i1 = 1;
    *i2 = 2;
    *i3 = 3;
    *i4 = 4;
    
    ListObject* l1 = Memory.make(mem, List.new);
    ListObject* l2 = Memory.make(mem, List.new);
    
    List.push(l1, i1);
    List.push(l1, i2);
    // l1 contains [1, 2]
    
    List.push(l2, i3);
    List.push(l2, i4);
    // l2 contains [3, 4]
    
    ListObject* l3 = List.concat(l1, l2, mem);
    // l3 contains [1, 2, 3, 4]

    decref(mem); // all memory is free'd
}
```
