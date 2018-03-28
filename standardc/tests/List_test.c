#include "../List.h"
#include "../gc.h"
#include "../unittest.h"

int encrypt(int i) {
    return (i+20)*7;
}

#define BUFSIZE 5
int BUF[BUFSIZE];
int COUNTER = 0;

void storeBuf(void* i) {
    BUF[COUNTER++] = *((int*) i)-1;
}

List* arr;

SETUP {
    arr = new_List();
    
    // Init the List to store type int.
    arr->init(arr, sizeof(int));
}

TEARDOWN {
    del(&arr);
}

RUN

    CASE("immediate-free")
        List* arr2 = new_List();
        del(&arr2);
    END

    CASE("push-pop")
        
        ASSERT(arr->len(arr) == 0);
        
        int i[] = {40, 1231};
        arr->push(arr, i);
        arr->push(arr, i+1);
        ASSERT(*((int*) arr->getitem(arr, 0)) == i[0]);
        ASSERT(*((int*) arr->getitem(arr, 1)) == i[1]);
        ASSERT(arr->len(arr) == 2);
        
        int* p;
        
        p = arr->pop(arr);
        ASSERT(arr->len(arr) == 1);
        ASSERT(*p == i[1]);
        
        p = arr->pop(arr);
        ASSERT(arr->len(arr) == 0);
        ASSERT(*p == i[0]);
        
        p = arr->pop(arr);
        ASSERT(arr->len(arr) == 0);
        ASSERT(p == NULL);
        
        p = arr->pop(arr);
        ASSERT(arr->len(arr) == 0);
        ASSERT(p == NULL);
        
    END
    
    CASE("resize")
    
        int TEST_N = 10000;
        
        int i;
        
        // Fill the array with many encrypted ints to induce resize.
        for (i=0; i<TEST_N; i++) {
            int j = encrypt(i);
            arr->push(arr, &j);
        }
        
        // Test the indices within the resized array.
        int is[] = {0, TEST_N >> 1, TEST_N-1};
        for (i=0; i<3; i++) {
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
        int is2[] = {-100, -1, TEST_N, TEST_N+1, 2*TEST_N};
        for (i=0; i<5; i++) {
            int* k = arr->at(arr, is2[i]);
            ASSERT(k == NULL);
        }
        
        // Test pop order
        for (i=0; i<TEST_N; i++) {
            int p = TEST_N-i-1;
            int j = encrypt(p);
            int* k = arr->pop(arr);
            ASSERT(arr->len(arr) == p);
            ASSERT(j == *k);
        }
        
    END
    
    CASE("setitem")
        ASSERT(arr->len(arr) == 0);
        
        int i[] = {1, 2, 3, 4};
        arr->push(arr, i);
        arr->push(arr, i+1);
        
        // replace the pushed items
        arr->set(arr, 1, i+2);
        ASSERT(arr->len(arr) == 2);
        ASSERT(*((int*) arr->getitem(arr, 0)) == i[0]);
        ASSERT(*((int*) arr->getitem(arr, 1)) == i[2]);
        
        arr->setitem(arr, 0, i+3);
        ASSERT(arr->len(arr) == 2);
        ASSERT(*((int*) arr->getitem(arr, 0)) == i[3]);
        ASSERT(*((int*) arr->getitem(arr, 1)) == i[2]);
    END
    
    CASE("set out-of-bounds")
        int size = 40;
        int i = 5;
        arr->initall(arr, sizeof(int), size, &i); // 40 5's
        
        int j[] = {40, 50, 60};
        
        ASSERT(arr->set(arr, size-1, j));
        ASSERT(*((int*) arr->getitem(arr, size-1)) == j[0]);
        ASSERT(*((int*) arr->getitem(arr, size-2)) == i);
        ASSERT(*((int*) arr->getitem(arr, size-3)) == i);
        ASSERT(*((int*) arr->getitem(arr, 0)) == i);
        ASSERT(*((int*) arr->getitem(arr, size >> 1)) == i);
        
        int d[] = {0, 1, 100};
        int k;
        for (k=0; k<3; k++) {
            ASSERT(!arr->set(arr, size+d[k], j + k));
            ASSERT(*((int*) arr->getitem(arr, size-1)) == j[0]);
            ASSERT(*((int*) arr->getitem(arr, size-2)) == i);
            ASSERT(*((int*) arr->getitem(arr, size-3)) == i);
            ASSERT(*((int*) arr->getitem(arr, 0)) == i);
            ASSERT(*((int*) arr->getitem(arr, size >> 1)) == i);
        }
    END

    CASE("initall")
        int i = 20;
        int j[] = {0, 4, 200, 1000};
        int k;
        for (k=0; k<4; k++) {
            int p = j[k];
            
            List* arr2 = new_List();
            
            arr2->initall(arr2, sizeof(int), p, &i);
            ASSERT(arr2->len(arr2) == p);
            
            // See contents are all same value
            int w;
            for (w=0; w<p; w++)
                ASSERT(*((int*) arr2->at(arr2, w)) == i);
            
            ASSERT(arr2->at(arr2, -1) == NULL);
            ASSERT(arr2->at(arr2, p) == NULL);
            ASSERT(arr2->at(arr2, p+1) == NULL);
            
            del(&arr2);
        }
        
    END
    
    CASE("initarray")
    
        // Test re-init (expect no memory leak)
        // then extend with empty array
        arr->initarray(arr, sizeof(int), 0, NULL);
        ASSERT(arr->len(arr) == 0);
        ASSERT(arr->at(arr, 0) == NULL);
        
        // Init a large random array
        int size = 5000;
        int is[size];
        int i;
        for (i=0; i<size; i++)
            is[i] = 123;
        is[size-1] = 122;
        is[size >> 2] = 13;
        
        List* arr2 = new_List();
        
        // Large array init - test resize.
        arr->initarray(arr, sizeof(int), size, is);
        arr2->initarray(arr2, sizeof(int), size, is);
        
        for (i=0; i<size; i++) {
            ASSERT(*((int*) arr->at(arr, i)) == is[i]);
            ASSERT(*((int*) arr2->at(arr2, i)) == is[i]);
        }
        
        ASSERT(arr->at(arr, size) == NULL);
        ASSERT(arr2->at(arr2, size) == NULL);
        
        del(&arr2);
    END
    
    CASE("foreach")
        int is[] = {1, 2, 3, 4, 5};
        arr->initarray(arr, sizeof(int), 5, is);
        arr->foreach(arr, &storeBuf);
        int i;
        for (i=0; i<BUFSIZE; i++) {
            int p = *((int*) arr->at(arr, i));
            ASSERT(p == is[i]);
            ASSERT(is[i]-1 == BUF[i]);
            ASSERT(p == BUF[i]+1);
        }
    END

STOP
