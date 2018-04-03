#include "stdc/unittest.h"

MemoryObject* mem;
PathObject* p1;
PathObject* p2;

SETUP {
    mem = Memory.new();
    p1 = Memory.make(mem, Path.new);
    Path.setrel(p1, "folder/subfolder\\file.py");
    p2 = Memory.make(mem, Path.new);
}

TEARDOWN {
    decref(mem);
}

RUN

    CASE("empty path")
        ASSERT(Path.cstr(p2) == NULL);
        ASSERT(String.size(Path.str(p2)) == 0);
    END
    
    CASE("set")
        StringObject* s = Memory.make(mem, String.new);
        String.set(s, "folder/subfolder\\file.py");
        ASSERT(String.equals(s, Path.str(p1)));
    END
    
    CASE("set empty")
        Path.setrel(p1, "");
        StringObject* s = Memory.make(mem, String.new);
        String.set(s, "");
        ASSERT(String.equals(s, Path.str(p1)));
    END
    
    CASE("copy")
        PathObject* p3 = Path.copy(p1, mem);
        ASSERT(Path.equals(p3, p1));
        ASSERT(!Path.equals(p3, p2));
        ASSERT(!Path.equals(p1, p2));
        p3 = Path.copy(p2, mem);
        ASSERT(!Path.equals(p3, p1));
        ASSERT(Path.equals(p3, p2));
        ASSERT(!Path.equals(p1, p2));
    END

STOP
