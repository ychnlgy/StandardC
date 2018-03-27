#include "../String.h"
#include "../gc.h"

#include <stdio.h>
#include <assert.h>

int main() {
    printf("Testing String...");
    
    String* s1 = new_String("Hello world!");
    assert(len_String(s1) == 12);
    
    String* s2 = copy_String(s1);
    assert(len_String(s2) == 12);
    String* s3 = new_String("Evil bunny");
    assert(len_String(s3) == 10);
    
    assert(equals_String(s1, s2));
    assert(!equals_String(s1, s3));
    assert(!equals_String(s2, s3));
    
    decref(s1);
    decref(s2);
    decref(s3);
    
    printf("OK\n");
}
