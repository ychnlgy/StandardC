#include "stdc/unittest.h"
#include "stdc/unittest/print.h"

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

    CASE("cwd")
        printBlue(" %s:", Os.cwd(mem));
    END
    
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

    CASE("listdir folder")
        ListObject* dirs = Os.listdir(Path.cstr(dir), mem);
        ASSERT(List.size(dirs) > 3); // at least more than three items in this folder.
        long i;
        bool matched = false;
        for (i=0; i<List.size(dirs); i++) {
            StringObject* s = List.getitem(dirs, i);
            if (String.eqCStr(s, "data"))
                matched = true;
        }
        ASSERT(matched);
    END
    
    CASE("chmod")
        Os.chmod(Path.cstr(fileNoRead), "+r");
        Os.chmod(Path.cstr(fileNoWrite), "+w");
        Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw");
    
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
        Os.chmod(Path.cstr(fileNoRead), "+r");
        Os.chmod(Path.cstr(fileNoWrite), "+w");
        Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw");
        
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
    
    CASE("null names")
        ASSERT(!Os.isfile(NULL));
        ASSERT(!Os.isdir(NULL));
        ASSERT(!Os.readable(NULL));
        ASSERT(!Os.writable(NULL));
    END


STOP
