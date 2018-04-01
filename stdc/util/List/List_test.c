#include "stdc/unittest.h"

int encrypt(int i) {
    return (i+20)*7;
}

void use(Ptr ptr){}

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

    CASE("repeated-push")
        int* i = Memory.alloc(mem, sizeof(int));
        List.push(arr, i);
        List.push(arr, i);
        List.push(arr, i);
    END

    CASE("immediate-free")
        ListObject* arr2 = Memory.make(mem, List.new);
        use(arr2);
    END

    CASE("push-pop NULL")

        ASSERT(List.size(arr) == 0);
        List.push(arr, NULL);
        ASSERT(List.size(arr) == 1);
        List.push(arr, NULL);
        ASSERT(List.size(arr) == 2);
        ASSERT(List.pop(arr) == NULL);
        ASSERT(List.size(arr) == 1);
        ASSERT(List.pop(arr) == NULL);
        ASSERT(List.size(arr) == 0);

    END

    CASE("push-pop")
        ASSERT(List.at(arr, 0) == NULL);
        ASSERT(List.at(arr, 1) == NULL);
        ASSERT(List.at(arr, 2) == NULL);
        int* i = Memory.alloc(mem, sizeof(int));
        int* j = Memory.alloc(mem, sizeof(int));
        *i = 50;
        *j = 4;

        List.push(arr, i);
        List.push(arr, j);
        ASSERT(List.size(arr) == 2);
        ASSERT(*((int*) List.getitem(arr, 1)) == *j);
        ASSERT(*((int*) List.at(arr, -2)) == *i);

        int* test1 = List.pop(arr);
        Memory.track(mem, test1);
        ASSERT(*test1 == *j);

        int* test2 = List.pop(arr);
        Memory.track(mem, test2);
        ASSERT(*test2 == *i);

        ASSERT(List.size(arr) == 0);
        ASSERT(List.pop(arr) == NULL);
        ASSERT(List.pop(arr) == NULL);
        ASSERT(List.size(arr) == 0);
        List.push(arr, i);
        List.push(arr, j);
        ASSERT(List.size(arr) == 2);
        ASSERT(List.at(arr, 2) == NULL);
        ASSERT(*((int*) List.at(arr, -1)) == *j);
        ASSERT(*((int*) List.at(arr, 1)) == *j);
        ASSERT(*((int*) List.at(arr, 1)) == *j);

    END

    CASE("resize")

        int TEST_N = 10000;

        int i;
        ASSERT(List.size(arr) == 0);

        // Fill the array with many encrypted ints to induce resize.
        for (i=0; i<TEST_N; i++) {
            int* j = Memory.alloc(mem, sizeof(int));
            *j = encrypt(i);
            List.push(arr, j);
        }

        // Test the indices within the resized array.
        int is[] = {0, TEST_N >> 1, TEST_N-1};
        for (i=0; i<LEN(is); i++) {
            int p = is[i];
            int j = encrypt(p);
            int* k;

            k = List.getitem(arr, p);
            ASSERT(*k == j);

            // Test if at does the same as getitem.
            k = List.at(arr, p);
            ASSERT(*k == j);
        }

        // Test the indices outside the resized array.
        int is2[] = {TEST_N, TEST_N+1, 2*TEST_N};
        for (i=0; i<LEN(is2); i++) {
            int* k = List.at(arr, is2[i]);
            ASSERT(k == NULL);
        }

        // Test pop order
        for (i=0; i<TEST_N; i++) {
            int p = TEST_N-i-1;
            int j = encrypt(p);
            int* k = List.pop(arr);
            Memory.track(mem, k);
            ASSERT(List.size(arr) == p);
            ASSERT(j == *k);
        }

    END

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

        int* test1 = List.pop(arr);
        Memory.track(mem, test1);
        ASSERT(*test1 == *j);

        for (k=0; k<null_pos-2; k++) {
            int* test2 = List.pop(arr);
            Memory.track(mem, test2);
            ASSERT(*test2 == *i);
        }
        ASSERT(List.pop(arr) == NULL);
        Memory.track(mem, NULL);

        int* test3 = List.pop(arr);
        Memory.track(mem, test3);
        ASSERT(*test3 == *i);

    END

    CASE("push-pop refcount")
    
        MemoryObject* mem2 = Memory.new();
        
        int* b1 = Memory.alloc(mem2, sizeof(int));
        int* b2 = Memory.alloc(mem2, sizeof(int));
        
        *b1 = 20;
        *b2 = 30;
        
        List.push(arr, b1);
        List.push(arr, b2);
        // b1, b2 now have ref=2
        
        decref(mem2);
        // b1, b2 now have ref=1
        
        int* p;
        p = List.pop(arr);
        Memory.track(mem, p);
        ASSERT(p != NULL);
        ASSERT(*p == *b2);
        
        p = List.pop(arr);
        Memory.track(mem, p);
        ASSERT(*p == *b1);
        
        p = List.pop(arr);
        Memory.track(mem, p);
        ASSERT(p == NULL);
        
        p = List.pop(arr);
        Memory.track(mem, p);
        ASSERT(p == NULL);
    
    END

STOP
