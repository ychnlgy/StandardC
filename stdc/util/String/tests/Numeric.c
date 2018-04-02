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

    CASE("add")
        StringObject* space = Memory.make(mem, String.new);
        String.set(space, " ");
        StringObject* s3 = String.add(s1, space, mem);
        StringObject* s4 = String.add(s3, s2, mem);
        
        String.set(s3, "Hello world! Evil bunny");
        ASSERT(String.equals(s3, s4));
        ASSERT(String.hash(s3) == String.hash(s4));
        ASSERT(!String.equals(s1, s4));
    END
    
    CASE("empty add")
        StringObject* mt1 = Memory.make(mem, String.new);
        StringObject* mt2 = Memory.make(mem, String.new);
        
        StringObject* mt3 = String.add(mt1, mt2, mem);
        ASSERT(String.size(mt3) == 0);
    END

STOP
