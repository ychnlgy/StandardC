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
    
    Os.chmod(Path.cstr(fileNoRead), "-r");
    Os.chmod(Path.cstr(fileNoWrite), "-w");
    Os.chmod(Path.cstr(fileNoReadOrWrite), "-rw");
}

TEARDOWN {
    Os.chmod(Path.cstr(fileNoRead), "+r");
    Os.chmod(Path.cstr(fileNoWrite), "+w");
    Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw");
    decref(mem);
}

RUN 

    CASE("isfile-isdir")
        
        ASSERT(Os.isfile(Path.cstr(filep)));
        ASSERT(Os.isdir(Path.cstr(dataDir)));
        ASSERT(Os.isdir(Path.cstr(dir)));
        ASSERT(Os.isfile(Path.cstr(fname)));
        
        ASSERT(!Os.isfile(Path.cstr(dataDir)));
        ASSERT(!Os.isdir(Path.cstr(filep)));
        ASSERT(!Os.isdir(Path.cstr(fname)));
        ASSERT(!Os.isfile(Path.cstr(dir)));
        
        ASSERT(!Os.isfile("skdjflds.c"));
        ASSERT(!Os.isdir("skdjls/sdfs"));
        
        ASSERT(!Os.isfile(""));
        ASSERT(!Os.isdir(""));
    
    END

    CASE("readable-writable")
        
        ASSERT(Os.readable(Path.cstr(filep)));
        ASSERT(Os.writable(Path.cstr(filep)));
        
        ASSERT(!Os.readable(Path.cstr(fileNoRead)));
        ASSERT(Os.writable(Path.cstr(filep)));
        
        ASSERT(Os.readable(Path.cstr(fileNoWrite)));
        ASSERT(!Os.writable(Path.cstr(fileNoWrite)));
        
        ASSERT(!Os.readable(Path.cstr(fileNoReadOrWrite)));
        ASSERT(!Os.writable(Path.cstr(fileNoReadOrWrite)));
    END

STOP
