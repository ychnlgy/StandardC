#include "stdc/unittest.h"

MemoryObject* mem;
PathObject* dir;
PathObject* fname;
PathObject* dataDir;
PathObject* filep;
PathObject* fileNoRead;
PathObject* fileNoWrite;
PathObject* fileNoReadOrWrite;

PathObject* p1;
PathObject* p2;

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
    
    p1 = Memory.make(mem, Path.new);
    Path.setrel(p1, "folder/subfolder\\file.py");
    p2 = Memory.make(mem, Path.new);
}

TEARDOWN {
    Os.chmod(Path.cstr(fileNoRead), "+rw");
    Os.chmod(Path.cstr(fileNoWrite), "+rw");
    Os.chmod(Path.cstr(fileNoReadOrWrite), "+rw");
    decref(mem);
}

RUN

    // Object
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
    
    CASE("size")
        ASSERT(Path.size(filep) == 6);
        ASSERT(Path.size(dir) > 0);
        ASSERT(Path.size(fileNoReadOrWrite) == 10);
        ASSERT(Path.size(fileNoRead) == 0);
        ASSERT(Path.size(fileNoWrite) == 0);
    END

    // listdir
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
    
    // Numeric
    CASE("add")
        PathObject* p3 = Path.add(p1, p2, mem);
        StringObject* s1 = Memory.make(mem, String.new);
        String.set(s1, "folder/subfolder/file.py");
        ASSERT(String.equals(s1, Path.str(p3)));
        p3 = Path.add(p2, p1, mem);
        ASSERT(String.equals(s1, Path.str(p3)));
        Path.setrel(p2, "subdir\\joke");
        ASSERT(String.equals(s1, Path.str(p3)));
        p3 = Path.add(p2, p1, mem);
        ASSERT(!String.equals(s1, Path.str(p3)));
        String.set(s1, "subdir/joke/folder/subfolder/file.py");
        ASSERT(String.equals(s1, Path.str(p3)));
    END
    
    CASE("strip-terminating folder sep")
        Path.setrel(p2, "folder/with/sep/");
        Path.setrel(p1, "folder/with/sep");
        ASSERT(Path.equals(p1, p2));
        
        Path.setrel(p1, "subfolder/pop/");
        p2 = Path.add(p2, p1, mem);
        PathObject* p3 = Memory.make(mem, Path.new);
        Path.setrel(p3, "folder/with/sep/subfolder/pop");
        ASSERT(Path.equals(p2, p3));
        
        Path.setrel(p1, "file.py");
        p1 = Path.add(p2, p1, mem);
        Path.setrel(p3, "folder/with/sep/subfolder/pop/file.py");
        ASSERT(Path.equals(p1, p3));
        
        Path.setrel(p1, "joke/inner\\outer\\");
        p1 = Path.add(p2, p1, mem);
        Path.setrel(p3, "folder/with/sep/subfolder/pop/joke/inner/outer");
        ASSERT(Path.equals(p1, p3));
    END
    
    CASE("abs")
        StringObject* cwd = Memory.make(mem, String.new);
        String.set(cwd, Os.cwd(mem));
        StringObject* file = Memory.make(mem, String.new);
        String.set(file, "/folder/subfolder/file.py");
        StringObject* fname = String.add(cwd, file, mem);
        
        PathObject* absp = Path.abs(p1, mem);
        ASSERT(String.equals(fname, Path.str(absp)));
        ASSERT(!String.equals(Path.str(p1), Path.str(absp)));
        
        PathObject* absp2 = Path.abs(p2, mem);
        ASSERT(String.equals(cwd, Path.str(absp2)));
    END
    
    CASE("abs-already")
        Path.setabs(p1, "/usr/c");
        StringObject* cwd = Memory.make(mem, String.new);
        String.set(cwd, "/usr/c");
        ASSERT(String.equals(cwd, Path.str(p1)));
        Path.setabsstr(p1, cwd);
        ASSERT(String.equals(cwd, Path.str(p1)));
    END
    
    CASE("norm")
        StringObject* s1 = Memory.make(mem, String.new);
        String.set(s1, "folder/subfolder/file.py");
        ASSERT(!String.equals(s1, Path.str(p1)));
        PathObject* p3 = Path.norm(p1, mem);
        ASSERT(String.equals(s1, Path.str(p3)));
        PathObject* p4 = Path.norm(p2, mem);
        ASSERT(!String.equals(s1, Path.str(p4)));
        String.set(s1, "");
        ASSERT(String.equals(s1, Path.str(p4)));
    END
    
    CASE("norm-start back")
        StringObject* s1 = Memory.make(mem, String.new);
        StringObject* s2 = Memory.make(mem, String.new);
        String.set(s1, "../folder/subfolder/file.py");
        String.set(s2, "../folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
    
        String.set(s1, "folder/../subfolder/file.py");
        String.set(s2, "subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "../../folder/subfolder/file.py");
        String.set(s2, "../../folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "../folder/subfolder/../../file.py");
        String.set(s2, "../file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "folder/subfolder/../../file.py");
        String.set(s2, "file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "../../../../");
        String.set(s2, "../../../..");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
    END
    
    CASE("norm-redundancy")
        StringObject* s1 = Memory.make(mem, String.new);
        StringObject* s2 = Memory.make(mem, String.new);
        String.set(s1, "./folder/subfolder/file.py");
        String.set(s2, "folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "folder/./subfolder/file.py");
        String.set(s2, "folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "././folder/subfolder/file.py");
        String.set(s2, "folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "./folder/subfolder/././file.py");
        String.set(s2, "folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "folder/subfolder/././file.py");
        String.set(s2, "folder/subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
    
        String.set(s1, "./././././");
        String.set(s2, "");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
    END
    
    CASE("norm-both")
        StringObject* s1 = Memory.make(mem, String.new);
        StringObject* s2 = Memory.make(mem, String.new);
        String.set(s1, "./folder/../../subfolder/./file.py");
        String.set(s2, "../subfolder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
        String.set(s1, "folder/./subfolder/../file.py");
        String.set(s2, "folder/file.py");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
    
        String.set(s1, "./././../././..");
        String.set(s2, "../..");
        Path.setrelstr(p1, s1);
        p2 = Path.norm(p1, mem);
        ASSERT(String.equals(Path.str(p2), s2));
        
    END

    // Path
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
    
    CASE("abspath")
        Path.setabs(p1, "c:/usr/folder");
        Path.setabs(p2, "c:/usr/folder");
        ASSERT(Path.equals(p1, p2));
    END

STOP
