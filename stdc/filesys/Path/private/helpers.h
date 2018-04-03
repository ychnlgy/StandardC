#ifdef STDC_FILESYS_PATH_PRIVATE

static void         breakCStrPath       (ListObject*, CStr);
static void         setpath             (PathObject*, CStr, bool);
static bool         isSkipPath          (Ptr);
static ListObject*  removeBack          (ListObject*, MemoryObject*);
static ListObject*  removePathRedundancy(ListObject*, MemoryObject*);

#endif
