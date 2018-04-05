#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
CStr ip = "127.0.0.1";
CStr outfile = "temp.exe";

int main() {
    MemoryObject* mem = Memory.new();
    
    TCPSocketObject* client = Memory.make(mem, TCPSocket.new);
    TCPSocket.connect(client, ip, port);

    FileObject* data = TCPSocket.readfile(client, mem);
    printf("Server sent a file!\n");
    
    // Save the file
    File.name(data, outfile);
    long bytes = File.flush(data);
    printf("Saved the new file at \"%s\" (%ld bytes).\n", outfile, bytes);
    
    decref(mem);
    return 0;
}
