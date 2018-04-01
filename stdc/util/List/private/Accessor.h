#ifdef STDC_UTIL_LIST_PRIVATE

static Ptr         getitem_List    (ListObject*, long);
static void        setitem_List    (ListObject*, long, Ptr);
static Ptr         at_List         (ListObject*, long);
static bool        set_List        (ListObject*, long, Ptr);
static ListObject* slice_List      (ListObject*, MemoryObject*, long, long);

#endif
