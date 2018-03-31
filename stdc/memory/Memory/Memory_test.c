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
        memory->_->track(memory, a);

        b = memory->_->alloc(memory, sizeof(int));
        c = memory->_->make(memory, &new_int);

        *a = 4;
        *b = 6;
        *c = 10;

    END

    CASE("track NULL")

        a = memory->_->alloc(memory, sizeof(int));
        b = memory->_->alloc(memory, sizeof(int));
        c = new_int();
        int* d = new_int();
        memory->_->track(memory, c);
        memory->_->track(memory, d);
        memory->_->track(memory, NULL);
        memory->_->track(memory, NULL);

    END

STOP
