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

STOP
