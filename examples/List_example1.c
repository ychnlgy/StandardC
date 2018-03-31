#include "stdc/lib.h"
#include <assert.h>

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
    Memory* mem = new_Memory();
    
    int* i1 = mem->alloc(mem, sizeof(int));
    int* i2 = mem->alloc(mem, sizeof(int));
    *i1 = 40;
    *i2 = 60;

    List* list = mem->make(mem, &new_List);
    list->push(list, i1);
    list->push(list, i2);
    // The list is now [40, 60]
    
    // List->size returns the size!
    assert(list->size(list) == 2);
    
    int* j1 = list->at(list, 0);
    assert(*j1 == 40);
    
    int* j2 = list->at(list, 1);
    assert(*j2 == 60);
    
    // Python-style negative indexing.
    int* j3 = list->at(list, -1); // -1 means back of list.
    assert(*j3 == *i2);
    
    int* j4 = list->at(list, -2); // -2 means second last item.
    assert(*j4 == *i1);
    
    // Out of range access returns NULL
    // List is now [40, 60]
    int* j5 = list->at(list, 2); // the third element does not exist.
    assert(j5 == NULL);
    
    // Elements of the array are pointers
    // to the original data.
    *i1 = 70; // Since the first element points to
              // the same block of memory as i1,
              // we can change *i1 to change 
              // element 0 of the list.
    
    // List is now [70, 60]
    assert(*j1 == 70);
    int* k1 = list->at(list, 0);
    assert(*k1 == 70); // k1 and j1 and i1 all point to the same memory.
    
    int* i3 = mem->alloc(mem, sizeof(int));
    *i3 = 90; // we want to insert 90 into position 0.
    
    // Set the 0th element to a new element.
    // List manages incref and decref for you:
    // decref is applied to the 0th element
    // incref is applied to the inserted element.
    list->set(list, 0, i3);
    // List is now [90, 60]
    assert(*j1 == 70); // the old pointer is not changed.
    
    // Here we show that the element at 0 is indeed 90.
    int* j6 = list->at(list, 0);
    assert(*j6 == 90);
    
    int* j7 = list->pop(list);
    // List is now [90]
    assert(*j7 == 60);
    mem->track(mem, j7); // stack needs to keep track of popped elements.
    
    // List is now []
    int* j8 = list->pop(list);
    assert(*j8 == 90);
    mem->track(mem, j8); // stack needs to keep track of popped elements.
    
    // Popping an empty list returns NULL.
    int* j9 = list->pop(list);
    assert(j9 == NULL);
    assert(list->size(list) == 0);

    // notice we don't have to free or decref
    // anything other than the Memory scope.
    decref(mem); 
    return 0;
}
