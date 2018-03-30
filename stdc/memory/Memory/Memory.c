#include "stdc/lib.h"
#include "Memory_protected.h"
#include "stdc/util/List/List_protected.h"

// === PUBLIC METHODS ===

void del_Memory(Ptr this) {
	List* super = this;
	long i;
	for (i=0; i<super->size(super); i++)
		decref(super->getitem(super, i));
	del_List(super);
}

void init_Memory(Memory* this) {
	init_List((List*) this);
	
	this->track		= &track_Memory;
	this->alloc		= &alloc_Memory;
	this->make		= &make_Memory;
}

void* new_Memory() {
	Memory* this = new(sizeof(Memory), &del_Memory);
	init_Memory(this);
	return this;
}

void track_Memory(Memory* this, Ptr ptr) {
	if (ptr != NULL)
		this->super.push((List*) this, ptr);
}

Ptr alloc_Memory(Memory* this, size_t typesize) {
	Ptr ptr = new(typesize, NULL);
	track_Memory(this, ptr);
	return ptr;
}

Ptr make_Memory(Memory* this, Maker maker) {
	Ptr ptr = maker();
	track_Memory(this, ptr);
	return ptr;
}
