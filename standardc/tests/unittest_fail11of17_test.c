#define SYSTEM_EXIT 0

#include "../unittest.h"

#include <stdlib.h> 
// malloc

#include <stdio.h>
#include <assert.h>

typedef struct Foo {
    char c;
    int i;
    float f;
} Foo;

Foo foo;
int a;
int* p;

SETUP {
    foo.c = 'w';
    foo.i = 40;
    foo.f = 10.10;
    
    a = 60;
    p = malloc(sizeof(int));
}

TEARDOWN {
    free(p);
}

RUN

    CASE("Do pigs fly?")
        ASSERT(2 + 2 == 4);
        ASSERT(3 + 2 == 4);
        ASSERT(5 + 5 ==10);
    END
    
    CASE("Multiple suppression")
        int i;
        for (i=0; i<10; i++)
            ASSERT(1 == 2);
        ASSERT(2 == 2);
    END
    
    CASE("Check Foo init")
        ASSERT(foo.i == a - 20);
        ASSERT(foo.c == 'w');
    END
    
    CASE("Check malloc'd")
        *p = 50;
        ASSERT(*p == 50);
    END
    
    CASE("Empty")
    END

STOP
