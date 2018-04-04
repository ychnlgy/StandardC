#include "stdc/unittest.h"

MemoryObject* mem;
TCPSocketObject* sock1;
TCPSocketObject* sock2;

SETUP {
    mem = Memory.new();
    sock1 = Memory.make(mem, TCPSocket.new);
    sock2 = Memory.make(mem, TCPSocket.new);
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("constructor")
        ASSERT(TCPSocket.bind(sock1, "127.0.0.1", 8080) == 0);
        ASSERT(TCPSocket.bind(sock1, "100.0.0.1", 8080) == -1);
    END
    
    CASE("copy")
        
    END

STOP
