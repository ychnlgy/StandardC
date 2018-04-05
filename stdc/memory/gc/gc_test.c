#include "stdc/unittest.h"

#include <stddef.h>
// NULL

SETUP {}
TEARDOWN{}

RUN

    CASE("inc-decref")

        int* a = new(sizeof(int), NULL);
        int* b = new(sizeof(int), NULL);

        *a = 4;
        *b = 5;

        ASSERT(*a + *b == 9);

        int i;
        for (i=0; i<4; i++) {
            ASSERT(incref(b) == 2);
            ASSERT(incref(b) == 3);
            ASSERT(*a + *b == 9);

            ASSERT(decref(b) == 2);
            ASSERT(*a + *b == 9);

            ASSERT(decref(b) == 1);
            ASSERT(*a + *b == 9);

            incref(b); incref(b);
            decref(b); decref(b);
        }

        ASSERT(decref(b) == 0);
        ASSERT(decref(a) == 0);



        int* c = new(sizeof(int), NULL);
        ASSERT(decref(c) == 0);
    END
    
    CASE("inc-decref NULL")
        ASSERT(incref(NULL) == -1);
        ASSERT(decref(NULL) == -1);
    END

STOP
