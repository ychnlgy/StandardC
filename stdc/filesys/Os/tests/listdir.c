#include "stdc/unittest.h"

MemoryObject* mem;
PathObject* dir;
PathObject* fname;
PathObject* dataDir;
PathObject* filep;
PathObject* fileNoRead;
PathObject* fileNoWrite;
PathObject* fileNoReadOrWrite;

char* filepn = "file1.txt";
char* filenrn = "cannotRead.txt";
char* filenwn = "cannotWrite.txt";
char* filenrwn = "cannotReadOrWrite.txt";

SETUP {
    mem = Memory.new();
    fname = Memory.make(mem, Path.new);
    
    Path.setrel(fname, __FILE__);
    dir = Path.dirname(fname, mem);
    dataDir = Path.addcstr(dir, "data", mem);
    filep = Path.addcstr(dataDir, filepn, mem);
    fileNoRead = Path.addcstr(dataDir, filenrn, mem);
    fileNoWrite = Path.addcstr(dataDir, filenwn, mem);
    fileNoReadOrWrite = Path.addcstr(dataDir, filenrwn, mem);
}

TEARDOWN {
    Os.chmod(Path.cstr(fileNoRead), "+rw");
    Os.chmod(Path.cstr(fileNoWrite), "+rw");
    Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw");
    decref(mem);
}

RUN
    CASE("listdir")
        ListObject* dirs = Os.listdir(Path.cstr(dataDir), mem);
        long size = List.size(dirs);
        ASSERT(size == 4);
        ListObject* realDirs = Memory.make(mem, List.new);
        List.pushes(realDirs, size, filep, fileNoRead, fileNoWrite, fileNoReadOrWrite);
        long i;
        for (i=0; i<size; i++) {
            StringObject* s = List.getitem(dirs, i);
            bool matched = false;
            long j;
            for (j=0; j<size; j++) {
                PathObject* p = List.getitem(realDirs, j);
                if (String.endswith(Path.str(p), s)) {
                    matched = true;
                    break;
                }
            }
            ASSERT(matched);
        }
    END
    
    CASE("bad listdir")
        ListObject* dirs = Os.listdir("ksjdfks", mem);
        ASSERT(dirs == NULL);
        dirs = Os.listdir(Path.cstr(filep), mem);
        ASSERT(dirs == NULL);
    END

STOP
