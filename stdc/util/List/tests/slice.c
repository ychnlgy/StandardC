#include "stdc/unittest.h"

ListObject* arr;
ListObject* arr2;

ListObject* sub1;
ListObject* sub2;
ListObject* sub3;
ListObject* sub4;

MemoryObject* mem;

SETUP {
    mem = Memory.new();
    arr = Memory.make(mem, List.new);
    arr2 = Memory.make(mem, List.new);
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("slice")
        long i;
        long size = 1000;
        for (i=0; i<size; i++) {
            int* k = Memory.alloc(mem, sizeof(int));
            *k = i;
            List.push(arr, k);
        }
        
        sub1 = List.slice(arr, mem, 0, size);
        ASSERT(List.equals(sub1, arr));
        
        sub2 = List.slice(arr, mem, 0, 0);
        ASSERT(List.size(sub2) == 0);
        ASSERT(List.equals(sub2, arr2));
        
        sub3 = List.slice(arr, mem, size, size);
        ASSERT(List.size(sub3) == 0);
        ASSERT(List.equals(sub3, arr2));
        
        long start = 5;
        long end = 10;
        sub4 = List.slice(arr, mem, start, end);
        ASSERT(List.size(sub4) == 5);
        for (i=0; i<end-start; i++) {
            int* k = List.getitem(sub4, i);
            ASSERT(*k == i+start);
        }
    END

    CASE("bad-slice")
        long i;
        long size = 1000;
        for (i=0; i<size; i++) {
            int* k = Memory.alloc(mem, sizeof(int));
            *k = i;
            List.push(arr, k);
        }
        
        sub1 = List.slice(arr, mem, 4, 1);
        ASSERT(sub1 == NULL);
        
        sub2 = List.slice(arr, mem, -1, 40);
        ASSERT(sub2 == NULL);
        
        sub3 = List.slice(arr, mem, 1, size+1);
        ASSERT(sub3 == NULL);
    
    END

STOP
