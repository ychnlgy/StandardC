#ifndef STDC_FILESYS_FILE_FILE
#define STDC_FILESYS_FILE_FILE

typedef struct FileObject FileObject;

typedef struct {
    Ptr             (*new)      ();
    void            (*init)     (FileObject*);
    void            (*del)      (Ptr);
    
    // Methods
    void            (*name)     (FileObject*, CStr);
    void            (*namestr)  (FileObject*, StringObject*);
    
    bool            (*exists)   (FileObject*);
    bool            (*readable) (FileObject*);
    bool            (*writable) (FileObject*);
    
    void            (*write)    (FileObject*, CStr);
    void            (*writestr) (FileObject*, StringObject*);
    StringObject*   (*read)     (FileObject*, MemoryObject*);

} FileVtable;

extern FileVtable File;

#endif
