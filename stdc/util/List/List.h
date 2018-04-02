#ifndef STDC_UTIL_LIST_LIST
#define STDC_UTIL_LIST_LIST

#include "stdc/lib.h"

typedef struct ListObject ListObject;

typedef struct {

    // Construction/destruction
    Ptr         (*new)      ();
    void        (*init)     (ListObject*);
    void        (*del)      (Ptr);
    //ListObject* (*copy)     (ListObject*);
    
    // Numeric
    ListObject* (*add)      (ListObject*, ListObject*, MemoryObject*);

    // Object interface
    bool        (*equals)   (ListObject*, ListObject*);

    // Container interface
    long        (*size)     (ListObject*);
    void        (*clear)    (ListObject*);

    // Stack interface
    void        (*push)     (ListObject*, Ptr);
    void        (*pushes)   (ListObject*, long, ...);
    Ptr         (*pop)      (ListObject*, MemoryObject*);
    Ptr         (*back)     (ListObject*);
    void        (*extend)   (ListObject*, ListObject*);

    // Accessor interface
    Ptr         (*getitem)  (ListObject*, long);
    void        (*setitem)  (ListObject*, long, Ptr);
    Ptr         (*at)       (ListObject*, long);
    bool        (*set)      (ListObject*, long, Ptr);
    ListObject* (*slice)    (ListObject*, MemoryObject*, long, long);

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
