#include "stdc/lib.h"
#include "stdc/unittest/print.h" // print in color
#include <assert.h>

/* 
 * An example demonstrating List usage:
 *  - getitem: appends an element to the back of the list.
 *  - setitem : removes and returns the element at the back of the list.
 *  - Pay attention to returning lists from functions.
 */

List* createReverseRange(int n) {
    Memory* mem = new_Memory();
    
    List* list = mem->make(mem, &new_List);
    int i;
    for (i=n; i>0; i--) {
        // we want the elements to persist
        // beyond local variable scope,
        // so we allocate memory on the heap.
        int* j = mem->alloc(mem, sizeof(int));
        *j = i;
        list->push(list, j);
    }
    
    incref(list); // always incref the objects
                  // you plan to return or else
                  // decref(mem) will free them.
    
    // NOTE: You can ignore the following comments
    // if you are only interested in how to use the functions.
    
    // If you would like to have a deeper understanding
    // of why no memory leak or invalid memory reads are
    // made, then read on.
    
    // Notice how the memory of the elements
    // in list were allocated by Memory.
    
    // When they are pushed onto the list,
    // List automatically increfs them.
    
    // decref(mem) results in a refcount of 0,
    // so the Memory will be deleted, causing decref of the
    // list it allocated at the beginning of this function.
    
    // Deletion of the list causes decref of all elements
    // within the list, resulting in the deallocation
    // of all memory allocated in this Memory scope.
    
    // But since the refcount of the list is 2, 
    // after decref it will become 1 and not deleted.
    // Therefore decref(mem) does not free
    // the elements of the list and we are free to
    // access them later.
    decref(mem);
    return list; // the elements of list are not free'd
                 // which is good because we need to 
                 // access them later.
}

int sumList(List* list) {
    int out = 0;
    int i;
    for (i=0; i<list->size(list); i++) {
        // getitem does not check for range,
        // so it is only safe to use when
        // you know the indices are within bounds.
        int* j = list->getitem(list, i);
        out += *j;
    }
    return out;
}

void incList(List* list) {
    // returns a original list with each
    // element of the input list 
    // incremented by 1.
    int i;
    for (i=0; i<list->size(list); i++) {
        int* j = list->getitem(list, i);
        (*j)++;
        // setitem does not check for range,
        // so it is only safe to use when
        // you know the indices are within bounds.
        list->setitem(list, i, j);
    }
}

int main() {
    Memory* mem = new_Memory();
    
    List* list = createReverseRange(100);
    mem->track(mem, list); // track this list on
                           // local stack memory.
    
    int sum = sumList(list);
    printBold("The sum of 1 to 100 is: ");
    printGreen("%d\n", sum);
    
    incList(list);
    sum = sumList(list);
    printBold("The sum of 2 to 101 is: ");
    printGreen("%d\n", sum);
    
    decref(mem);
    return 0;
}
