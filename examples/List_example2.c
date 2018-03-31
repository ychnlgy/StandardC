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
    decref(mem);
    return list;
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
