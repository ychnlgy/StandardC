#ifndef STDC_NET_SOCKET_SOCKET
#define STDC_NET_SOCKET_SOCKET

#include "stdc/lib.h"

typedef struct TCPSocketObject TCPSocketObject;

typedef struct {
    Ptr             (*new)      ();
    void            (*init)     (TCPSocketObject*);
    void            (*del)      (Ptr);
    
    // Methods
    int             (*bind)     (TCPSocketObject*, CStr, long);
    int             (*listen)   (TCPSocketObject*, long);
    int             (*accept)   (TCPSocketObject*);
    
    // File
    FileData*       (*read)     (TCPSocketObject*, MemoryObject*);
    FileObject*     (*readfile) (TCPSocketObject*, MemoryObject*);
    void            (*write)    (TCPSocketObject*, CStr);
    void            (*writestr) (TCPSocketObject*, StringObject*);
    void            (*writefile)(TCPSocketObject*, FileObject*);
} TCPSocketVtable;

extern TCPSocketVtable TCPSocket;

#endif
