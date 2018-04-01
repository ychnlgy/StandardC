#include "stdc/lib.h"
#include "stdc/unittest/print.h" // for color printing
#include <string.h>
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
    printBold("Running %s...", __FILE__);
    MemoryObject* mem = Memory.new();
    
    StringObject* s1 = Memory.make(mem, String.new);
    String.set(s1, "Hello world!");
    
    StringObject* s2 = Memory.make(mem, String.new);
    String.set(s2, "Carrot");
    
    StringObject* s3 = String.copy(s1);
    Memory.track(mem, s3); // don't forget to let stack know
                         // about this new block of memory.
    
    // s1 is equal to s3 but not s2.
    assert(String.equals(s1, s3));
    assert(!String.equals(s1, s2));
    assert(!String.equals(s2, s3));
    
    assert(String.size(s1) == 12);
    assert(strcmp(String.cstr(s1), "Hello world!") == 0);
    
    decref(mem);
    printGreen("OK\n");
    return 0;
}
