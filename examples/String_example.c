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
    
    assert(s1->_->size(s1) == 12);
    assert(strcmp(s1->_->cstr(s1), "Hello world!") == 0);
    
    decref(mem);
    printGreen("OK\n");
    return 0;
}
