#include "stdc/lib.h"
#include "stdc/unittest/print.h" // for color printing.

typedef struct SuperExpensiveStruct {
	int result;
	// assume to contain a huge number of fields.
	// i.e. would be expensive to copy each time.
} SuperExpensiveStruct;

// Returns the sum of the list.
SuperExpensiveStruct* sum(List*);

// Returns the sum of the three integers.
int simpleSum(int* a, int* b, int* c);

int main() {
	Memory* mem = new_Memory();
	
	// Allocate a bunch of integers that do not
	// need the programmer to remember to free.
	int* i1 = mem->alloc(mem, sizeof(int)); *i1 = 20;
	int* i2 = mem->alloc(mem, sizeof(int)); *i2 = 40;
	int* i3 = mem->alloc(mem, sizeof(int)); *i3 = 60;
	
	int result = simpleSum(i1, i2, i3);
	printBold("The sum of 20, 40 and 60 is: ");
	printGreen("%d\n", result);
	
	// Classes have special constructors and destructors.
	// List is such a class and it is allocated via new_List.
	// Use Memory.make(this, &constructor) to make these classes.
	List* numlist = mem->make(mem, &new_List);
	// numlist is currently empty []
	
	SuperExpensiveStruct* ses;
	
	ses = sum(numlist);
	
	// Since ses is a dynamically allocated pointer,
	// we want the current memory stack to track it
	// so we won't have to remember to decref it.
	mem->track(mem, ses);
	
	printBold("The sum of [] is: ");
	printGreen("%d\n", ses->result);
	
	// Lists automatically incref any items pushed to it.
	numlist->push(numlist, i1);
	numlist->push(numlist, i2);
	numlist->push(numlist, i3);
	// numlist is currently [20, 40, 60].
	
	ses = sum(numlist);
	
	// This ses is a different pointer from the previous one.
	// The memory stack should track it.
	mem->track(mem, ses);
	
	printBold("The sum of [20, 40, 60] is: ");
	printGreen("%d\n", ses->result);
	
	// List.set(this, i, ptr) decrefs the object
	// at the set position i if it is not NULL, and
	// increfs the new ptr set to that position.
	numlist->set(numlist, 0, i3);
	// numlist is currently [60, 40, 60]
	
	ses = sum(numlist);
	mem->track(mem, ses);
	
	printBold("The sum of [60, 40, 60] is: ");
	printGreen("%d\n", ses->result);
	
	// python style negative indexing also works
	numlist->set(numlist, -1, i1);
	// numlist is currently [60, 40, 20]
	
	ses = sum(numlist);
	mem->track(mem, ses);
	
	printBold("The sum of [60, 40, 20] is: ");
	printGreen("%d\n", ses->result);
	
	// since the different ses were all tracked,
	// we don't decref them here.
	decref(mem);
}

SuperExpensiveStruct* sum(List* numlist) {
	// allocate stack for each function body.
	// remember to deallocate it with decref at the end!
	Memory* mem = new_Memory();
	
	SuperExpensiveStruct* ses = mem->alloc(
		mem, 
		sizeof(SuperExpensiveStruct)
	);
	
	// sum elements of the array.
	ses->result = 0;
	long i;
	for (i=0; i<numlist->size(numlist); i++) {
		// List.getitem(this, i) returns a pointer
		// to the original data.
		int* k = numlist->getitem(numlist, i);
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
