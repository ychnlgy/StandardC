#include "stdc/unittest.h"

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

    CASE("immediate-free")
        ListObject* arr2 = Memory.make(mem, List.new);
        use(arr2);
    END
    
    CASE("equals")
        ListObject* arr2 = Memory.make(mem, List.new);
        ASSERT(List.isEmpty(arr2));
        ASSERT(List.equals(arr, arr2));
        
        int* i1 = Memory.alloc(mem, sizeof(int));
        int* i2 = Memory.alloc(mem, sizeof(int));
        List.pushes(arr2, 2, i1, i2);
        ASSERT(!List.isEmpty(arr2));
        
        ASSERT(!List.equals(arr, arr2));
        
        List.pushes(arr, 2, i2, i1);
        ASSERT(!List.equals(arr, arr2));
        
        List.clear(arr);
        List.pushes(arr, 2, i1, i2);
        ASSERT(List.equals(arr, arr2));
    END
    
    CASE("copy")
        int* i1 = Memory.alloc(mem, sizeof(int));
        int* i2 = Memory.alloc(mem, sizeof(int));
        ASSERT(List.isEmpty(arr));
        List.pushes(arr, 2, i1, i2);
        ASSERT(!List.isEmpty(arr));
        ASSERT(List.size(arr) == 2);
        ListObject* arr2 = List.copy(arr, mem);
        ASSERT(List.size(arr2) == 2);
        ASSERT(List.equals(arr, arr2));
        List.push(arr, i1);
        ASSERT(List.size(arr) == 3);
        ASSERT(List.size(arr2) == 2);
        ASSERT(!List.equals(arr, arr2));
    END
    
STOP
