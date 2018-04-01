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

    CASE("repeated-push")
        int* i = Memory.alloc(mem, sizeof(int));
        List.push(arr, i);
        List.push(arr, i);
        List.push(arr, i);
    END
    
    CASE("push-pop NULL")

        ASSERT(List.size(arr) == 0);
        List.push(arr, NULL);
        ASSERT(List.size(arr) == 1);
        List.push(arr, NULL);
        ASSERT(List.size(arr) == 2);
        ASSERT(List.pop(arr, mem) == NULL);
        ASSERT(List.size(arr) == 1);
        ASSERT(List.pop(arr, mem) == NULL);
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

        int* test1 = List.pop(arr, mem);
        ASSERT(*test1 == *j);

        int* test2 = List.pop(arr, mem);
        ASSERT(*test2 == *i);

        ASSERT(List.size(arr) == 0);
        ASSERT(List.pop(arr, mem) == NULL);
        ASSERT(List.pop(arr, mem) == NULL);
        ASSERT(List.size(arr) == 0);
        List.push(arr, i);
        List.push(arr, j);
        ASSERT(List.size(arr) == 2);
        ASSERT(List.at(arr, 2) == NULL);
        ASSERT(*((int*) List.back(arr)) == *j);
        ASSERT(*((int*) List.at(arr, 1)) == *j);
        ASSERT(*((int*) List.at(arr, 1)) == *j);

    END
    
    CASE("pushes")
        List.pushes(arr, 0);
        ASSERT(List.size(arr) == 0);
    
        int* i1 = Memory.alloc(mem, sizeof(int));
        int* i2 = Memory.alloc(mem, sizeof(int));
        *i1 = 20;
        *i2 = 40;
        
        List.pushes(arr, 2, i1, i2);
        ASSERT(List.size(arr) == 2);
        int* j1 = List.at(arr, 0);
        int* j2 = List.back(arr);
        
        ASSERT(*j1 == *i1);
        ASSERT(*j2 == *i2);
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
        p = List.pop(arr, mem);
        ASSERT(p != NULL);
        ASSERT(*p == *b2);
        
        p = List.pop(arr, mem);
        ASSERT(*p == *b1);
        
        p = List.pop(arr, mem);
        ASSERT(p == NULL);
        
        p = List.pop(arr, mem);
        ASSERT(p == NULL);
    
    END

STOP
