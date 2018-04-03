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

    CASE("addcstr")
        Path.setrel(p1, "folder");
        p2 = Path.addcstr(p1, "sub1\\gook/./sup", mem);
        p2 = Path.addcstr(p2, "../foo.py", mem);
        ASSERT(String.eqCStr(Path.str(p2), "folder/sub1/gook/foo.py"));
    END

    CASE("dirname")
        p2 = Path.dirname(p1, mem);
        ASSERT(String.eqCStr(Path.str(p2), "folder/subfolder"));
        p2 = Path.dirname(p2, mem);
        ASSERT(String.eqCStr(Path.str(p2), "folder"));
        p2 = Path.dirname(p2, mem);
        ASSERT(String.eqCStr(Path.str(p2), NULL));
        p2 = Path.dirname(p2, mem);
        ASSERT(String.eqCStr(Path.str(p2), ""));
    END

STOP
