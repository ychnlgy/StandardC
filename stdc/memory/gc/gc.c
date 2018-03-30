#include <stdlib.h> 
// malloc

#include "stdc/lib.h"

/*
 * new allocates the desired size with a few bits of header:
 *   1) Function pointer to its destructor
 *   2) Reference count. Starts at 1. The pointer gets freed 
 *      if reference count is 0. Negative reference counts
 *      are allowed, but be aware that using freed memory results
 *      in unpredictable behavior.
 */

// === PRIVATE ===

#define GCH_SIZE sizeof(_GCHeader)

typedef struct _GCHeader {
	Destructor destructor;
	int refcount;
} _GCHeader;

_GCHeader* _ptrToGCHeader(Ptr p) {
	return (_GCHeader*) (((char*) p) - GCH_SIZE);
}

// === PUBLIC ===

Ptr new(size_t bytes, Destructor destructor) {
	_GCHeader* gch = malloc(GCH_SIZE + bytes);
	gch->destructor = destructor;
	gch->refcount = 1;
	return ((char*) gch) + GCH_SIZE;
}

int incref(Ptr p) {
	return ++_ptrToGCHeader(p)->refcount;
}

int decref(Ptr p) {
	_GCHeader* gch = _ptrToGCHeader(p);
	int ref = --gch->refcount;
	if (ref == 0) {
		if (gch->destructor != NULL)
			gch->destructor(p);
		free(gch);
	}
	return ref;
}
