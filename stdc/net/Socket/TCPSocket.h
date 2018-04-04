#ifndef STDC_NET_SOCKET_SOCKET
#define STDC_NET_SOCKET_SOCKET

#include "stdc/lib.h"

typedef struct TCPSocketObject TCPSocketObject;

typedef struct {
    Ptr                 (*new)      ();
    void                (*init)     (TCPSocketObject*);
    void                (*del)      (Ptr);
    TCPSocketObject*    (*copy)     (TCPSocketObject*, int, MemoryObject*);
    
    // Methods
    int                 (*bind)     (TCPSocketObject*, CStr, long);
    int                 (*listen)   (TCPSocketObject*, long);
    TCPSocketObject*    (*accept)   (TCPSocketObject*, MemoryObject*);
    
    // File
    FileData*           (*read)     (TCPSocketObject*, MemoryObject*);
    FileObject*         (*readfile) (TCPSocketObject*, MemoryObject*);
    int                 (*write)    (TCPSocketObject*, CStr);
    int                 (*writestr) (TCPSocketObject*, StringObject*);
    int                 (*writefile)(TCPSocketObject*, FileObject*);
} TCPSocketVtable;

extern TCPSocketVtable TCPSocket;

#endif
