#include "stdc/unittest.h"

void* new_int() {
    return new(sizeof(int), NULL);
}

int* a;
int* b;
int* c;

MemoryObject* memory;

SETUP{
    memory = Memory.new();
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
        Memory.track(memory, a);

        b = Memory.alloc(memory, sizeof(int));
        c = Memory.make(memory, &new_int);

        *a = 4;
        *b = 6;
        *c = 10;

    END

    CASE("track NULL")

        a = Memory.alloc(memory, sizeof(int));
        b = Memory.alloc(memory, sizeof(int));
        c = new_int();
        int* d = new_int();
        Memory.track(memory, c);
        Memory.track(memory, d);
        Memory.track(memory, NULL);
        Memory.track(memory, NULL);

    END

STOP
