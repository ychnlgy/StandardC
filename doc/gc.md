# Garbage Collection

A few functions for reference counting.

## Files

 * [stdc/memory/gc/gc.h](../stdc/memory/gc/gc.h)

 * [stdc/memory/gc/gc.c](../stdc/memory/gc/gc.c)

 * [stdc/memory/gc/gc_test.c](../stdc/memory/gc/gc_test.c)

## incref(_ptr_)
```c
int incref(Ptr ptr);
```
Increases the reference count of **ptr** by 1 and returns the new reference count. If **ptr** is ```NULL```, the reference count is not updated and the returned value is ```-1```. The input **ptr** must have been allocated by ```new```. This function is typically used when returning a dynamically allocated object at the end of a function:
```c
// continuing from the Foo example...

Foo* fooify() {
  MemoryObject* mem = Memory.new();
  
  Foo* foo = Memory.make(mem, &new_Foo);
  *foo->i = 34;
  
  incref(foo); // increase its reference count to prevent
               // its destruction with the memory.
  decref(mem);
  return foo; // if you forgot the previous incref, 
              // foo would be freed memory here - dangerous!
}
```
You can see how ```incref``` is used in [List.c](../stdc/util/List/List.c) (ctrl-f to find its usage).

## decref(_ptr_)
```c
int decref(Ptr ptr);
```
Decreases the reference count of **ptr** by 1 and returns the new reference count. If **ptr** is ```NULL```, the reference count is not updated and the returned value is ```-1```. The input **ptr** must have been allocated by ```new```. This function is typically used to attempt to free its memory - which is successfully freed when its reference count is decreased to 0.

## new(_typesize_, _destructor_)
 ```c
 Ptr new(size_t typesize, Destructor destructor);
 ```
Allocates a block of memory with size of **typesize** plus enough additional memory to store the reference count and destruction function pointer. Reference count is set to 1. 

See [types](../stdc/util/types.h) for ```Ptr``` and ```Destructor``` declarations.

**Note: you should not use this function often as [Memory](Memory.md) is a much better option for dynamically allocating objects on heap memory.** This function is typically used in class instantiation code rather than program coding.
```c
int main() {
  // rather than doing:
  int* i1 = new(sizeof(int), NULL);
  char* i2 = new(sizeof(char), NULL);
  int* i3 = new(sizeof(int), NULL);
  decref(i1);
  decref(i2);
  decref(i3);
  
  // do:
  MemoryObject* mem = Memory.new();
  int* i4 = Memory.alloc(mem, sizeof(int));
  char* i5 = Memory.alloc(mem, sizeof(char));
  int* i6 = Memory.alloc(mem, sizeof(int));
  decref(mem); // less opportunity to forget to free memory.
}
```

Parameter **destructor** is a function pointer to the destructor function for the pointer.
For primitive types like ```int```, ```float```, ```char``` and structs that do not require malloc,
set **destructor** = ```NULL```. 
```c
#include "stdc/lib.h"

int main() {
  int* i = new(sizeof(int), NULL);
  
  // do stuff with i
  // ...
  
  decref(i);
  return 0;
}
```

On the other hand, destructors work well for the following struct:
```c
#include "stdc/lib.h"

typedef struct Foo {
  int* i;
} Foo;

void del_Foo(Ptr this) {
  free(((Foo*) this)->i);
  // Notice we do not call free(this).
  // This is because decref will do it.
  // If an object's refcount is 0, 
  // decref first calls the object's destructor
  // and then frees the object.
}

Ptr new_Foo() {
  Foo* this = new(sizeof(Foo), &del_Foo);
  // for structs that do not require additional malloc
  // and therefore do not require destruction,
  // you can simply use NULL for the destructor:
  // Bar* this = new(sizeof(Bar), NULL);
  
  this->i = malloc(sizeof(int));
  return this;
}
```
The philosophy here is to store destruction information in the construction of complex objects. While it is easy to know when new objects are needed, it is hard to remember the fields of the object to free.
```c
// continued from above...

int main() {
  // You could do this:
  Foo* foo = new_Foo();
  decref(foo); // foo and foo->i are completely freed.
  
  // ...but it is better to do this:
  MemoryObject* mem = Memory.new();
  Foo* foo2 = Memory.make(mem, &new_Foo);
  
  // do stuff with foo2
  // ...
  
  decref(mem); // destruction of memory will destroy foo2
               // as well as any other allocated/tracked
               // memory for you.
  
  return 0;
}
```
