# String

String class for the ease of string manipulation.

## Methods chart
| Interface | Method |
|-----------|--------|
| Object | ```Ptr String.new();``` |
|        | ```bool String.equals(StringObject* this, StringObject* other);``` |
|        | ```CStr String.cstr(StringObject* this);``` |
|        | ```StringObject* String.copy(StringObject* this, MemoryObject* mem);``` |
| Hashable | ```long String.hash(StringObject* this);``` |
| Container | ```long String.size(StringObject* this);``` |
|           | ```bool String.contains(StringObject* this, StringObject* substring);``` |
| Accessor | ```char* String.getitem(StringObject* this, long i);``` |
|          | ```char* String.at(StringObject* this, long i);``` |
|          | ```void String.set(StringObject* this, CStr cstr);``` |
|          | ```StringObject* String.slice(StringObject* this, MemoryObject* mem, long i, long j);``` |
| String | ```StringObject* String.format(StringObject* this, MemoryObject* mem, ...);``` |
|        | ```StringObject* String.rstrip(StringObject* this, MemoryObject* mem);``` |
|        | ```StringObject* String.lstrip(StringObject* this, MemoryObject* mem);``` |
|        | ```StringObject* String.strip(StringObject* this, MemoryObject* mem);``` |
|        | ```List* String.split(StringObject* this, char delimiter, MemoryObject* mem);``` |
|        | ```List* String.splitstr(StringObject* this, StringObject* delimiter, MemoryObject* mem);``` |
|        | ```bool String.beginswith(StringObject* this, StringObject* substring);``` |
|        | ```bool String.endswith(StringObject* this, StringObject* substring);``` |

## Files
 * [stdc/util/String/String.h](../stdc/util/String/String.h)
 * [stdc/util/String/String_protected.h](../stdc/util/String/String_protected.h)

## Demonstration
```c
#include "stdc/lib.h"
#include <stdio.h>
#include <assert.h>

int main() {
    MemoryObject* mem = Memory.new();
    
    StringObject* s1 = Memory.make(mem, String.new);
    String.set(s1, "Hello world!");
    
    StringObject* s2 = Memory.make(mem, String.new);
    String.set(s2, "Carrot");
    
    StringObject* s3 = String.copy(s1, mem);
    
    // s1 is equal to s3 but not s2.
    assert(String.equals(s1, s3));
    assert(!String.equals(s1, s2));
    assert(!String.equals(s2, s3));
    
    printf("The length of \"%s\" is: %d\n", String.cstr(s1), String.size(s1));
    
    decref(mem);
    return 0;
}
```
## Object
#### String.new()
```c
Ptr String.new();
```
Returns a pointer to the newly allocated memory for a string.

#### String.equals(_this_, _other_)
```c
bool String.equals(StringObject* this, StringObject* other);
```
Returns ```true``` if this string equals the other string.

#### String.cstr(_this_)
```c
CStr String.cstr(StringObject* this);
```
Returns the [CStr](../stdc/util/types.h) data of this string.

#### String.copy(_this_, _mem_)
```c
StringObject* String.copy(StringObject* this, MemoryObject* mem);
```
Allocates a copy of this string on heap memory and returns the pointer to it.
```c
#include "stdc/lib.h"

int main() {
  MemoryObject* mem = Memory.new();
  
  StringObject* s1 = Memory.make(mem, String.new);
  StringObject* s2 = String.copy(s1, mem);
  
  decref(mem); // no memory leaks.
}
```

## Hashable
#### String.hash(_this_)
TODO

## Container
#### String.size(_this_)
```c
long String.size(StringObject* this);
```
Returns the number of characters in this string.

#### String.contains(_this_, _other_)
TODO

## Accessor
#### String.getitem(_this_, _i_)
TODO

#### String.at(_this_, _i_)
TODO

#### String.set(_this_, _cstr_)
```c
void String.set(StringObject* this, CStr cstr);
```
Sets the value of this string to **cstr**. 
See [types](../stdc/util/types.h) for the declaration of ```CStr```.

#### String.slice(_this_, _mem_, _i_, _j_)
TODO

## String
#### String.format(_this_, _mem_, ...)
```c
StringObject* String.format(StringObject* this, MemoryObject* mem, ...);
```
Formats this string with variable arguments and returns a new string. 

```c
#include "stdc/lib.h"
#include <stdio.h>

int main() {
    MemoryObject* mem = Memory.new();
    
    StringObject* s1 = Memory.make(mem, String.new);
    String.set(s1, "%d eggs a %s. Have a good day, %s!\n");
    
    StringObject* s2 = String.format(s1, mem, 12, "dozen", "mister");
    
    printf("%s", String.cstr(s2)); 
    // prints: "12 eggs a dozen. Have a good day, mister!\n"
    
    decref(mem);
}
```
#### String.rstrip(_this_, _mem_)
TODO

#### String.lstrip(_this_, _mem_)
TODO

#### String.strip(_this_, _mem_)
TODO

#### String.split(_this_, _c_, _mem_)
TODO

#### String.splitstr(_this_, _substring_, _mem_)
TODO

#### String.beginswith(_this_, _substring_)
TODO

#### String.endswith(_this_, _substring_)
TODO
