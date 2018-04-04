#ifndef STDC_FILESYS_FILE_FILE
#define STDC_FILESYS_FILE_FILE

#include "stdc/lib.h"

typedef struct FileObject FileObject;

typedef struct {
    long n; // number of elements in d
    char* d;
} FileData;

typedef struct {
    Ptr             (*new)      ();
    void            (*init)     (FileObject*);
    void            (*del)      (Ptr);
    
    CStr            (*cstr)     (FileObject*);
    
    // Methods
    void            (*name)     (FileObject*, CStr);
    void            (*namestr)  (FileObject*, StringObject*);
    void            (*namepath) (FileObject*, PathObject*);
    
    bool            (*exists)   (FileObject*);
    bool            (*readable) (FileObject*);
    bool            (*writable) (FileObject*);
    
    void            (*write)    (FileObject*, long, CStr);
    void            (*writestr) (FileObject*, StringObject*);
    FileData*       (*read)     (FileObject*, MemoryObject*);
    long            (*flush)    (FileObject*);
    ListObject*     (*segment)  (FileObject*, MemoryObject*);

} FileVtable;

extern FileVtable File;

#endif
