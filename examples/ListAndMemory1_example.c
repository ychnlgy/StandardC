#include "stdc/lib.h"
#include <assert.h>
#include "stdc/unittest/print.h"

/* 
 * An example demonstrating basic List usage:
 *  - push: appends a pointer to an element to the back of the list.
 *  - pop : removes and returns the pointer of the element at the back of the list.
 *  - at  : safely access the list.
 *  - set : replaces the element at the index with a new element.
 *
 * Note: at and set both support negative indexing.
 */

int main() {
    printBold("Running %s...", __FILE__);
    MemoryObject* mem = Memory.new();
    
    int* i1 = Memory.alloc(mem, sizeof(int));
    int* i2 = Memory.alloc(mem, sizeof(int));
    *i1 = 40;
    *i2 = 60;

    ListObject* list = Memory.make(mem, List.new);
    List.push(list, i1);
    List.push(list, i2);
    // The list is now [40, 60]
    
    // List.size returns the size!
    assert(List.size(list) == 2);
    
    int* j1 = List.at(list, 0);
    assert(*j1 == 40);
    
    int* j2 = List.at(list, 1);
    assert(*j2 == 60);
    
    // Python-style negative indexing.
    int* j3 = List.at(list, -1); // -1 means back of list.
    assert(*j3 == *i2);
    
    int* j4 = List.at(list, -2); // -2 means second last item.
    assert(*j4 == *i1);
    
    // Out of range access returns NULL
    // List is now [40, 60]
    int* j5 = List.at(list, 2); // the third element does not exist.
    assert(j5 == NULL);
    
    // Elements of the array are pointers
    // to the original data.
    *i1 = 70; // Since the first element points to
              // the same block of memory as i1,
              // we can change *i1 to change 
              // element 0 of the list.
    
    // List is now [70, 60]
    assert(*j1 == 70);
    int* k1 = List.at(list, 0);
    assert(*k1 == 70); // k1 and j1 and i1 all point to the same memory.
    
    int* i3 = Memory.alloc(mem, sizeof(int));
    *i3 = 90; // we want to insert 90 into position 0.
    
    // Set the 0th element to a new element.
    // List manages incref and decref for you:
    // decref is applied to the 0th element
    // incref is applied to the inserted element.
    List.set(list, 0, i3);
    // List is now [90, 60]
    assert(*j1 == 70); // the old pointer is not changed.
    
    // Here we show that the element at 0 is indeed 90.
    int* j6 = List.at(list, 0);
    assert(*j6 == 90);
    
    int* j7 = List.pop(list, mem);
    // List is now [90]
    assert(*j7 == 60);
    
    // List is now []
    int* j8 = List.pop(list, mem);
    assert(*j8 == 90);
    
    // Popping an empty list returns NULL.
    int* j9 = List.pop(list, mem);
    assert(j9 == NULL);
    assert(List.size(list) == 0);

    // notice we don't have to free or decref
    // anything other than the Memory scope.
    decref(mem); 
    printGreen("OK\n");
    return 0;
}
