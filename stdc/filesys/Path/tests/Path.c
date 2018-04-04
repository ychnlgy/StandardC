#include "stdc/unittest.h"

MemoryObject* mem;
PathObject* p1;
PathObject* p2;

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
    p1 = Memory.make(mem, Path.new);
    Path.setrel(p1, "folder/subfolder\\file.py");
    p2 = Memory.make(mem, Path.new);
    
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
    decref(mem);
}

RUN

    CASE("isfile-isdir")
        ASSERT(Path.isfile(fname));
        ASSERT(Path.isfile(filep));
        ASSERT(Path.isdir(dir));
        ASSERT(Path.isdir(dataDir));
        
        ASSERT(!Path.isdir(fname));
        ASSERT(!Path.isdir(filep));
        ASSERT(!Path.isfile(dir));
        ASSERT(!Path.isfile(dataDir));
        
    END

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
    
    CASE("listdir")
        ListObject* dirs = Path.listdir(dataDir, mem);//Os.listdir(Path.cstr(dataDir), mem);
        ASSERT(dirs != NULL);
        long size = List.size(dirs);
        ASSERT(size == 4);
        ListObject* realDirs = Memory.make(mem, List.new);
        List.pushes(realDirs, size, filep, fileNoRead, fileNoWrite, fileNoReadOrWrite);
        long i;
        for (i=0; i<size; i++) {
            PathObject* s = List.getitem(dirs, i);
            bool matched = false;
            long j;
            for (j=0; j<size; j++) {
                PathObject* p = List.getitem(realDirs, j);
                if (Path.equals(p, s)) {
                    matched = true;
                    break;
                }
            }
            ASSERT(matched);
        }
    END
    
    CASE("bad listdir")
        ListObject* dirs = Path.listdir(filep, mem);
        ASSERT(dirs == NULL);
    END
    
    CASE("basename")
        ASSERT(Path.basename(p2) == NULL);
        ASSERT(String.eqCStr(Path.basename(p1), "file.py"));
    END

STOP
