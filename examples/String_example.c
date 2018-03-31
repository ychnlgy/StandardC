#include "stdc/lib.h"
#include "stdc/unittest/print.h" // for color printing
#include <assert.h>

/*
 * An example demonstrating basic String usage:
 *  - set   : set the String's const char* value.
 *  - copy  : copy the String to a new memory block.
 *  - equals: check if two Strings are equal.
 *  - size  : return the number of characters in the String.
 *  - cstr  : return the const char* value of the String.
 */

int main() {
    Memory* mem = new_Memory();
    
    String* s1 = mem->make(mem, &new_String);
    s1->set(s1, "Hello world!");
    
    String* s2 = mem->make(mem, &new_String);
    s2->set(s2, "Carrot");
    
    String* s3 = s1->copy(s1);
    mem->track(mem, s3); // don't forget to let stack know
                         // about this new block of memory.
    
    // s1 is equal to s3 but not s2.
    assert(s1->equals(s1, s3));
    assert(!s1->equals(s1, s2));
    assert(!s2->equals(s2, s3));
    
    printBold("The length of \"%s\" is: ", s1->cstr(s1));
    printGreen("%d\n", s1->size(s1));
    
    decref(mem);
    return 0;
}
