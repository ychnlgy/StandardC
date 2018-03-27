#include "../ArrayList.h"
#include "../gc.h"
#include "../algorithm.h"
#include "../Memory.h"

#include <stdio.h>
#include <assert.h>

int encrypt(int i) {
    return (i+20)*7;
}

void do_nothing(void* ptr) {}

int main() {
    printf("Running %s...", __FILE__);
    Memory* mem = new_Memory();
    
    ArrayList* a1 = make_Memory(mem, &new_ArrayList);
    init_ArrayList(a1, sizeof(int));
    
    // Test general properties.
    assert(len_ArrayList(a1) == 0);
    
    int i1 = 40;
    int i2 = 1231;
    push_ArrayList(a1, &i1);
    push_ArrayList(a1, &i2);
    assert(*((int*) getitem_ArrayList(a1, 0)) == i1);
    assert(*((int*) getitem_ArrayList(a1, 1)) == i2);
    assert(len_ArrayList(a1) == 2);
    
    int* i3 = pop_ArrayList(a1);
    assert(len_ArrayList(a1) == 1);
    int* i4 = pop_ArrayList(a1);
    assert(len_ArrayList(a1) == 0);
    int* i5 = pop_ArrayList(a1);
    assert(len_ArrayList(a1) == 0);
    int* i6 = pop_ArrayList(a1);
    assert(len_ArrayList(a1) == 0);
    
    assert(*i3 == i2); // stack reverse
    assert(*i4 == i1);
    assert(i5 == NULL);
    assert(i6 == NULL);
    
    // Test resize
    int TEST_N = 10000;
    
    {
        int i;
        for (i=0; i<TEST_N; i++) {
            int j = encrypt(i);
            push_ArrayList(a1, &j);
        }
    }
    
    int is[] = {0, TEST_N >> 1, TEST_N-1};
    
    {
        int i;
        for (i=0; i<len(is); i++) {
            int j = encrypt(is[i]);
            int* k = getitem_ArrayList(a1, is[i]);
            assert(*k == j);
            k = at_ArrayList(a1, is[i]);
            assert(*k == j);
        }
    }
    
    int is2[] = {TEST_N, TEST_N+1, 2*TEST_N};
    
    {
        int i;
        for (i=0; i<len(is2); i++) {
            int* k = at_ArrayList(a1, is2[i]);
            assert(k == NULL);
        }
    }
    
    {
        int i;
        for (i=0; i<TEST_N; i++) {
            int p = TEST_N-i-1;
            int j = encrypt(p);
            int* k = pop_ArrayList(a1);
            assert(len_ArrayList(a1) == p);
            assert(j == *k);
        }
    }
    
    // Test setitem
    assert(len_ArrayList(a1) == 0);
    push_ArrayList(a1, &i1);
    push_ArrayList(a1, &i2);
    
    int p = 100;
    setitem_ArrayList(a1, 1, &p);
    assert(len_ArrayList(a1) == 2);
    assert(*((int*) getitem_ArrayList(a1, 0)) == i1);
    assert(*((int*) getitem_ArrayList(a1, 1)) == p);
    
    // Test initall
    int is3[] = {1, 4, 7, 8};
    int is4[] = {0, 4, 200, 1000};
    
    {
        int k;
        for (k=0; k<len(is4); k++) {
            int p = is4[k];
            ArrayList* a2 = make_Memory(mem, &new_ArrayList);
            initall_ArrayList(a2, sizeof(int), p, is3);
            assert(len_ArrayList(a2) == p);
            int i;
            for (i=0; i<p; i++)
                assert(*((int*) at_ArrayList(a2, i)) == is3[0]);
            assert(at_ArrayList(a2, p) == NULL);
            assert(at_ArrayList(a2, p+1) == NULL);
        }
    }
    
    // Test initarray
    ArrayList* a3 = make_Memory(mem, &new_ArrayList);
    initarray_ArrayList(a3, sizeof(int), 0, NULL);
    assert(len_ArrayList(a3) == 0);
    assert(at_ArrayList(a3, 0) == NULL);

    int size = 5000;
    int is5[size];
    
    {
        int i;
        for (i=0; i<size; i++)
            is5[i] = 123;
        is5[size-1] = 122;
        is5[size >> 2] = 13;
    }
    
    ArrayList* a4 = make_Memory(mem, &new_ArrayList);
    initarray_ArrayList(a4, sizeof(int), size, is5);
    
    {
        int i;
        for (i=0; i<size; i++)
            assert(*((int*) at_ArrayList(a4, i)) == is5[i]);
        assert(at_ArrayList(a4, size) == NULL);
    }
    
    // Test foreach
    ArrayList* a5 = make_Memory(mem, &new_ArrayList);
    initarray_ArrayList(a5, sizeof(int), len(is3), is3);
    foreach_ArrayList(a5, &do_nothing);
    
    free_Memory(mem);
    printf("OK\n");
    return 0;
}
