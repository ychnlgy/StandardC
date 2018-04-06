#include <unistd.h>
// close

#include <stdio.h>

#include <sys/socket.h>
// AF_INET, SOCK_STREAM

#include <netinet/in.h>
// sockaddr_in

#include <arpa/inet.h>
// inet_addr

#include <string.h>

#include "TCPSocket_private.h"

TCPSocketVtable TCPSocket = {
    .new = &new_TCPSocket,
    .init = &init_TCPSocket,
    .del = &del_TCPSocket,
    
    .copy = &copy_TCPSocket,
    
    .bind = &bind_TCPSocket,
    .bindany = &bindany_TCPSocket,
    .listen = &listen_TCPSocket,
    .accept = &accept_TCPSocket,
    
    .connect = &connect_TCPSocket,
    
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
    TCPSocketObject* this = ptr;
    if (this->filedesciptor != 0)
        close(this->filedesciptor);
}

static void resetFileDescriptor(TCPSocketObject* this) {
    del_TCPSocket(this);
    this->filedesciptor = socket(AF_INET, SOCK_STREAM, 0);
    
    
    /* Copied from:
     * https://www.geeksforgeeks.org/socket-programming-cc/
     * "Socket Programming in C/C++"
     *
     * Rationale:
     *      Closing a socket only marks it to the OS for closing.
     *      Therefore if you try to bind again and the OS has not
     *      yet closed it, then you will fail to bind.
     *      This extra code allows you to successfully bind
     *      if you closed the socket.
     */
    int opt = 1;
    setsockopt(this->filedesciptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
}

static TCPSocketObject* copy_TCPSocket(TCPSocketObject* this, long filedesciptor, MemoryObject* mem) {
    TCPSocketObject* copy = Memory.make(mem, &new_TCPSocket);
    copy->filedesciptor = filedesciptor;
    copy->address = this->address;
    copy->addrlen = this->addrlen;
    // do not copy buffer
    return copy;
}

static void setTCPSocket(TCPSocketObject* this, CStr ip, long port) {
    resetFileDescriptor(this);
    
    this->address.sin_family = AF_INET;
    
    if (ip == NULL)
        this->address.sin_addr.s_addr = INADDR_ANY;
    else
        this->address.sin_addr.s_addr = inet_addr(ip);
    
    this->address.sin_port = htons(port);
}

static bool bindTCPSocket(TCPSocketObject* this, CStr ip, long port) {
    setTCPSocket(this, ip, port);
    return 0 == bind(
        this->filedesciptor,
        (struct sockaddr*) &this->address,
        sizeof(struct sockaddr_in)
    );
}

static bool bind_TCPSocket(TCPSocketObject* this, CStr ip, long port) {
    return bindTCPSocket(this, ip, port);
}

static bool bindany_TCPSocket(TCPSocketObject* this, long port) {
    return bindTCPSocket(this, NULL, port);
}

static bool listen_TCPSocket(TCPSocketObject* this, long maxClients) {
    return listen(this->filedesciptor, maxClients) == 0;
}

static TCPSocketObject* accept_TCPSocket(TCPSocketObject* this, MemoryObject* mem) {
    int newFileDescriptor = accept(
        this->filedesciptor,
        (struct sockaddr*) &this->address,
        (socklen_t*) &this->addrlen
    );
    return copy_TCPSocket(this, newFileDescriptor, mem);
}

// TODO: refactor this because it is copied from File

static void del_FileData(Ptr ptr) {
    free(((FileData*) ptr)->d);
}

static FileData* new_FileData(long n) {
    FileData* d = new(sizeof(FileData), &del_FileData);
    d->n = n;
    d->d = malloc(n+1);
    return d;
}

static FileData* allocFileData(long n, CStr data, MemoryObject* mem) {
    FileData* s = new_FileData(n);
    Memory.track(mem, s);
    long i;
    for (i=0; i<n; i++)
        s->d[i] = data[i];
    return s;
}

// the above needs to be treated

static bool connect_TCPSocket(TCPSocketObject* this, CStr ip, long port) {
    setTCPSocket(this, ip, port);
    return 0 == connect(
        this->filedesciptor,
        (struct sockaddr*) &this->address,
        this->addrlen
    );
}

static ListObject* segmentRead(TCPSocketObject* this, MemoryObject* mem, long* size) {
    MemoryObject* scope = Memory.new();
    
    ListObject* segments = Memory.make(mem, List.new);
    
    long bytesread, totalbytes = 0;
    while ((bytesread = read(this->filedesciptor, this->buffer, BUFSIZE)) == BUFSIZE) {
        totalbytes += bytesread;
        FileData* fd = allocFileData(bytesread, this->buffer, scope);
        List.push(segments, fd);
    }
    if (bytesread > 0) {
        totalbytes += bytesread;
        FileData* fd = allocFileData(bytesread, this->buffer, scope);
        List.push(segments, fd);
    }
    decref(scope);
    if (size != NULL)
        *size = totalbytes;
    return segments;
}

static FileData* read_TCPSocket(TCPSocketObject* this, MemoryObject* mem) {
    MemoryObject* scope = Memory.new();
    
    long totalbytes;
    ListObject* segments = segmentRead(this, scope, &totalbytes);
    
    FileData* alldata = new_FileData(totalbytes);
    Memory.track(mem, alldata);
    long i, j;
    long k = 0;
    for (i=0; i<List.size(segments); i++) {
        FileData* fd = List.getitem(segments, i);
        for (j=0; j<fd->n; j++)
            alldata->d[k++] = fd->d[j];
    }
    alldata->d[k] = '\0';
    alldata->n = k;
    
    decref(scope);
    return alldata;
}

static FileObject* readfile_TCPSocket(TCPSocketObject* this, MemoryObject* mem) {
    FileObject* out;
    
    MemoryObject* scope = Memory.new();
    
    ListObject* segments = segmentRead(this, scope, NULL);
    out = Memory.make(mem, File.new);
    long i;
    for (i=0; i<List.size(segments); i++) {
        FileData* fd = List.getitem(segments, i);
        File.write(out, fd->n, fd->d);
    }
    
    decref(scope);
    return out;
}

static long write_TCPSocket(TCPSocketObject* this, CStr msg) {
    if (msg == NULL)
        return 0;
    else
        return send(this->filedesciptor, msg, strlen(msg), 0);
}

static long writestr_TCPSocket(TCPSocketObject* this, StringObject* msg) {
    if (msg == NULL)
        return 0;
    else
        return send(this->filedesciptor, String.cstr(msg), String.size(msg), 0);
}

static long writefile_TCPSocket(TCPSocketObject* this, FileObject* file) {
    if (file == NULL)
        return 0;
    MemoryObject* scope = Memory.new();
    FileData* fd = File.read(file, scope);
    long result;
    if (fd == NULL) {
        result = 0;
    } else {
        result = send(this->filedesciptor, fd->d, fd->n, 0);
    }
    decref(scope);
    return result;
}
