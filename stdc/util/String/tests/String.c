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
    
    CASE("rstrip")
        String.set(s1, "    ");
        StringObject* s3 = String.rstrip(s1, mem);
        ASSERT(String.size(s3) == 0);
        String.set(s1, " \t\r\nHello \t\r\n");
        String.set(s2, " \t\r\nHello");
        s3 = String.rstrip(s1, mem);
        ASSERT(String.equals(s3, s2));
        ASSERT(!String.equals(s3, s1));
        ASSERT(!String.equals(s1, s2));
    END
    
    CASE("no rstrip")
        s2 = String.rstrip(s1, mem);
        ASSERT(String.equals(s2, s1));
    END
    
    CASE("lstrip")
        String.set(s1, "    ");
        StringObject* s3 = String.lstrip(s1, mem);
        ASSERT(String.size(s3) == 0);
        String.set(s1, " \t\r\nHello \t ");
        String.set(s2, "Hello \t ");
        s3 = String.lstrip(s1, mem);
        ASSERT(String.equals(s3, s2));
        ASSERT(!String.equals(s3, s1));
        ASSERT(!String.equals(s1, s2));
    END
    
    CASE("no lstrip")
        s2 = String.lstrip(s1, mem);
        ASSERT(String.equals(s2, s1));
    END
    
    CASE("strip")
        String.set(s1, "    ");
        StringObject* s3 = String.strip(s1, mem);
        ASSERT(String.size(s3) == 0);
        String.set(s1, " \t\r\nHello \t ");
        String.set(s2, "Hello");
        s3 = String.strip(s1, mem);
        ASSERT(String.equals(s3, s2));
        ASSERT(!String.equals(s3, s1));
        ASSERT(!String.equals(s1, s2));
    END
    
    CASE("no strip")
        s2 = String.strip(s1, mem);
        ASSERT(String.equals(s2, s1));
    END
    
    CASE("split")
        String.set(s1, "Hello world evil bunny.");
        ListObject* ss1 = String.split(s1, ' ', mem);
        ASSERT(List.size(ss1) == 4);
        StringObject* part1 = List.getitem(ss1, 0);
        StringObject* part2 = List.getitem(ss1, 1);
        StringObject* part3 = List.getitem(ss1, 2);
        StringObject* part4 = List.getitem(ss1, 3);
        
        String.set(s1, "Hello");
        ASSERT(String.equals(s1, part1));
        
        String.set(s1, "world");
        ASSERT(String.equals(s1, part2));
        
        String.set(s1, "evil");
        ASSERT(String.equals(s1, part3));
        
        String.set(s1, "bunny.");
        ASSERT(String.equals(s1, part4));
    END
    
    CASE("split ends")
        String.set(s1, " Hello world evil bunny. ");
        ListObject* ss1 = String.split(s1, ' ', mem);
        ASSERT(List.size(ss1) == 6);
        StringObject* part0 = List.getitem(ss1, 0);
        StringObject* part1 = List.getitem(ss1, 1);
        StringObject* part2 = List.getitem(ss1, 2);
        StringObject* part3 = List.getitem(ss1, 3);
        StringObject* part4 = List.getitem(ss1, 4);
        StringObject* part5 = List.getitem(ss1, 5);
        
        String.set(s1, "");
        ASSERT(String.equals(s1, part0));
        
        String.set(s1, "Hello");
        ASSERT(String.equals(s1, part1));
        
        String.set(s1, "world");
        ASSERT(String.equals(s1, part2));
        
        String.set(s1, "evil");
        ASSERT(String.equals(s1, part3));
        
        String.set(s1, "bunny.");
        ASSERT(String.equals(s1, part4));
        
        String.set(s1, "");
        ASSERT(String.equals(s1, part5));
    END
    
    CASE("no split")
        String.set(s1, "cannotsplit");
        ListObject* ss1 = String.split(s1, ' ', mem);
        ASSERT(List.size(ss1) == 1);
    END
    
    CASE("splitstr")
        String.set(s1, "Hello world world bunny.");
        String.set(s2, "world ");
        ListObject* ss1 = String.splitstr(s1, s2, mem);
        ASSERT(List.size(ss1) == 3);
        StringObject* part1 = List.getitem(ss1, 0);
        StringObject* part2 = List.getitem(ss1, 1);
        StringObject* part3 = List.getitem(ss1, 2);
        
        String.set(s1, "Hello ");
        ASSERT(String.equals(s1, part1));
        
        String.set(s1, "");
        ASSERT(String.equals(s1, part2));
        
        String.set(s1, "bunny.");
        ASSERT(String.equals(s1, part3));

    END
    
    CASE("splitstr ends")
        String.set(s1, "world Hello world world bunny. world ");
        String.set(s2, "world ");
        ListObject* ss1 = String.splitstr(s1, s2, mem);
        ASSERT(List.size(ss1) == 5);
        StringObject* part0 = List.getitem(ss1, 0);
        StringObject* part1 = List.getitem(ss1, 1);
        StringObject* part2 = List.getitem(ss1, 2);
        StringObject* part3 = List.getitem(ss1, 3);
        StringObject* part4 = List.getitem(ss1, 4);
        
        String.set(s1, "");
        ASSERT(String.equals(s1, part0));
        
        String.set(s1, "Hello ");
        ASSERT(String.equals(s1, part1));
        
        String.set(s1, "");
        ASSERT(String.equals(s1, part2));
        
        String.set(s1, "bunny. ");
        ASSERT(String.equals(s1, part3));
        
        String.set(s1, "");
        ASSERT(String.equals(s1, part4));

    END
    
    CASE("empty str split")
        String.set(s2, "");
        ListObject* ss1 = String.splitstr(s1, s2, mem);
        ASSERT(ss1 == NULL);
    END

STOP
