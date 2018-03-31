#include "stdc/unittest.h"

int encrypt(int i) {
    return (i+20)*7;
}

void use(Ptr ptr){}

List* arr;
Memory* mem;

SETUP {
    mem = new_Memory();
    arr = mem->_->make(mem, &new_List);
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("repeated-push")
        int* i = mem->_->alloc(mem, sizeof(int));
        arr->_->push(arr, i);
        arr->_->push(arr, i);
        arr->_->push(arr, i);
    END

    CASE("immediate-free")
        List* arr2 = mem->_->make(mem, &new_List);
        use(arr2);
    END

    CASE("push-pop NULL")

        ASSERT(arr->_->size(arr) == 0);
        arr->_->push(arr, NULL);
        ASSERT(arr->_->size(arr) == 1);
        arr->_->push(arr, NULL);
        ASSERT(arr->_->size(arr) == 2);
        ASSERT(arr->_->pop(arr) == NULL);
        ASSERT(arr->_->size(arr) == 1);
        ASSERT(arr->_->pop(arr) == NULL);
        ASSERT(arr->_->size(arr) == 0);

    END

    CASE("push-pop")
        ASSERT(arr->_->at(arr, 0) == NULL);
        ASSERT(arr->_->at(arr, 1) == NULL);
        ASSERT(arr->_->at(arr, 2) == NULL);
        int* i = mem->_->alloc(mem, sizeof(int));
        int* j = mem->_->alloc(mem, sizeof(int));
        *i = 50;
        *j = 4;

        arr->_->push(arr, i);
        arr->_->push(arr, j);
        ASSERT(arr->_->size(arr) == 2);
        ASSERT(*((int*) arr->_->getitem(arr, 1)) == *j);
        ASSERT(*((int*) arr->_->at(arr, -2)) == *i);

        int* test1 = arr->_->pop(arr);
        mem->_->track(mem, test1);
        ASSERT(*test1 == *j);

        int* test2 = arr->_->pop(arr);
        mem->_->track(mem, test2);
        ASSERT(*test2 == *i);

        ASSERT(arr->_->size(arr) == 0);
        ASSERT(arr->_->pop(arr) == NULL);
        ASSERT(arr->_->pop(arr) == NULL);
        ASSERT(arr->_->size(arr) == 0);
        arr->_->push(arr, i);
        arr->_->push(arr, j);
        ASSERT(arr->_->size(arr) == 2);
        ASSERT(arr->_->at(arr, 2) == NULL);
        ASSERT(*((int*) arr->_->at(arr, -1)) == *j);
        ASSERT(*((int*) arr->_->at(arr, 1)) == *j);
        ASSERT(*((int*) arr->_->at(arr, 1)) == *j);

    END

    CASE("resize")

        int TEST_N = 10000;

        int i;
        ASSERT(arr->_->size(arr) == 0);

        // Fill the array with many encrypted ints to induce resize.
        for (i=0; i<TEST_N; i++) {
            int* j = mem->_->alloc(mem, sizeof(int));
            *j = encrypt(i);
            arr->_->push(arr, j);
        }

        // Test the indices within the resized array.
        int is[] = {0, TEST_N >> 1, TEST_N-1};
        for (i=0; i<LEN(is); i++) {
            int p = is[i];
            int j = encrypt(p);
            int* k;

            k = arr->_->getitem(arr, p);
            ASSERT(*k == j);

            // Test if at does the same as getitem.
            k = arr->_->at(arr, p);
            ASSERT(*k == j);
        }

        // Test the indices outside the resized array.
        int is2[] = {TEST_N, TEST_N+1, 2*TEST_N};
        for (i=0; i<LEN(is2); i++) {
            int* k = arr->_->at(arr, is2[i]);
            ASSERT(k == NULL);
        }

        // Test pop order
        for (i=0; i<TEST_N; i++) {
            int p = TEST_N-i-1;
            int j = encrypt(p);
            int* k = arr->_->pop(arr);
            mem->_->track(mem, k);
            ASSERT(arr->_->size(arr) == p);
            ASSERT(j == *k);
        }

    END

    CASE("setitem")
        ASSERT(arr->_->size(arr) == 0);

        int* i0 = mem->_->alloc(mem, sizeof(int*));
        int* i1 = mem->_->alloc(mem, sizeof(int*));
        int* i2 = mem->_->alloc(mem, sizeof(int*));
        int* i3 = mem->_->alloc(mem, sizeof(int*));

        *i0 = 1;
        *i1 = 2;
        *i2 = 3;
        *i3 = 4;

        arr->_->push(arr, i0);
        arr->_->push(arr, i1);

        // replace the pushed items
        arr->_->set(arr, 1, i2);
        ASSERT(arr->_->size(arr) == 2);
        ASSERT(*((int*) arr->_->getitem(arr, 0)) == *i0);
        ASSERT(*((int*) arr->_->getitem(arr, 1)) == *i2);

        arr->_->setitem(arr, 0, i3);
        ASSERT(arr->_->size(arr) == 2);
        ASSERT(*((int*) arr->_->getitem(arr, 0)) == *i3);
        ASSERT(*((int*) arr->_->getitem(arr, 1)) == *i2);

    END

    CASE("set out-of-bounds")
        int size = 40;
        int k;
        int* i = mem->_->alloc(mem, sizeof(int*));
        *i = 5;
        for (k=0; k<size; k++)
            arr->_->push(arr, i);

        int* j = mem->_->alloc(mem, sizeof(int*));
        *j = 100;

        ASSERT(arr->_->set(arr, size-1, j));
        ASSERT(*((int*) arr->_->getitem(arr, size-1)) == *j);
        ASSERT(*((int*) arr->_->getitem(arr, size-2)) == *i);
        ASSERT(*((int*) arr->_->getitem(arr, size-3)) == *i);
        ASSERT(*((int*) arr->_->getitem(arr, 0)) == *i);
        ASSERT(*((int*) arr->_->getitem(arr, size >> 1)) == *i);

        int d[] = {0, 1, 100};
        int* p = mem->_->alloc(mem, sizeof(int*));
        *p = 500;
        for (k=0; k<LEN(d); k++) {
            ASSERT(!arr->_->set(arr, size+d[k], p));
            ASSERT(*((int*) arr->_->getitem(arr, size-1)) == *j);
            ASSERT(*((int*) arr->_->getitem(arr, size-2)) == *i);
            ASSERT(*((int*) arr->_->getitem(arr, size-3)) == *i);
            ASSERT(*((int*) arr->_->getitem(arr, 0)) == *i);
            ASSERT(*((int*) arr->_->getitem(arr, size >> 1)) == *i);
        }

        long null_pos = 10;
        ASSERT(arr->_->set(arr, -null_pos, NULL));

        int* test1 = arr->_->pop(arr);
        mem->_->track(mem, test1);
        ASSERT(*test1 == *j);

        for (k=0; k<null_pos-2; k++) {
            int* test2 = arr->_->pop(arr);
            mem->_->track(mem, test2);
            ASSERT(*test2 == *i);
        }
        ASSERT(arr->_->pop(arr) == NULL);
        mem->_->track(mem, NULL);

        int* test3 = arr->_->pop(arr);
        mem->_->track(mem, test3);
        ASSERT(*test3 == *i);

    END

    CASE("push-pop refcount")
    
        Memory* mem2 = new_Memory();
        
        int* b1 = mem2->_->alloc(mem2, sizeof(int));
        int* b2 = mem2->_->alloc(mem2, sizeof(int));
        
        *b1 = 20;
        *b2 = 30;
        
        arr->_->push(arr, b1);
        arr->_->push(arr, b2);
        // b1, b2 now have ref=2
        
        decref(mem2);
        // b1, b2 now have ref=1
        
        int* p;
        p = arr->_->pop(arr);
        mem->_->track(mem, p);
        ASSERT(p != NULL);
        ASSERT(*p == *b2);
        
        p = arr->_->pop(arr);
        mem->_->track(mem, p);
        ASSERT(*p == *b1);
        
        p = arr->_->pop(arr);
        mem->_->track(mem, p);
        ASSERT(p == NULL);
        
        p = arr->_->pop(arr);
        mem->_->track(mem, p);
        ASSERT(p == NULL);
    
    END

STOP
