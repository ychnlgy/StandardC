#ifdef STDC_FILESYS_PATH_PRIVATE

static bool         isfile_Path       (PathObject*);
static bool         isdir_Path        (PathObject*);
static ListObject*  listdir_Path      (PathObject*, MemoryObject*);
static void         setrel_Path       (PathObject*, CStr);
static void         setabs_Path       (PathObject*, CStr);
static void         setrelstr_Path    (PathObject*, StringObject*);
static void         setabsstr_Path    (PathObject*, StringObject*);

#endif
