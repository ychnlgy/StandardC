#include "stdc/unittest.h"

MemoryObject* mem;
PathObject* dir;
PathObject* fname;
PathObject* dataDir;
PathObject* filep;

SETUP {
    mem = Memory.new();
    fname = Memory.make(mem, Path.new);
    
    Path.setrel(fname, __FILE__);
    dir = Path.dirname(fname, mem);
    dataDir = Path.addcstr(dir, "data", mem);
    filep = Path.addcstr(dataDir, "file1.txt", mem);
}

TEARDOWN {
    decref(mem);
}

RUN 

    CASE("isfile")
        
/*        ASSERT(Os.isfile("*/
    
    END

STOP
