#ifndef STDC_UTIL_LIST_PRIVATE
#define STDC_UTIL_LIST_PRIVATE

#include "List_protected.h"

// Helpers
static void         resize   (ListObject*, size_t);
static bool         isWithin (ListObject*, long);
static long         fitWithin(ListObject*, long);

// Object
static Ptr         new_List         ();
static void        init_List        (ListObject*);
static void        del_List         (Ptr);
static bool        equals_List      (ListObject*, ListObject*);
static ListObject* copy_List        (ListObject*, MemoryObject*);

// Container
static long size_List   (ListObject*);
static void clear_List  (ListObject*);
static bool isEmpty_List(ListObject*);

// Accessor
static Ptr         getitem_List    (ListObject*, long);
static void        setitem_List    (ListObject*, long, Ptr);
static Ptr         at_List         (ListObject*, long);
static bool        set_List        (ListObject*, long, Ptr);
static ListObject* slice_List      (ListObject*, MemoryObject*, long, long);

// Stack
static void        push_List       (ListObject*, Ptr);
static void        pushes_List     (ListObject*, long, ...);
static Ptr         pop_List        (ListObject*, MemoryObject*);
static Ptr         back_List       (ListObject*);
static void        extend_List     (ListObject*, ListObject*);

// Numeric
static ListObject* concat_List (ListObject*, ListObject*, MemoryObject*);

// Iterable
static ListObject* filter_List(ListObject*, FilterFunc, MemoryObject*);

#endif
