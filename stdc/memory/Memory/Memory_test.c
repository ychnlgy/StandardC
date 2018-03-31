#include "stdc/lib.h"
#include "stdc/unittest.h"

void* new_int() {
    return new(sizeof(int), NULL);
}

int* a;
int* b;
int* c;

Memory* memory;

SETUP{
    memory = new_Memory();
}

TEARDOWN{
    decref(memory);
}

RUN

    CASE("old-method")

        a = new(sizeof(int), NULL);
        b = new(sizeof(int), NULL);
        c = new_int();

        *a = 4;
        *b = 6;
        *c = 10;

        decref(a);
        decref(b);
        decref(c);

    END

    CASE("new-method")

        a = new(sizeof(int), NULL);
        memory->track(memory, a);

        b = memory->alloc(memory, sizeof(int));
        c = memory->make(memory, &new_int);

        *a = 4;
        *b = 6;
        *c = 10;

    END

    CASE("track NULL")

        a = memory->alloc(memory, sizeof(int));
        b = memory->alloc(memory, sizeof(int));
        c = new_int();
        int* d = new_int();
        memory->track(memory, c);
        memory->track(memory, d);
        memory->track(memory, NULL);
        memory->track(memory, NULL);

    END

STOP
