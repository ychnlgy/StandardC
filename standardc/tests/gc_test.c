#include <stdio.h>
#include <assert.h>

#include "../gc.h"

int main() {
    printf("Testing gc...");

    int* a = new(sizeof(int), &destroy_nothing);
    int* b = new(sizeof(int), &destroy_nothing);
    
    *a = 4;
    *b = 5;
    
    assert(*a + *b == 9);
    
    incref(b);
    incref(b);
    assert(*a + *b == 9);
    
    decref(b);
    assert(*a + *b == 9);
    
    decref(b);
    assert(*a + *b == 9);
    
    decref(b);
    decref(a);
    
    int* c = new(sizeof(int), &destroy_nothing);
    del(c);
    
    printf("OK (but you should use Valgrind to check for memory leaks)\n");
}
