#include "stdc/unittest.h"
#include <string.h>
// strlen

#include <stdio.h>
// remove

MemoryObject* mem;
FileObject* f1;

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
    f1 = Memory.make(mem, File.new);
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
    
    remove(Path.cstr(filep));
    f1 = Memory.make(mem, File.new);
    File.namepath(f1, filep);
    File.flush(f1);
    
    decref(mem);
}

RUN

    CASE("constructor")
        ASSERT(!File.exists(f1));
    
        File.name(f1, "foo.c");
        ASSERT(strcmp("foo.c", File.cstr(f1)) == 0);
        
        ASSERT(!File.exists(f1));
        File.name(f1, Path.cstr(filep));
        ASSERT(File.exists(f1));
        
        StringObject* s1 = Memory.make(mem, String.new);
        String.set(s1, "goo.c");
        
        File.namestr(f1, s1);
        ASSERT(!File.exists(f1));
        File.namestr(f1, Path.str(filep));
        ASSERT(File.exists(f1));
        
        File.namepath(f1, filep);
        ASSERT(File.exists(f1));
        File.namepath(f1, dir);
        ASSERT(!File.exists(f1));
    END
    
    CASE("readable-writable")
        ASSERT(!File.readable(f1));
        ASSERT(!File.writable(f1));
        
        File.namepath(f1, filep);
        ASSERT(File.readable(f1));
        ASSERT(File.writable(f1));
        
        File.namepath(f1, fileNoRead);
        ASSERT(!File.readable(f1));
        ASSERT(File.writable(f1));
        
        File.namepath(f1, fileNoReadOrWrite);
        ASSERT(!File.readable(f1));
        ASSERT(!File.writable(f1));
    
    END
    
    CASE("write-read null")
        // cannot read/flush without setting fname
        ASSERT(File.read(f1, mem) == NULL);
        ASSERT(File.flush(f1) == -1);
        
        File.namepath(f1, fileNoReadOrWrite);
        ASSERT(File.read(f1, mem) == NULL);
        ASSERT(File.flush(f1) == -1);
        
        // Try flushing bad input
        File.namepath(f1, filep);
        File.write(f1, 0, "skdfjlsd");
        File.write(f1, 10, NULL);
        ASSERT(File.flush(f1) == 0);
        
        StringObject* s = Memory.make(mem, String.new);
        String.set(s, NULL);
        File.writestr(f1, s);
        ASSERT(File.flush(f1) == 0);
        
        // read an empty file
        FileData* ss = File.read(f1, mem);
        ASSERT(ss->n == 0);
    END
    
    CASE("write-read")
        File.write(f1, 2, "01");
        File.write(f1, 5, "abcde");
        ASSERT(File.flush(f1) == -1);
        File.namepath(f1, filep);
        long size = 7;
        ASSERT(File.flush(f1) == size);
        FileData* fd1 = File.read(f1, mem);
        ASSERT(fd1->n == size);
        
        CStr answer = "01abcde";
        long i;
        for (i=0; i<size; i++)
            ASSERT(answer[i] == fd1->d[i]);
        
        StringObject* s = Memory.make(mem, String.new);
        CStr answer2 = "Hello world!";
        String.set(s, answer2);
        File.writestr(f1, s);
        size = 12;
        ASSERT(File.flush(f1) == size);
        fd1 = File.read(f1, mem);
        ASSERT(fd1->n == size);

        for (i=0; i<size; i++)
            ASSERT(answer2[i] == fd1->d[i]);
    END
    
    CASE("write-read long")
        File.namepath(f1, filep);
        CStr msg = "123456789";
        long len = 10;
        long loop = 100;
        long i;
        for (i=0; i<loop; i++)
            File.write(f1, len, msg);
        ASSERT(File.flush(f1) == len*loop);
        FileData* fd = File.read(f1, mem);
        ASSERT(fd->n == len*loop);
        for (i=0; i<loop; i++)
            ASSERT(msg[MOD(i, len)] == fd->d[i]);
    END

STOP
