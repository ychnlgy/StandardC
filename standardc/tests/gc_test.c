#include "../gc.h"
#include "../unittest.h"

SETUP {}
TEARDOWN{}

RUN

    CASE("inc-decref")
    
        int* a = new(sizeof(int), &destroy_nothing);
        int* b = new(sizeof(int), &destroy_nothing);
        
        *a = 4;
        *b = 5;
        
        ASSERT(*a + *b == 9);
        
        incref(&b);
        incref(&b);
        ASSERT(*a + *b == 9);
        
        decref(&b);
        ASSERT(*a + *b == 9);
        
        decref(&b);
        ASSERT(*a + *b == 9);
        
        ASSERT(b != NULL);
        decref(&b);
        ASSERT(b == NULL);
        
        ASSERT(a != NULL);
        decref(&a);
        ASSERT(a == NULL);
        
        int* c = new(sizeof(int), &destroy_nothing);
        
        ASSERT(c != NULL);
        del(&c);
        ASSERT(c == NULL);
    END

STOP
