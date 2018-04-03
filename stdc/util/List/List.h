#ifndef STDC_UTIL_LIST_LIST
#define STDC_UTIL_LIST_LIST

#include "stdc/lib.h"

typedef struct ListObject ListObject;

typedef struct {

    // Construction/destruction
    Ptr         (*new)      ();
    void        (*init)     (ListObject*);
    void        (*del)      (Ptr);
    
    // Numeric
    ListObject* (*add)      (ListObject*, ListObject*, MemoryObject*);

    // Object
    bool        (*equals)   (ListObject*, ListObject*);
    ListObject* (*copy)     (ListObject*, MemoryObject*);

    // Container
    long        (*size)     (ListObject*);
    void        (*clear)    (ListObject*);
    bool        (*isEmpty)  (ListObject*);

    // Stack
    void        (*push)     (ListObject*, Ptr);
    void        (*pushes)   (ListObject*, long, ...);
    Ptr         (*pop)      (ListObject*, MemoryObject*);
    Ptr         (*back)     (ListObject*);
    void        (*extend)   (ListObject*, ListObject*);

    // Accessor
    Ptr         (*getitem)  (ListObject*, long);
    void        (*setitem)  (ListObject*, long, Ptr);
    Ptr         (*at)       (ListObject*, long);
    bool        (*set)      (ListObject*, long, Ptr);
    ListObject* (*slice)    (ListObject*, MemoryObject*, long, long);
    
    // Iterable
    ListObject* (*filter)   (ListObject*, FilterFunc, MemoryObject*);

    // Iteration
    // TODO: implement them!
    // iter
    // reverse
    // etc.
//	ListObject*	(*map)		(ListObject*, MapFunc);
//	ListObject*	(*filter)	(ListObject*, FilterFunc);
//	ListObject*	(*reduce)	(ListObject*, ReduceFunc);
} ListVtable;

extern ListVtable List;

#endif
