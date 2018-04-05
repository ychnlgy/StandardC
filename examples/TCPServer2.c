#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
long maxclients = 3;

// This program sends a copy of its 
// own binary executable to the client.
CStr filename = "TCPServer2.exe";

int main() {
    MemoryObject* mem = Memory.new();
    
    // the following assumes you are executing
    // TCPServer2.exe at its directory.
    FileObject* file = Memory.make(mem, File.new);
    File.name(file, filename);

    TCPSocketObject* server = Memory.make(mem, TCPSocket.new);
    TCPSocket.bindany(server, port);
    TCPSocket.listen(server, maxclients);
    
    // The following line blocks until a client connects.
    printf("Waiting for connections...\n");
    TCPSocketObject* connectedSock = TCPSocket.accept(server, mem);
    printf("Recieved a connection!\n");
    
    // Send the file
    long bytesSent = TCPSocket.writefile(connectedSock, file);
    printf("Sent the %ld bytes of %s to the connected client.\n", bytesSent, filename);

    decref(mem);
    return 0;
}
