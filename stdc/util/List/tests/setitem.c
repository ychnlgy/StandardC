#include "stdc/unittest.h"

ListObject* arr;
MemoryObject* mem;

SETUP {
    mem = Memory.new();
    arr = Memory.make(mem, List.new);
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("setitem")
        ASSERT(List.size(arr) == 0);

        int* i0 = Memory.alloc(mem, sizeof(int*));
        int* i1 = Memory.alloc(mem, sizeof(int*));
        int* i2 = Memory.alloc(mem, sizeof(int*));
        int* i3 = Memory.alloc(mem, sizeof(int*));

        *i0 = 1;
        *i1 = 2;
        *i2 = 3;
        *i3 = 4;

        List.push(arr, i0);
        List.push(arr, i1);

        // replace the pushed items
        List.set(arr, 1, i2);
        ASSERT(List.size(arr) == 2);
        ASSERT(*((int*) List.getitem(arr, 0)) == *i0);
        ASSERT(*((int*) List.getitem(arr, 1)) == *i2);

        List.setitem(arr, 0, i3);
        ASSERT(List.size(arr) == 2);
        ASSERT(*((int*) List.getitem(arr, 0)) == *i3);
        ASSERT(*((int*) List.getitem(arr, 1)) == *i2);

    END

    CASE("set out-of-bounds")
        int size = 40;
        int k;
        int* i = Memory.alloc(mem, sizeof(int*));
        *i = 5;
        for (k=0; k<size; k++)
            List.push(arr, i);

        int* j = Memory.alloc(mem, sizeof(int*));
        *j = 100;

        ASSERT(List.set(arr, size-1, j));
        ASSERT(*((int*) List.getitem(arr, size-1)) == *j);
        ASSERT(*((int*) List.getitem(arr, size-2)) == *i);
        ASSERT(*((int*) List.getitem(arr, size-3)) == *i);
        ASSERT(*((int*) List.getitem(arr, 0)) == *i);
        ASSERT(*((int*) List.getitem(arr, size >> 1)) == *i);

        int d[] = {0, 1, 100};
        int* p = Memory.alloc(mem, sizeof(int*));
        *p = 500;
        for (k=0; k<LEN(d); k++) {
            ASSERT(!List.set(arr, size+d[k], p));
            ASSERT(*((int*) List.getitem(arr, size-1)) == *j);
            ASSERT(*((int*) List.getitem(arr, size-2)) == *i);
            ASSERT(*((int*) List.getitem(arr, size-3)) == *i);
            ASSERT(*((int*) List.getitem(arr, 0)) == *i);
            ASSERT(*((int*) List.getitem(arr, size >> 1)) == *i);
        }

        long null_pos = 10;
        ASSERT(List.set(arr, -null_pos, NULL));

        int* test1 = List.pop(arr, mem);
        ASSERT(*test1 == *j);

        for (k=0; k<null_pos-2; k++) {
            int* test2 = List.pop(arr, mem);
            ASSERT(*test2 == *i);
        }
        ASSERT(List.pop(arr, mem) == NULL);

        int* test3 = List.pop(arr, mem);
        ASSERT(*test3 == *i);

    END

STOP
