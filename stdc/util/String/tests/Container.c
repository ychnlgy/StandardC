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
    CASE("size")
        ASSERT(String.size(s1) == 12);
        ASSERT(String.size(s2) == 10);
    END
    
    CASE("contains")
        ASSERT(!String.contains(s1, s2));
        ASSERT(!String.contains(s2, s1));
        String.set(s2, "world");
        ASSERT(String.contains(s1, s2));
        ASSERT(!String.contains(s2, s1));
        
        String.set(s2, "!");
        ASSERT(String.contains(s1, s2));
        ASSERT(!String.contains(s2, s1));
        
        String.set(s2, String.cstr(s1));
        ASSERT(String.contains(s1, s2));
        ASSERT(String.contains(s2, s1));
    END
    
    CASE("empty contains")
        StringObject* s3 = Memory.make(mem, String.new);
        ASSERT(!String.contains(s3, s1));
        ASSERT(!String.contains(s3, s1));
        ASSERT(String.contains(s1, s3));
        ASSERT(String.contains(s2, s3));
    END
    
STOP
