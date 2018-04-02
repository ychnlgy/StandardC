#include "stdc/unittest.h"

StringObject* s1;
StringObject* s2;
MemoryObject* mem;

SETUP {
    mem = Memory.new();
    s1 = Memory.make(mem, String.new);
    String.set(s1, "Hello world!");
    s2 = Memory.make(mem, String.new);
    String.set(s2, "Evil bunny");
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("hash")
        long size = 10;
        long hash1 = MOD(String.hash(s1), size);
        long hash2 = MOD(String.hash(s2), size);
        
        StringObject* s3 = Memory.make(mem, String.new);
        long hash3 = MOD(String.hash(s3), size);
        
        ASSERT(hash1 != hash2);
        ASSERT(hash2 != hash3);
        ASSERT(hash3 != hash1);
    END

STOP
