#ifndef STDC_NET_SOCKET_TCPSOCKET_PRIVATE
#define STDC_NET_SOCKET_TCPSOCKET_PRIVATE

#include "TCPSocket_protected.h"

static Ptr new_TCPSocket();
static void init_TCPSocket(TCPSocketObject*);
static void del_TCPSocket(Ptr);

static TCPSocketObject* copy_TCPSocket(TCPSocketObject*, int, MemoryObject*);

static bool bind_TCPSocket(TCPSocketObject*, CStr, long);
static bool bindany_TCPSocket(TCPSocketObject*, long);
static bool listen_TCPSocket(TCPSocketObject*, long);
static TCPSocketObject* accept_TCPSocket(TCPSocketObject*, MemoryObject*);

static bool connect_TCPSocket(TCPSocketObject*, CStr, long);

static FileData* read_TCPSocket(TCPSocketObject*, MemoryObject*);
static FileObject* readfile_TCPSocket(TCPSocketObject*, MemoryObject*);
static long write_TCPSocket(TCPSocketObject*, CStr);
static long writestr_TCPSocket(TCPSocketObject*, StringObject*);
static long writefile_TCPSocket(TCPSocketObject*, FileObject*);

#endif
