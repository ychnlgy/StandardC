#include "stdc/unittest.h"

MemoryObject* mem;
ListObject* list1;
ListObject* list2;
int* i1;
int* i2;
int* i3;
int* i4;

bool positive(Ptr ptr) {
    return *((int*) ptr) >= 0;
}

SETUP {
    mem = Memory.new();
    list1 = Memory.make(mem, List.new);
    list2 = Memory.make(mem, List.new);
    i1 = Memory.alloc(mem, sizeof(int));
    *i1 = 20;
    i2 = Memory.alloc(mem, sizeof(int));
    *i2 = -20;
    i3 = Memory.alloc(mem, sizeof(int));
    *i3 = 30;
    i4 = Memory.alloc(mem, sizeof(int));
    *i4 = -1;
    
}

TEARDOWN {
    decref(mem);
}

RUN
    
    CASE("filter-empty")
        list2 = List.filter(list1, positive, mem);
        ASSERT(List.size(list2) == 0);
    END

    CASE("filter")
        List.push(list1, i1);
        List.push(list1, i2);
        List.push(list1, i3);
        List.push(list1, i4);
        list2 = List.filter(list1, positive, mem);
        ASSERT(List.size(list2) == 2);
        int* j1 = List.getitem(list2, 0);
        ASSERT(*j1 == 20);
        int* j2 = List.getitem(list2, 1);
        ASSERT(*j2 == 30);
    END

STOP
