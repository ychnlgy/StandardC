#ifndef STDC_UTIL_LIST_LIST_PRIVATE
#define STDC_UTIL_LIST_LIST_PRIVATE

#include "stdc/lib.h"

// Construction/destruction
Ptr         new_List        ();
void        init_List       (ListObject*);
void        del_List        (Ptr);

// Methods
ListObject* concat_List     (ListObject*, ListObject*, MemoryObject*);

// Object interface
bool        equals_List     (ListObject*, ListObject*);

// Container interface
long        size_List       (ListObject*);
void        clear_List      (ListObject*);

// Stack interface
void        push_List       (ListObject*, Ptr);
void        pushes_List     (ListObject*, long, ...);
Ptr         pop_List        (ListObject*, MemoryObject*);
Ptr         back_List       (ListObject*);
void        extend_List     (ListObject*, ListObject*);

// Accessor interface
Ptr         getitem_List    (ListObject*, long);
void        setitem_List    (ListObject*, long, Ptr);
Ptr         at_List         (ListObject*, long);
bool        set_List        (ListObject*, long, Ptr);
ListObject* slice_List      (ListObject*, MemoryObject*, long, long);

ListVtable List = {

    // Construction/destruction
    .new        = &new_List,
    .init       = &init_List,
    .del        = &del_List,
    
    // Methods
    .concat     = &concat_List,
    
    // Object interface
    .equals     = &equals_List,
    
    // Container interface
    .size       = &size_List,
    .clear      = &clear_List,
    
    // Stack interface
    .push       = &push_List,
    .pushes     = &pushes_List,
    .pop        = &pop_List,
    .back       = &back_List,
    .extend     = &extend_List,
    
    // Accessor interface
    .getitem    = &getitem_List,
    .setitem    = &setitem_List,
    .at         = &at_List,
    .set        = &set_List,
    .slice      = &slice_List
};

#endif
