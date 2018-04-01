#ifndef STDC_UTIL_LIST_LIST
#define STDC_UTIL_LIST_LIST

#include "stdc/lib.h"

typedef struct ListObject ListObject;

typedef struct {

    // Construction/destruction
    Ptr     (*new)      ();
    void    (*init)     (ListObject*);
    void    (*del)      (Ptr);

    // Container interface
    long    (*size)     (ListObject*);

    // Stack interface
    void    (*push)     (ListObject*, Ptr);
    Ptr     (*pop)      (ListObject*);

    // Accessor interface
    Ptr     (*getitem)  (ListObject*, long);
    void    (*setitem)  (ListObject*, long, Ptr);
    Ptr     (*at)       (ListObject*, long);
    bool    (*set)      (ListObject*, long, Ptr);

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
