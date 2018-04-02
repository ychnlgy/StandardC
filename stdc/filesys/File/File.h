#ifndef STDC_FILESYS_FILE_FILE
#define STDC_FILESYS_FILE_FILE

typedef struct FileObject FileObject;

typedef struct {
    Ptr     (*new)      ();
    void    (*init)     (FileObject*);
    void    (*del)      (Ptr);
    
    void    (*set)      
    
    
    bool    (*exists)   

} FileVtable;

extern FileVtable File;

#endif
