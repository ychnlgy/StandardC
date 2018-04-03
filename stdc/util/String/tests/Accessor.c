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

    CASE("set empty")
        String.set(s1, "");
        ASSERT(String.size(s1) == 0);
        String.set(s1, NULL);
        ASSERT(String.size(s1) == 0);
    END

    CASE("re-set")
        String.set(s1, "No memory leaks!");
        ASSERT(String.size(s1) == 16);
        String.set(s1, "Half");
        ASSERT(!(String.equals(s1, s2)));
    
        StringObject* s3 = Memory.make(mem, String.new);
        String.set(s3, "Half");
        ASSERT(String.equals(s1, s3));
        ASSERT(String.hash(s1) == String.hash(s3));
    END
    
    CASE("getitem-at")
        ASSERT(*String.getitem(s1, 0) == 'H');
        ASSERT(*String.at(s1, 0) == 'H');
        ASSERT(*String.getitem(s1, 4) == 'o');
        ASSERT(*String.at(s1, 4) == 'o');
        ASSERT(*String.getitem(s1, 5) == ' ');
        ASSERT(*String.at(s1, 5) == ' ');
        ASSERT(String.at(s1, 12) == NULL);
        ASSERT(*String.at(s1, -1) == '!');
    END
    
    CASE("slice")
        StringObject* substr1 = String.slice(s1, 0, 5, mem);
        ASSERT(!String.equals(substr1, s1));
        StringObject* match1 = Memory.make(mem, String.new);
        String.set(match1, "Hello");
        ASSERT(String.equals(match1, substr1));
        ASSERT(String.hash(match1) == String.hash(substr1));
        ASSERT(!String.equals(match1, s1));
        
        substr1 = String.slice(s1, 0, String.size(s1), mem);
        ASSERT(String.equals(s1, substr1));
        ASSERT(String.hash(s1) == String.hash(substr1));
        ASSERT(!String.equals(s1, match1));
    END
    
    CASE("NULL slice")
        StringObject* substr = String.slice(s1, -1, 5, mem);
        ASSERT(substr == NULL);
        substr = String.slice(s1, 0, String.size(s1)+1, mem);
        ASSERT(substr == NULL);
        substr = String.slice(s1, 5, 0, mem);
        ASSERT(substr == NULL);
    END
    
    CASE("Empty slice")
        StringObject* substr = String.slice(s1, 0, 0, mem);
        ASSERT(String.size(substr) == 0);
        long size = String.size(s1);
        substr = String.slice(s1, size, size, mem);
        ASSERT(String.size(substr) == 0);
    END
    
    CASE("Index string")
        ASSERT(String.index(s1, s2) == -1);
        ASSERT(String.index(s2, s1) == -1);
        String.set(s2, "world");
        ASSERT(String.index(s1, s2) == 6);
        ASSERT(String.index(s2, s1) == -1);
        
        String.set(s2, "!");
        ASSERT(String.index(s1, s2) == 11);
        ASSERT(String.index(s2, s1) == -1);
        
        String.set(s2, String.cstr(s1));
        ASSERT(String.index(s1, s2) == 0);
        ASSERT(String.index(s2, s1) == 0);
    END
    
    CASE("empty index")
        StringObject* s3 = Memory.make(mem, String.new);
        ASSERT(String.index(s3, s1) == -1);
        ASSERT(String.index(s3, s1) == -1);
        ASSERT(String.index(s1, s3) == 0);
        ASSERT(String.index(s2, s3) == 0);
    END

STOP
