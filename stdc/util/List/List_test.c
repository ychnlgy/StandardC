#include "stdc/lib.h"
#include "stdc/unittest.h"

int encrypt(int i) {
    return (i+20)*7;
}

void use(Ptr ptr){}

List* arr;
Memory* mem;

SETUP {
    mem = new_Memory();
    arr = mem->make(mem, &new_List);
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("repeated-push")
        int* i = mem->alloc(mem, sizeof(int));
        arr->push(arr, i);
        arr->push(arr, i);
        arr->push(arr, i);
    END

    CASE("immediate-free")
        List* arr2 = mem->make(mem, &new_List);
        use(arr2);
    END

    CASE("push-pop NULL")

        ASSERT(arr->size(arr) == 0);
        arr->push(arr, NULL);
        ASSERT(arr->size(arr) == 1);
        arr->push(arr, NULL);
        ASSERT(arr->size(arr) == 2);
        ASSERT(arr->pop(arr) == NULL);
        ASSERT(arr->size(arr) == 1);
        ASSERT(arr->pop(arr) == NULL);
        ASSERT(arr->size(arr) == 0);

    END

    CASE("push-pop")
        ASSERT(arr->at(arr, 0) == NULL);
        ASSERT(arr->at(arr, 1) == NULL);
        ASSERT(arr->at(arr, 2) == NULL);
        int* i = mem->alloc(mem, sizeof(int));
        int* j = mem->alloc(mem, sizeof(int));
        *i = 50;
        *j = 4;

        arr->push(arr, i);
        arr->push(arr, j);
        ASSERT(arr->size(arr) == 2);
        ASSERT(*((int*) arr->getitem(arr, 1)) == *j);
        ASSERT(*((int*) arr->at(arr, -2)) == *i);

        int* test1 = arr->pop(arr);
        mem->track(mem, test1);
        ASSERT(*test1 == *j);

        int* test2 = arr->pop(arr);
        mem->track(mem, test2);
        ASSERT(*test2 == *i);

        ASSERT(arr->size(arr) == 0);
        ASSERT(arr->pop(arr) == NULL);
        ASSERT(arr->pop(arr) == NULL);
        ASSERT(arr->size(arr) == 0);
        arr->push(arr, i);
        arr->push(arr, j);
        ASSERT(arr->size(arr) == 2);
        ASSERT(arr->at(arr, 2) == NULL);
        ASSERT(*((int*) arr->at(arr, -1)) == *j);
        ASSERT(*((int*) arr->at(arr, 1)) == *j);
        ASSERT(*((int*) arr->at(arr, 1)) == *j);

    END

    CASE("resize")

        int TEST_N = 10000;

        int i;
        ASSERT(arr->size(arr) == 0);

        // Fill the array with many encrypted ints to induce resize.
        for (i=0; i<TEST_N; i++) {
            int* j = mem->alloc(mem, sizeof(int));
            *j = encrypt(i);
            arr->push(arr, j);
        }

        // Test the indices within the resized array.
        int is[] = {0, TEST_N >> 1, TEST_N-1};
        for (i=0; i<LEN(is); i++) {
            int p = is[i];
            int j = encrypt(p);
            int* k;

            k = arr->getitem(arr, p);
            ASSERT(*k == j);

            // Test if at does the same as getitem.
            k = arr->at(arr, p);
            ASSERT(*k == j);
        }

        // Test the indices outside the resized array.
        int is2[] = {TEST_N, TEST_N+1, 2*TEST_N};
        for (i=0; i<LEN(is2); i++) {
            int* k = arr->at(arr, is2[i]);
            ASSERT(k == NULL);
        }

        // Test pop order
        for (i=0; i<TEST_N; i++) {
            int p = TEST_N-i-1;
            int j = encrypt(p);
            int* k = arr->pop(arr);
            mem->track(mem, k);
            ASSERT(arr->size(arr) == p);
            ASSERT(j == *k);
        }

    END

    CASE("setitem")
        ASSERT(arr->size(arr) == 0);

        int* i0 = mem->alloc(mem, sizeof(int*));
        int* i1 = mem->alloc(mem, sizeof(int*));
        int* i2 = mem->alloc(mem, sizeof(int*));
        int* i3 = mem->alloc(mem, sizeof(int*));

        *i0 = 1;
        *i1 = 2;
        *i2 = 3;
        *i3 = 4;

        arr->push(arr, i0);
        arr->push(arr, i1);

        // replace the pushed items
        arr->set(arr, 1, i2);
        ASSERT(arr->size(arr) == 2);
        ASSERT(*((int*) arr->getitem(arr, 0)) == *i0);
        ASSERT(*((int*) arr->getitem(arr, 1)) == *i2);

        arr->setitem(arr, 0, i3);
        ASSERT(arr->size(arr) == 2);
        ASSERT(*((int*) arr->getitem(arr, 0)) == *i3);
        ASSERT(*((int*) arr->getitem(arr, 1)) == *i2);

    END

    CASE("set out-of-bounds")
        int size = 40;
        int k;
        int* i = mem->alloc(mem, sizeof(int*));
        *i = 5;
        for (k=0; k<size; k++)
            arr->push(arr, i);

        int* j = mem->alloc(mem, sizeof(int*));
        *j = 100;

        ASSERT(arr->set(arr, size-1, j));
        ASSERT(*((int*) arr->getitem(arr, size-1)) == *j);
        ASSERT(*((int*) arr->getitem(arr, size-2)) == *i);
        ASSERT(*((int*) arr->getitem(arr, size-3)) == *i);
        ASSERT(*((int*) arr->getitem(arr, 0)) == *i);
        ASSERT(*((int*) arr->getitem(arr, size >> 1)) == *i);

        int d[] = {0, 1, 100};
        int* p = mem->alloc(mem, sizeof(int*));
        *p = 500;
        for (k=0; k<LEN(d); k++) {
            ASSERT(!arr->set(arr, size+d[k], p));
            ASSERT(*((int*) arr->getitem(arr, size-1)) == *j);
            ASSERT(*((int*) arr->getitem(arr, size-2)) == *i);
            ASSERT(*((int*) arr->getitem(arr, size-3)) == *i);
            ASSERT(*((int*) arr->getitem(arr, 0)) == *i);
            ASSERT(*((int*) arr->getitem(arr, size >> 1)) == *i);
        }

        long null_pos = 10;
        ASSERT(arr->set(arr, -null_pos, NULL));

        int* test1 = arr->pop(arr);
        mem->track(mem, test1);
        ASSERT(*test1 == *j);

        for (k=0; k<null_pos-2; k++) {
            int* test2 = arr->pop(arr);
            mem->track(mem, test2);
            ASSERT(*test2 == *i);
        }
        ASSERT(arr->pop(arr) == NULL);
        mem->track(mem, NULL);

        int* test3 = arr->pop(arr);
        mem->track(mem, test3);
        ASSERT(*test3 == *i);

    END

    CASE("push-pop refcount")
    
        Memory* mem2 = new_Memory();
        
        int* b1 = mem2->alloc(mem2, sizeof(int));
        int* b2 = mem2->alloc(mem2, sizeof(int));
        
        *b1 = 20;
        *b2 = 30;
        
        arr->push(arr, b1);
        arr->push(arr, b2);
        // b1, b2 now have ref=2
        
        decref(mem2);
        // b1, b2 now have ref=1
        
        int* p;
        p = arr->pop(arr);
        mem->track(mem, p);
        ASSERT(p != NULL);
        ASSERT(*p == *b2);
        
        p = arr->pop(arr);
        mem->track(mem, p);
        ASSERT(*p == *b1);
        
        p = arr->pop(arr);
        mem->track(mem, p);
        ASSERT(p == NULL);
        
        p = arr->pop(arr);
        mem->track(mem, p);
        ASSERT(p == NULL);
    
    END

STOP
