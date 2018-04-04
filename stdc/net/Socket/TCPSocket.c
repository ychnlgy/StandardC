#include <unistd.h>
// close

#include <stdio.h>

#include <sys/socket.h>
// AF_INET, SOCK_STREAM

#include <netinet/in.h>
// sockaddr_in

#include <arpa/inet.h>
// inet_addr

#include <assert.h>

#include "protected.h"

static Ptr new_TCPSocket();
static void init_TCPSocket(TCPSocketObject*);
static void del_TCPSocket(Ptr);

static int bind_TCPSocket(TCPSocketObject*, CStr, long);
static int listen_TCPSocket(TCPSocketObject*, long);
static int accept_TCPSocket(TCPSocketObject*);

static FileData* read_TCPSocket(TCPSocketObject*, MemoryObject*);
static FileObject* readfile_TCPSocket(TCPSocketObject*, MemoryObject*);
static void write_TCPSocket(TCPSocketObject*, CStr);
static void writestr_TCPSocket(TCPSocketObject*, StringObject*);
static void writefile_TCPSocket(TCPSocketObject*, FileObject*);

TCPSocketVtable TCPSocket = {
    .new = &new_TCPSocket,
    .init = &init_TCPSocket,
    .del = &del_TCPSocket,
    
    .bind = &bind_TCPSocket,
    .listen = &listen_TCPSocket,
    .accept = &accept_TCPSocket,
    
    .read = &read_TCPSocket,
    .readfile = &readfile_TCPSocket,
    .write = &write_TCPSocket,
    .writestr = &writestr_TCPSocket,
    .writefile = &writefile_TCPSocket
};

static Ptr new_TCPSocket() {
    TCPSocketObject* this = new(sizeof(TCPSocketObject), &del_TCPSocket);
    init_TCPSocket(this);
    return this;
}

static void init_TCPSocket(TCPSocketObject* this) {
    this->filedesciptor = 0;
    this->addrlen = sizeof(this->address);
}

static void del_TCPSocket(Ptr ptr) {
    // do nothing.
}

static int bind_TCPSocket(TCPSocketObject* this, CStr ip, long port) {
    if (this->filedesciptor > 0)
        close(this->filedesciptor);
    
    this->filedesciptor = socket(AF_INET, SOCK_STREAM, 0);
    assert(this->filedesciptor != 0); // don't know how to test.
    
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = inet_addr(ip);
    this->address.sin_port = htons(port);
    
    int bindCode = bind(
        this->filedesciptor,
        (struct sockaddr*) &this->address,
        sizeof(struct sockaddr_in)
    );
    
    if (bindCode < 0)
        return -1;
    
    return 0;
}

static int listen_TCPSocket(TCPSocketObject* this, long maxClients) {
    return listen(this->filedesciptor, maxClients);
}

// TODO: Accept returns a filedesciptor for the new recieving socket
// but it needs to have its own buffer, same address

static int accept_TCPSocket(TCPSocketObject* this) {
    return accept(
        this->filedesciptor,
        (struct sockaddr*) &this->address,
        (socklen_t*) &this->addrlen
    );
}

/*static void del_FileData(Ptr ptr) {*/
/*    free(((FileData*) ptr)->d);*/
/*}*/

/*static FileData* new_FileData(long n) {*/
/*    FileData* d = new(sizeof(FileData), &del_FileData);*/
/*    d->n = n;*/
/*    d->d = malloc(n);*/
/*    return d;*/
/*}*/

/*static FileData* allocFileData(long n, CStr data) {*/
/*    FileData* s = new_FileData(n);*/
/*    long i;*/
/*    for (i=0; i<n; i++)*/
/*        s->d[i] = data[i];*/
/*    return s;*/
/*}*/

/*static ListObject* segmentInput(TCPSocketObject* this, MemoryObject* mem) {*/
/*    long numchars;*/
/*    while((numchars = read(*/
/*}*/

static FileData* read_TCPSocket(TCPSocketObject* this, MemoryObject* mem) {
    return NULL;
}

static FileObject* readfile_TCPSocket(TCPSocketObject* this, MemoryObject* mem) {
    return NULL;
}

static void write_TCPSocket(TCPSocketObject* this, CStr msg) {

}

static void writestr_TCPSocket(TCPSocketObject* this, StringObject* msg) {

}

static void writefile_TCPSocket(TCPSocketObject* this, FileObject* file) {

}
