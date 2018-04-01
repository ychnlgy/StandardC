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
    CASE("size")
        ASSERT(String.size(s1) == 12);
        ASSERT(String.size(s2) == 10);
    END

    CASE("re-set")
        String.set(s1, "No memory leaks!");
        ASSERT(String.size(s1) == 16);
        String.set(s1, "Half");
        ASSERT(!(String.equals(s1, s2)));
    
        StringObject* s3 = Memory.make(mem, String.new);
        String.set(s3, "Half");
        ASSERT(String.equals(s1, s3));
    END

    CASE("copy")
        StringObject* s3 = String.copy(s1);
        Memory.track(mem, s3);
        StringObject* s4 = String.copy(s3);
        Memory.track(mem, s4);
        ASSERT(String.size(s3) == 12);
        ASSERT(String.size(s4) == 12);
        ASSERT(String.equals(s3, s1));
        ASSERT(String.equals(s4, s1));

        String.set(s2, "Hello world!");
        ASSERT(String.equals(s2, s3));
        ASSERT(String.equals(s2, s1));
        ASSERT(String.equals(s2, s4));

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
    
    CASE("format")
        String.set(s1, "%d - %d + %d = %s");
        
        StringObject* s3 = String.format(s1, 12, 3, 2000, "Answer");
        Memory.track(mem, s3);
        
        int d = strlen(String.cstr(s3));
        ASSERT(String.size(s3) == d);
        
        StringObject* s4 = Memory.make(mem, String.new);
        String.set(s4, "12 - 3 + 2000 = Answer");
        
        ASSERT(String.equals(s4, s3));
        ASSERT(!String.equals(s4, s1));
        ASSERT(!String.equals(s3, s1));
        ASSERT(!String.equals(s4, s2));
        ASSERT(!String.equals(s3, s2));
    END

STOP
