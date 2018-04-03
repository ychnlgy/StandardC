#include "stdc/unittest.h"

MemoryObject* mem;
PathObject* dir;
PathObject* fname;
PathObject* dataDir;
PathObject* filep;
PathObject* fileNoRead;
PathObject* fileNoWrite;
PathObject* fileNoReadOrWrite;

SETUP {
    mem = Memory.new();
    fname = Memory.make(mem, Path.new);
    
    Path.setrel(fname, __FILE__);
    dir = Path.dirname(fname, mem);
    dataDir = Path.addcstr(dir, "data", mem);
    filep = Path.addcstr(dataDir, "file1.txt", mem);
    fileNoRead = Path.addcstr(dataDir, "cannotRead.txt", mem);
    fileNoWrite = Path.addcstr(dataDir, "cannotWrite.txt", mem);
    fileNoReadOrWrite = Path.addcstr(dataDir, "cannotReadOrWrite.txt", mem);
    
    
}

TEARDOWN {
    Os.chmod(Path.cstr(fileNoRead), "+rw");
    Os.chmod(Path.cstr(fileNoWrite), "+rw");
    Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw");
    decref(mem);
}

RUN 

    CASE("chmod")
        ASSERT(Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        ASSERT(Os.chmod(Path.cstr(fileNoRead), "-r") == 0);
        ASSERT(!Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        
        ASSERT(Os.readable(Path.cstr(fileNoWrite)));
        ASSERT(Os.writable(Path.cstr(fileNoWrite)));
        ASSERT(Os.chmod(Path.cstr(fileNoWrite), "-w") == 0);
        ASSERT(Os.readable(Path.cstr(fileNoWrite)));
        ASSERT(!Os.writable(Path.cstr(fileNoWrite)));
        
        ASSERT(Os.readable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(Os.writable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(Os.chmod(Path.cstr(fileNoReadOrWrite), "-rw") == 0);
        ASSERT(!Os.readable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(!Os.writable(Path.cstr(fileNoReadOrWrite)));
        
        ASSERT(!Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        ASSERT(Os.chmod(Path.cstr(fileNoRead), "+r") == 0);
        ASSERT(Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        
        ASSERT(Os.readable(Path.cstr(fileNoWrite)));
        ASSERT(!Os.writable(Path.cstr(fileNoWrite)));
        ASSERT(Os.chmod(Path.cstr(fileNoWrite), "+w") == 0);
        ASSERT(Os.readable(Path.cstr(fileNoWrite)));
        ASSERT(Os.writable(Path.cstr(fileNoWrite)));
        
        ASSERT(!Os.readable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(!Os.writable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw") == 0);
        ASSERT(Os.readable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(Os.writable(Path.cstr(fileNoReadOrWrite)));
    END
    
    CASE("chmod bad")
        ASSERT(Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        
        ASSERT(Os.chmod(Path.cstr(fileNoRead), "r") == -1);
        ASSERT(Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        
        ASSERT(Os.chmod(Path.cstr(fileNoRead), "rw") == -1);
        ASSERT(Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
        
        ASSERT(Os.chmod(Path.cstr(fileNoRead), "-rpoa") == -1);
        ASSERT(Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(fileNoRead)));
    END

STOP
