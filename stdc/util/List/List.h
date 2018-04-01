#ifndef STDC_UTIL_LIST_LIST
#define STDC_UTIL_LIST_LIST

#include "stdc/lib.h"

typedef struct ListObject ListObject;

typedef struct {

    // Construction/destruction
    Ptr     (*new)      ();
    void    (*init)     (ListObject*);
    void    (*del)      (Ptr);


    // Methods
    long    (*size)     (ListObject*);
    void    (*push)     (ListObject*, Ptr);
    Ptr     (*pop)      (ListObject*);

    /* NOTE: Accessors take long position rather than
     * the unsigned size_t because there may be times
     * where accidents happen and wierd things happen.
     */

    // Fast but unsafe accessors (does not check range)
    Ptr     (*getitem)  (ListObject*, long);
    void    (*setitem)  (ListObject*, long, Ptr);

    // Slow but safe accessors (checks for range)
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
