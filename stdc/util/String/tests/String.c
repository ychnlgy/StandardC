#include <string.h>

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

    CASE("format")
        String.set(s1, "%d - %d + %d = %s");
        
        StringObject* s3 = String.format(s1, mem, 12, 3, 2000, "Answer");
        
        int d = strlen(String.cstr(s3));
        ASSERT(String.size(s3) == d);
        
        StringObject* s4 = Memory.make(mem, String.new);
        String.set(s4, "12 - 3 + 2000 = Answer");
        
        ASSERT(String.equals(s4, s3));
        ASSERT(String.hash(s3) == String.hash(s4));
        ASSERT(!String.equals(s4, s1));
        ASSERT(!String.equals(s3, s1));
        ASSERT(!String.equals(s4, s2));
        ASSERT(!String.equals(s3, s2));
    END

    CASE("startswith-endswith")
        StringObject* s3 = Memory.make(mem, String.new);
        String.set(s3, "Hello");
        ASSERT(String.startswith(s1, s3));
        ASSERT(!String.startswith(s3, s1));
        ASSERT(!String.startswith(s2, s3));
        ASSERT(!String.endswith(s1, s3));
        ASSERT(!String.endswith(s2, s3));
        ASSERT(!String.endswith(s3, s1));
        
        String.set(s3, "world!");
        ASSERT(!String.startswith(s1, s3));
        ASSERT(!String.startswith(s3, s1));
        ASSERT(!String.startswith(s2, s3));
        ASSERT(String.endswith(s1, s3));
        ASSERT(!String.endswith(s2, s3));
        ASSERT(!String.endswith(s3, s1));
        
        String.set(s3, "!");
        ASSERT(!String.startswith(s1, s3));
        ASSERT(!String.startswith(s3, s1));
        ASSERT(!String.startswith(s2, s3));
        ASSERT(String.endswith(s1, s3));
        ASSERT(!String.endswith(s2, s3));
        ASSERT(!String.endswith(s3, s1));
        
        String.set(s3, "E");
        ASSERT(!String.startswith(s1, s3));
        ASSERT(!String.startswith(s3, s1));
        ASSERT(String.startswith(s2, s3));
        ASSERT(!String.endswith(s1, s3));
        ASSERT(!String.endswith(s2, s3));
        ASSERT(!String.endswith(s3, s1));
        
        String.set(s3, "!");
        ASSERT(!String.startswith(s1, s3));
        ASSERT(!String.startswith(s3, s1));
        ASSERT(!String.startswith(s2, s3));
        ASSERT(String.endswith(s1, s3));
        ASSERT(!String.endswith(s2, s3));
        ASSERT(!String.endswith(s3, s1));
        
        String.set(s3, "Hello world!");
        ASSERT(String.startswith(s1, s3));
        ASSERT(String.startswith(s3, s1));
        ASSERT(!String.startswith(s2, s3));
        ASSERT(String.endswith(s1, s3));
        ASSERT(!String.endswith(s2, s3));
        ASSERT(String.endswith(s3, s1));
    END
    
    CASE("startswith-endswith empty")
        StringObject* s3 = Memory.make(mem, String.new);
        StringObject* s4 = Memory.make(mem, String.new);
        ASSERT(String.startswith(s1, s3));
        ASSERT(!String.startswith(s3, s1));
        ASSERT(String.startswith(s2, s3));
        ASSERT(String.endswith(s1, s3));
        ASSERT(String.endswith(s2, s3));
        ASSERT(!String.endswith(s3, s1));
        ASSERT(String.startswith(s3, s4));
        ASSERT(String.endswith(s3, s4));
        ASSERT(String.startswith(s4, s3));
        ASSERT(String.endswith(s4, s3));
    END

STOP
