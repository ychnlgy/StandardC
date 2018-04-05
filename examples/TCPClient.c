#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
CStr ip = "127.0.0.1";

int main() {
    MemoryObject* mem = Memory.new();
    
    TCPSocketObject* client = Memory.make(mem, TCPSocket.new);
    TCPSocket.connect(client, ip, port);
    
    // Interact with server
    TCPSocket.write(client, "my name is Client");

    FileData* data = TCPSocket.read(client, mem);
    printf("Server: %s\n", data->d);
    
    decref(mem);
    return 0;
}
