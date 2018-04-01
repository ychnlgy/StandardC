# String

String class for the ease of string manipulation.

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

## String.set(_this_, _cstr_)
```c
void String.set(StringObject* this, CStr cstr);
```
Sets the value of this string to **cstr**. 
See [types](../stdc/util/types.h) for the declaration of ```CStr```.

## String.copy(_this_, _mem_)
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

## String.equals(_this_, _other_)
```c
bool String.equals(StringObject* this, StringObject* other);
```
Returns ```true``` if this string equals the other string.

## String.size(_this_)
```c
long String.size(StringObject* this);
```
Returns the number of characters in this string.

## String.cstr(_this_)
```c
CStr String.cstr(StringObject* this);
```
Returns the [CStr](../stdc/util/types.h) data of this string.

## String.format(_this_, MemoryObject*, ...)
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
