#include "stdc/unittest.h"

void use(Ptr ptr){}

int encrypt(int i) {
    return (i+20)*7;
}

MemoryObject* mem;

ListObject* list1;
ListObject* list2;

ListObject* arr;
ListObject* arr2;

int* i1;
int* i2;
int* i3;
int* i4;

ListObject* sub1;
ListObject* sub2;
ListObject* sub3;
ListObject* sub4;

bool positive(Ptr ptr) {
    return *((int*) ptr) >= 0;
}

SETUP {
    mem = Memory.new();
    list1 = Memory.make(mem, List.new);
    list2 = Memory.make(mem, List.new);
    arr = Memory.make(mem, List.new);
    arr2 = Memory.make(mem, List.new);
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
    
    // Iterable
    
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
    
    // Object
    
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
    
    // Stack
    
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

    
    // Accessor
    
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
