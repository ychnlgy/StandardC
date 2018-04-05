#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
long maxclients = 3;

int main() {
    MemoryObject* mem = Memory.new();

    TCPSocketObject* server = Memory.make(mem, TCPSocket.new);
    TCPSocket.bindany(server, port);
    TCPSocket.listen(server, maxclients);
    
    // The following line blocks until a client connects.
    printf("Waiting for connections...\n");
    TCPSocketObject* connectedSock = TCPSocket.accept(server, mem);
    printf("Recieved a connection!\n");
    
    // Interact with client via the new socket: connectedSock
    FileData* data = TCPSocket.read(connectedSock, mem);
    printf("Client: %s\n", data->d);
    
    TCPSocket.write(connectedSock, "hello");

    decref(mem);
    return 0;
}
