#include "stdc/lib.h"
#include "stdc/unittest/print.h" // print in color
#include <assert.h>

/* 
 * An example demonstrating List usage:
 *  - getitem: returns the element at the specified index.
 *  - setitem : replaces the element at the specified index with the new element.
 *  - Both methods do not check boundaries,
 *    so only use them within loops to be safe.
 *  - Pay attention to returning lists from functions.
 */

List* createReverseRange(int n) {
    Memory* mem = new_Memory();
    
    List* list = mem->_->make(mem, &new_List);
    int i;
    for (i=n; i>0; i--) {
        // we want the elements to persist
        // beyond local variable scope,
        // so we allocate memory on the heap.
        int* j = mem->_->alloc(mem, sizeof(int));
        *j = i;
        list->_->push(list, j);
    }
    
    incref(list); // always incref the objects
                  // you plan to return or else
                  // decref(mem) will free them.
    decref(mem);
    return list; // the elements of list are not free'd
                 // which is good because we need to 
                 // access them later.
}

int sumList(List* list) {
    int out = 0;
    int i;
    for (i=0; i<list->_->size(list); i++) {
        // getitem does not check for range,
        // so it is only safe to use when
        // you know the indices are within bounds.
        int* j = list->_->getitem(list, i);
        out += *j;
    }
    return out;
}

void incList(List* list) {
    // returns a original list with each
    // element of the input list 
    // incremented by 1.
    int i;
    for (i=0; i<list->_->size(list); i++) {
        int* j = list->_->getitem(list, i);
        (*j)++;
        // setitem does not check for range,
        // so it is only safe to use when
        // you know the indices are within bounds.
        list->_->setitem(list, i, j);
    }
}

int main() {
    printBold("Running %s...", __FILE__);
    Memory* mem = new_Memory();
    
    List* list = createReverseRange(100);
    mem->_->track(mem, list); // track this list on
                           // local stack memory.
    
    int sum = sumList(list);
    assert(sum == 5050); // sum of 1 to 100
    
    incList(list);
    sum = sumList(list); // sum of 2 to 101
    assert(sum == 5150);
    
    decref(mem);
    printGreen("OK\n");
    return 0;
}
