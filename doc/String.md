# String

String class for the ease of string manipulation.

## Files
 * [stdc/util/String/String.h](../stdc/util/String/String.h)
 * [stdc/util/String/String_protected.h](../stdc/util/String/String_protected.h)
 * [stdc/util/String/String.c](../stdc/util/String/String.c)
 * [stdc/util/String/String_test.c](../stdc/util/String/String_test.c)

## Demonstration
```c
#include "stdc/lib.h"
#include <stdio.h>
#include <assert.h>

int main() {
    Memory* mem = new_Memory();
    
    String* s1 = mem->_->make(mem, &new_String);
    s1->_->set(s1, "Hello world!");
    
    String* s2 = mem->_->make(mem, &new_String);
    s2->_->set(s2, "Carrot");
    
    String* s3 = s1->_->copy(s1);
    mem->_->track(mem, s3); // don't forget to let stack know
                         // about this new block of memory.
    
    // s1 is equal to s3 but not s2.
    assert(s1->_->equals(s1, s3));
    assert(!s1->_->equals(s1, s2));
    assert(!s2->_->equals(s2, s3));
    
    printf("The length of \"%s\" is: %d\n", s1->_->cstr(s1), s1->_->size(s1));
    
    decref(mem);
    return 0;
}
```

## String.set(_this_, _cstr_)
```c
void String.set(String* this, CStr cstr);
```
Sets the value of this string to **cstr**. 
See [types](../stdc/util/types.h) for the declaration of ```CStr```.

## String.copy(_this_)
```c
String* String.copy(String* this);
```
Allocates a copy of this string on heap memory and returns the pointer to it.

**Remember to track it on the memory scope.**

```c
#include "stdc/lib.h"

int main() {
  Memory* mem = new_Memory();
  
  String* s1 = mem->_->make(mem, &new_String);
  String* s2 = s1->_->copy(s1);
  mem->_->track(mem, s2); // if you forget this, memory leak of s2 will occur.
  
  decref(mem); // no memory leaks.
}
```

## String.equals(_this_, _other_)
```c
bool String.equals(String* this, String* other);
```
Returns ```true``` if this string equals the other string.

## String.size(_this_)
```c
long String.size(String* this);
```
Returns the number of characters in this string.

## String.cstr(_this_)
```c
CStr String.cstr(String* this);
```
Returns the [CStr](../stdc/util/types.h) data of this string.

## String.format(_this_, ...)
```c
String* String.format(String* this, ...);
```
Formats this string with variable arguments. 
Returns the formatted String that should be tracked by the [memory scope](Memory.md).
```c
#include "stdc/lib.h"
#include <stdio.h>

int main() {
    Memory* mem = new_Memory();
    
    String* s1 = mem->_->make(mem, &new_String);
    s1->_->set(s1, "%d eggs a %s. Have a good day, %s!\n");
    
    String* s2 = s1->_->format(s1, 12, "dozen", "mister");
    mem->_->track(mem, s2); // REMEMBER TO DO THIS!
    
    printf("%s", s2->_->cstr(s2));
    
    decref(mem);
}
```
