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
| Numeric | ```StringObject* String.add(StringObject* this, StringObject* other, MemoryObject* mem);``` |
| Container | ```long String.size(StringObject* this);``` |
|           | ```bool String.contains(StringObject* this, StringObject* substring);``` |
| Accessor | ```char* String.getitem(StringObject* this, long i);``` |
|          | ```char* String.at(StringObject* this, long i);``` |
|          | ```void String.set(StringObject* this, CStr cstr);``` |
|          | ```StringObject* String.slice(StringObject* this, long i, long j, MemoryObject* mem);``` |
|          | ```long String.index(StringObject* this, StringObject* substring);``` |
| String | ```StringObject* String.format(StringObject* this, MemoryObject* mem, ...);``` |
|        | ```StringObject* String.rstrip(StringObject* this, MemoryObject* mem);``` |
|        | ```StringObject* String.lstrip(StringObject* this, MemoryObject* mem);``` |
|        | ```StringObject* String.strip(StringObject* this, MemoryObject* mem);``` |
|        | ```List* String.split(StringObject* this, char delimiter, MemoryObject* mem);``` |
|        | ```List* String.splitstr(StringObject* this, StringObject* delimiter, MemoryObject* mem);``` |
|        | ```bool String.startswith(StringObject* this, StringObject* substring);``` |
|        | ```bool String.endswith(StringObject* this, StringObject* substring);``` |
|        | ```StringObject* String.replace(StringObject* this, char oldc, char newc, MemoryObject* mem);``` |
|        | ```StringObject* String.replacestr(StringObject* this, StringObject* oldSubstr, StringObject* newSubstr, MemoryObject* mem);``` |
|        | ```StringObject* String.join(StringObject* this, ListObject* liststr, MemoryObject* mem);``` |

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
Returns ```true``` if **this** string equals the **other** string.

#### String.cstr(_this_)
```c
CStr String.cstr(StringObject* this);
```
Returns the [CStr](../stdc/util/types.h) data of **this** string.

#### String.copy(_this_, _mem_)
```c
StringObject* String.copy(StringObject* this, MemoryObject* mem);
```
Allocates a copy of **this** string on heap memory and returns the pointer to it.
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
```c
long String.hash(StringObject* this);
```
Returns the hash number of **this** string.

## Numeric
#### String.add(_this_, _other_, _mem_)
```c
StringObject* String.add(StringObject* this, StringObject* other, MemoryObject* mem);
```
Appends the **other** string to the end of **this** string. 

Returns the pointer to the memory of the new string.

## Container
#### String.size(_this_)
```c
long String.size(StringObject* this);
```
Returns the number of characters in **this** string.

#### String.contains(_this_, _substring_)
```c
bool String.contains(StringObject* this, StringObject* substring);
```
Returns true if **substring** can be located within **this** string.

## Accessor
#### String.getitem(_this_, _i_)
```c
char* String.getitem(StringObject* this, long i);
```
Returns the pointer to the character at index **i** for **this** string.

Does not check for boundaries, so this method should only be used within loops for safety.

#### String.at(_this_, _i_)
```c
char* String.at(StringObject* this, long i);
```
Returns the pointer to the character at index **i** for **this** string.

It functions as a safer version of ```String.getitem``` because it returns ``NULL`` if **i** is out of string bounds.

Accepts negative indexing (i.e. ```i = -1``` returns the character at the back of the string).

#### String.set(_this_, _cstr_)
```c
void String.set(StringObject* this, CStr cstr);
```
Sets the value of **this** string to **cstr**. 
See [types](../stdc/util/types.h) for the declaration of ```CStr```.

#### String.slice(_this_, _i_, _j_, _mem_)
```c
StringObject* String.slice(StringObject* this, long i, long j, MemoryObject* mem);
```
Returns the substring consisting of characters
at index **i** up to but not including **j** in **this** string.

If **j** is less than **i**
or **i** is negative or **j** exceeds the length of the string,
the method will return ```NULL```.

If **i** equals **j**, the method will return an empty string.

#### String.index(_this_, _substring_)
```c
long String.index(StringObject* this, StringObject* substring);
```
Returns the index at which **substring** appears in **this** string. 

If **substring** is not found in **this** string, ```-1``` is returned.

## String
#### String.format(_this_, _mem_, ...)
```c
StringObject* String.format(StringObject* this, MemoryObject* mem, ...);
```
Formats **this** string with variable arguments and returns a new string. 

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
```c
StringObject* String.rstrip(StringObject* this, MemoryObject* mem);
```
Returns a new string with whitespace characters removed from the right of **this** string.

#### String.lstrip(_this_, _mem_)
```c
StringObject* String.lstrip(StringObject* this, MemoryObject* mem);
```
Returns a new string with whitespace characters removed from the left of **this** string.

#### String.strip(_this_, _mem_)
```c
StringObject* String.strip(StringObject* this, MemoryObject* mem);
```
Returns a new string with whitespace characters removed from both ends of **this** string.

#### String.split(_this_, _delimiter_, _mem_)
```c
ListObject* String.split(StringObject* this, char delimiter, MemoryObject* mem);
```
Returns a list of substrings that result when you split **this** string by the **delimiter**.

#### String.splitstr(_this_, _substring_, _mem_)
```c
ListObject* String.splitstr(StringObject* this, StringObject* substring, MemoryObject* mem);
```
Returns a list of substrings that result when you split **this** string by the **substring**.

#### String.startswith(_this_, _substring_)
```c
bool String.startswith(StringObject* this, StringObject* substring);
```
Returns true if **this** string starts with **substring**.

#### String.endswith(_this_, _substring_)
```c
bool String.endswith(StringObject* this, StringObject* substring);
```
Returns true if **this** string ends with **substring**.

#### String.replace(_this_, _oldc_, _newc_, _mem_)
```c
StringObject* String.replace(StringObject* this, char oldc, char newc, MemoryObject* mem);
```
Makes a new string with character **oldc** of **this** string replaced with **newc**.

#### String.replacestr(_this_, _oldSubstr_, _newSubstr_, _mem_)
```c
StringObject* String.replacestr(StringObject* this, StringObject* oldSubstr, StringObject* newSubstr, MemoryObject* mem);
```
Makes a new string with substring **oldSubstr** of **this** string replaced with **newSubstr**.

#### String.join(_this_, _liststr_, _mem_)
```c
StringObject* String.join(StringObject* this, ListObject* liststr, MemoryObject* mem);
```
Makes a new string by joining **liststr** with **this** string.
