#include "stdc/unittest.h"

int encrypt(int i) {
    return (i+20)*7;
}

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
            int* k = List.pop(arr, mem);
            ASSERT(List.size(arr) == p);
            ASSERT(j == *k);
        }

    END
    
    CASE("empty extend-concat")
        ListObject* arr2 = Memory.make(mem, List.new);
        
        List.extend(arr, arr2);
        ASSERT(List.size(arr) == 0);
        ASSERT(List.size(arr2) == 0);
        
        ListObject* arr3 = List.add(arr, arr2, mem);
        ASSERT(List.size(arr) == 0);
        ASSERT(List.size(arr2) == 0);
        ASSERT(List.size(arr3) == 0);
    END
    
    CASE("extend")
        ListObject* arr2 = Memory.make(mem, List.new);
        ListObject* arr3 = Memory.make(mem, List.new);
        ListObject* arr4 = Memory.make(mem, List.new);
        
        long size1 = 10000;
        long i;
        for (i=0; i<size1; i++) {
            int* k = Memory.alloc(mem, sizeof(int));
            *k = i;
            List.push(arr, k);
            List.push(arr3, k);
        }
        
        List.extend(arr2, arr);
        ASSERT(List.size(arr2) == size1);
        ASSERT(List.equals(arr, arr2));
        ASSERT(List.equals(arr2, arr3));
        ASSERT(List.equals(arr, arr3));
        ASSERT(!List.equals(arr4, arr));
        ASSERT(!List.equals(arr4, arr2));
        ASSERT(!List.equals(arr4, arr3));
    
    END
    
    CASE("extend-concat")
        ListObject* arr2 = Memory.make(mem, List.new);
        
        long i;
        long size = 10000;
        for (i=0; i<size; i++) {
            int* k = Memory.alloc(mem, sizeof(int));
            *k = i;
            List.push(arr, k);
        }
        
        ASSERT(List.size(arr) == size);
        ListObject* arr3 = List.add(arr, arr2, mem);
        
        ASSERT(List.size(arr3) == size);
        ASSERT(List.equals(arr3, arr));
        ASSERT(!List.equals(arr3, arr2));
        
        List.extend(arr3, arr2);
        
        ASSERT(List.equals(arr3, arr));
        ASSERT(!List.equals(arr3, arr2));
        
        List.extend(arr2, arr3);
        
        ASSERT(List.size(arr2) == size);
        ASSERT(List.equals(arr3, arr));
        ASSERT(List.equals(arr3, arr2));
    
    END

STOP
