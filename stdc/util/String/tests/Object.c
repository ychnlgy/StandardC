#include "stdc/unittest.h"

#include <string.h>

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

    CASE("copy")
        StringObject* s3 = String.copy(s1, mem);
        StringObject* s4 = String.copy(s3, mem);
        ASSERT(String.size(s3) == 12);
        ASSERT(String.size(s4) == 12);
        ASSERT(String.equals(s3, s1));
        ASSERT(String.hash(s3) == String.hash(s1));
        ASSERT(String.equals(s4, s1));
        ASSERT(String.hash(s4) == String.hash(s1));

        String.set(s2, "Hello world!");
        ASSERT(String.equals(s2, s3));
        ASSERT(String.hash(s2) == String.hash(s3));
        ASSERT(String.equals(s2, s1));
        ASSERT(String.hash(s2) == String.hash(s1));
        ASSERT(String.equals(s2, s4));
        ASSERT(String.hash(s2) == String.hash(s4));

        String.set(s2, "Hello world");
        ASSERT(!(String.equals(s2, s3)));
        ASSERT(!(String.equals(s2, s1)));
        ASSERT(!(String.equals(s2, s4)));

        String.set(s3, "Superman1234");
        ASSERT(String.size(s3) == 12);
        ASSERT(String.size(s4) == 12);
        ASSERT(!String.equals(s3, s4));

    END

    CASE("get-cstr")
        ASSERT(strcmp(String.cstr(s2), String.cstr(s1)) != 0);
        String.set(s2, "Hello world!");
        ASSERT(strcmp(String.cstr(s2), String.cstr(s1)) == 0);
    END
    

STOP
