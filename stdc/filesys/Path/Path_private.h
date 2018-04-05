#ifndef STDC_FILESYS_PATH_PRIVATE
#define STDC_FILESYS_PATH_PRIVATE

#include "Path_protected.h"

// Helpers
static void             breakCStrPath       (ListObject*, CStr);
static void             setpath             (PathObject*, CStr, bool);
static bool             isSkipPath          (Ptr);
static ListObject*      removeBack          (ListObject*, MemoryObject*);
static ListObject*      removePathRedundancy(ListObject*, MemoryObject*);
static PathObject*      normalize           (ListObject*, bool, MemoryObject*);

// Object
static Ptr              new_Path     ();
static void             init_Path    (PathObject*);
static void             del_Path     (Ptr);

static CStr             cstr_Path   (PathObject*);
static StringObject*    str_Path    (PathObject*);
static bool             equals_Path (PathObject*, PathObject*);
static PathObject*      copy_Path   (PathObject*, MemoryObject*);

// Numeric
static PathObject*      add_Path (PathObject*, PathObject*, MemoryObject*);
static PathObject*      abs_Path (PathObject*, MemoryObject*);
static PathObject*      norm_Path(PathObject*, MemoryObject*);

// Path
static PathObject*      addcstr_Path        (PathObject*, CStr, MemoryObject*);
static bool             isfile_Path         (PathObject*);
static bool             isdir_Path          (PathObject*);
static ListObject*      listdir_Path        (PathObject*, MemoryObject*);
static void             setrel_Path         (PathObject*, CStr);
static void             setabs_Path         (PathObject*, CStr);
static void             setrelstr_Path      (PathObject*, StringObject*);
static void             setabsstr_Path      (PathObject*, StringObject*);
static PathObject*      dirname_Path        (PathObject*, MemoryObject*);
static StringObject*    basename_Path       (PathObject*);

#endif
