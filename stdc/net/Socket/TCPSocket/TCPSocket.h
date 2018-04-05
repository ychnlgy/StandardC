#ifndef STDC_NET_SOCKET_SOCKET
#define STDC_NET_SOCKET_SOCKET

#include "stdc/lib.h"

typedef struct TCPSocketObject TCPSocketObject;

typedef struct {
    Ptr                 (*new)      ();
    void                (*init)     (TCPSocketObject*);
    void                (*del)      (Ptr);
    TCPSocketObject*    (*copy)     (TCPSocketObject*, int, MemoryObject*);
    
    // Server methods
    bool                (*bind)     (TCPSocketObject*, CStr, long);
    bool                (*bindany)  (TCPSocketObject*, long);
    bool                (*listen)   (TCPSocketObject*, long);
    TCPSocketObject*    (*accept)   (TCPSocketObject*, MemoryObject*);
    
    // Client methods
    bool                (*connect)  (TCPSocketObject*, CStr, long);
    
    // File
    FileData*           (*read)     (TCPSocketObject*, MemoryObject*);
    FileObject*         (*readfile) (TCPSocketObject*, MemoryObject*);
    long                (*write)    (TCPSocketObject*, CStr);
    long                (*writestr) (TCPSocketObject*, StringObject*);
    long                (*writefile)(TCPSocketObject*, FileObject*);
} TCPSocketVtable;

extern TCPSocketVtable TCPSocket;

#endif
