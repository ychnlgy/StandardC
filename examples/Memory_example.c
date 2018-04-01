#include "stdc/lib.h"
#include "stdc/unittest/print.h" // for color printing.
#include <assert.h>

/*
 * An example demonstrating Memory usage:
 *  - track: let Memory know that it is responsible for a particular pointer.
 *  - alloc: allocate a number of bytes from this Memory scope.
 *  - make : construct objects that this Memory scope knows about.
 *
 * The purpose of Memory is to reduce free/decref calls by the coder.
 * Simply make a new Memory scope with Memory.new() at the beginning
 * of the scope and call decref on the memory object to call decref on
 * all the memory blocks it is responsible for.
 */

typedef struct SuperExpensiveStruct {
	int result;
	// assume to contain a huge number of fields.
	// i.e. would be expensive to copy each time.
} SuperExpensiveStruct;

// Returns the sum of the list.
SuperExpensiveStruct* sum(ListObject*);

// Returns the sum of the three integers.
int simpleSum(int* a, int* b, int* c);

int main() {
    printBold("Running %s...", __FILE__);
    MemoryObject* mem = Memory.new();

    // Allocate a bunch of integers that do not
    // need the programmer to remember to free.
    int* i1 = Memory.alloc(mem, sizeof(int)); *i1 = 20;
    int* i2 = Memory.alloc(mem, sizeof(int)); *i2 = 40;
    int* i3 = Memory.alloc(mem, sizeof(int)); *i3 = 60;

    int result = simpleSum(i1, i2, i3);
    assert(result == 120);

    // Classes have special constructors and destructors.
    // List is such a class and it is allocated via new_List.
    // Use Memory.make(this, &constructor) to make these classes.
    ListObject* numlist = Memory.make(mem, List.new);
    // numlist is currently empty []

    SuperExpensiveStruct* ses;

    ses = sum(numlist);

    // Since ses is a dynamically allocated pointer,
    // we want the current memory stack to track it
    // so we won't have to remember to decref it.
    Memory.track(mem, ses);
    
    assert(ses->result == 0);

    // Lists automatically incref any items pushed to it.
    List.push(numlist, i1);
    List.push(numlist, i2);
    List.push(numlist, i3);
    // numlist is currently [20, 40, 60].

    ses = sum(numlist);

    // This ses is a different pointer from the previous one.
    // The memory stack should track it.
    Memory.track(mem, ses);

    assert(ses->result == 120);

    // List.set(this, i, ptr) decrefs the object
    // at the set position i if it is not NULL, and
    // increfs the new ptr set to that position.
    List.set(numlist, 0, i3);
    // numlist is currently [60, 40, 60]

    ses = sum(numlist);
    Memory.track(mem, ses);

    assert(ses->result == 160);

    // python style negative indexing also works
    List.set(numlist, -1, i1);
    // numlist is currently [60, 40, 20]

    ses = sum(numlist);
    Memory.track(mem, ses);

    assert(ses->result == 120);

    // since the different ses were all tracked,
    // we don't decref them here.
    decref(mem);
    
    printGreen("OK\n");
    return 0;
}

SuperExpensiveStruct* sum(ListObject* numlist) {
    // allocate stack for each function body.
    // remember to deallocate it with decref at the end!
    MemoryObject* mem = Memory.new();

    SuperExpensiveStruct* ses = Memory.alloc(
        mem, 
        sizeof(SuperExpensiveStruct)
    );

    // sum elements of the array.
    ses->result = 0;
    long i;
    for (i=0; i<List.size(numlist); i++) {
        // List.getitem(this, i) returns a pointer
        // to the original data.
        int* k = List.getitem(numlist, i);
        ses->result += *k;
    }

    // allow the stack-allocated object
    // to survive after the stack is deallocated.
    incref(ses);

    // deallocate the memory stack
    decref(mem);
    return ses;
}

int simpleSum(int* a, int* b, int* c) {
    // You do not need to allocate stack
    // memory if not needed.
    return *a + *b + *c;
}
