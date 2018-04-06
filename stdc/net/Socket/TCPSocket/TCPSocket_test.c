#include "stdc/unittest.h"

#include <string.h>
#include <unistd.h>
#include <sched.h>
// sched_yield
#include <pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t serverThread;
pthread_t clientThread;
bool started = false;

MemoryObject* mem;
TCPSocketObject* serverSock;
TCPSocketObject* clientSock;

CStr serverHello = "0123456789";
CStr clientGoodbye = "Goodbye (from Grook)";
CStr LOCAL_IP = "127.0.0.1";
int PORT = 8080;

void lockClient() {
    pthread_mutex_lock(&mutex);
    while (!started)
        pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void lockServer() {
    pthread_mutex_lock(&mutex);
    started = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

// One message

Ptr serverOneMsg(Ptr args) {
    
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(strlen(serverHello) == TCPSocket.write(connectedSock, serverHello));
    
    FileData* fd = TCPSocket.read(connectedSock, mem);
    ASSERT(fd->n == strlen(clientGoodbye));
    ASSERT(strcmp(fd->d, clientGoodbye) == 0);

    return NULL;
}

Ptr clientOneMsg(Ptr args) {
    _TestCase* _testCase = args;
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    
    FileData* fd = TCPSocket.read(clientSock, mem);
    ASSERT(fd->n == strlen(serverHello));
    ASSERT(strcmp(fd->d, serverHello) == 0);
    
    ASSERT(strlen(clientGoodbye) == TCPSocket.write(clientSock, clientGoodbye));

    return NULL;
}

// Null message

Ptr serverNullMsg(Ptr args) {
    
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(0 == TCPSocket.write(connectedSock, NULL));
    ASSERT(0 == TCPSocket.writestr(connectedSock, NULL));
    
    // Cannot read empty messages
/*    FileData* fd = TCPSocket.read(connectedSock, mem);*/
/*    ASSERT(fd->n == 0);*/

    return NULL;
}

Ptr clientNullMsg(Ptr args) {
    _TestCase* _testCase = args;
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    
    // Cannot read empty message
/*    FileData* fd = TCPSocket.read(clientSock, mem);*/
/*    ASSERT(fd->n == 0);*/
    
    ASSERT(0 == TCPSocket.write(clientSock, NULL));
    ASSERT(0 == TCPSocket.writestr(clientSock, NULL));

    return NULL;
}

// Null message

Ptr serverNonexistentFile(Ptr args) {
    
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    
    FileObject* filenotinit = File.new();
    ASSERT(0 == TCPSocket.writefile(connectedSock, filenotinit));
    ASSERT(0 == TCPSocket.writefile(connectedSock, NULL));
    
    // Cannot read empty messages
/*    FileData* fd = TCPSocket.read(connectedSock, mem);*/
/*    ASSERT(fd->n == 0);*/

    decref(filenotinit);
    return NULL;
}

Ptr clientNonexistentFile(Ptr args) {
    _TestCase* _testCase = args;
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    
    FileObject* filenonexist = File.new();
    File.name(filenonexist, "Lasjsddlfks");
    ASSERT(!File.exists(filenonexist));
    
    // Cannot read empty message
/*    FileData* fd = TCPSocket.read(clientSock, mem);*/
/*    ASSERT(fd->n == 0);*/
    
    ASSERT(0 == TCPSocket.writefile(clientSock, filenonexist));
    decref(filenonexist);
    return NULL;
}

// Multiple messages

long MULTIPLE = 2000;
CStr HELLO_WORLD = "Hello world!";
CStr FOO_BAZ_BAR = "Foo Baz Bar";

Ptr serverMultipleMsgs(Ptr args) {
    
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    
    long i;
    for (i=0; i<MULTIPLE; i++) {
        ASSERT(strlen(HELLO_WORLD) == TCPSocket.write(connectedSock, HELLO_WORLD));
        
        FileData* fd = TCPSocket.read(connectedSock, mem);
        ASSERT(fd->n == strlen(FOO_BAZ_BAR));
        ASSERT(strcmp(fd->d, FOO_BAZ_BAR) == 0);
    }

    return NULL;
}

Ptr clientMultipleMsgs(Ptr args) {
    _TestCase* _testCase = args;
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    
    int i = 0;
    for (i=0; i<MULTIPLE; i++) {
        FileData* fd = TCPSocket.read(clientSock, mem);
        ASSERT(fd->n == strlen(HELLO_WORLD));
        ASSERT(strcmp(fd->d, HELLO_WORLD) == 0);
        ASSERT(strlen(FOO_BAZ_BAR) == TCPSocket.write(clientSock, FOO_BAZ_BAR));
    }
    return NULL;
}

// Large data + writestr

StringObject* multiplyString(CStr cstr, int n, MemoryObject* mem) {
    MemoryObject* scope = Memory.new();
    StringObject* s = Memory.make(scope, String.new);
    String.set(s, cstr);
    ListObject* list = Memory.make(scope, List.new);
    int i;
    for (i=0; i<n; i++)
        List.push(list, s);
    StringObject* out = String.merge(list, mem);
    decref(scope);
    return out;
}

int SERVER_REPEAT = 1000;
int CLIENT_REPEAT = 1000;
CStr SERVER_LARGE = "Server";
CStr CLIENT_LARGE = "Client!";

Ptr serverLargeMsg(Ptr args) {
    
    _TestCase* _testCase = args;

    StringObject* serverMsg = multiplyString(SERVER_LARGE, SERVER_REPEAT, mem);

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(String.size(serverMsg) == TCPSocket.writestr(connectedSock, serverMsg));
    
    FileData* fd = TCPSocket.read(connectedSock, mem);
    ASSERT(fd->n == CLIENT_REPEAT*strlen(CLIENT_LARGE));
    
    int i;
    for (i=0; i<fd->n; i++)
        ASSERT(fd->d[i] == CLIENT_LARGE[MOD(i, strlen(CLIENT_LARGE))]);

    
    return NULL;
}

Ptr clientLargeMsg(Ptr args) {
    _TestCase* _testCase = args;
    
    StringObject* clientMsg = multiplyString(CLIENT_LARGE, CLIENT_REPEAT, mem);
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)){
        sched_yield();
    }
    
    FileData* fd = TCPSocket.read(clientSock, mem);
    ASSERT(fd->n == strlen(SERVER_LARGE)*SERVER_REPEAT);
    
    int i;
    for (i=0; i<fd->n; i++)
        ASSERT(fd->d[i] == SERVER_LARGE[MOD(i, strlen(SERVER_LARGE))]);
    
    ASSERT(String.size(clientMsg) == TCPSocket.writestr(clientSock, clientMsg));
    return NULL;
}

// Small text file

char* binfilen = "data/binfile.o";
char* textfilen = "data/textfile.txt";

char* binfilen2 = "data/binfile2.o";
char* textfilen2 = "data/textfile2.txt";

PathObject* filex;
PathObject* dir;

PathObject* binfilep;
PathObject* textfilep;
PathObject* binfilep2;
PathObject* textfilep2;

FileObject* binfile;
FileObject* textfile;
FileObject* binfile2;
FileObject* textfile2;

Ptr serverTxtFile(Ptr args) {
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    ASSERT(File.exists(textfile));
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(9 == TCPSocket.writefile(connectedSock, textfile));
    
    FileObject* fd = TCPSocket.readfile(connectedSock, mem);
    File.namepath(fd, binfilep2);
    
    ASSERT(!File.equals(fd, binfile));
    File.flush(fd);
    
    ASSERT(File.equals(fd, binfile));
    
    return NULL;
}

Ptr clientTxtFile(Ptr args) {
    
    _TestCase* _testCase = args;
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    
    ASSERT(!File.equals(textfile2, textfile));
    
    FileObject* fileData = TCPSocket.readfile(clientSock, mem);
    File.namepath(fileData, textfilep2);
    File.flush(fileData);
    
    ASSERT(File.equals(fileData, textfile));
    ASSERT(File.equals(textfile2, textfile));
    ASSERT(!File.equals(fileData, binfile));
    
    ASSERT(33744 == TCPSocket.writefile(clientSock, binfile));
    return NULL;
}

// Large bin file

Ptr serverBinFile(Ptr args) {
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    ASSERT(File.exists(binfile));
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(33744 == TCPSocket.writefile(connectedSock, binfile));
    
    FileObject* fd = TCPSocket.readfile(connectedSock, mem);
    File.namepath(fd, textfilep2);

    ASSERT(!File.equals(fd, textfile));
    ASSERT(!File.equals(textfile2, textfile));
    ASSERT(File.exists(binfile));
    ASSERT(!File.equals(textfile2, binfile));
    
    File.flush(fd);
    
    ASSERT(File.equals(fd, textfile));
    ASSERT(File.equals(textfile2, textfile));
    ASSERT(File.exists(binfile));
    ASSERT(!File.equals(textfile2, binfile));
    return NULL;
}

Ptr clientBinFile(Ptr args) {
    
    _TestCase* _testCase = args;
    
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    
    ASSERT(!File.equals(binfile2, binfile));
    
    FileObject* fileData = TCPSocket.readfile(clientSock, mem);
    File.namepath(fileData, binfilep2);
    File.flush(fileData);
    
    ASSERT(File.equals(fileData, binfile));
    ASSERT(File.equals(binfile2, binfile));
    ASSERT(!File.equals(fileData, textfile));
    
    ASSERT(9 == TCPSocket.writefile(clientSock, textfile));
    return NULL;
}

// Failed file transfer

Ptr serverDirTransfer(Ptr args) {
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 5));
    
    lockServer();
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    File.namepath(textfile, dir); // textfile has name of directory
    ASSERT(0 == TCPSocket.writefile(connectedSock, textfile));
    return NULL;
}

Ptr clientDirTransfer(Ptr args) {
    lockClient();
    
    while(!TCPSocket.connect(clientSock, LOCAL_IP, PORT)) {
        sched_yield();
    }
    return NULL;
}


void runServerAndClient(ThreadFunc server, ThreadFunc client, Ptr args) {
    pthread_create(&serverThread, NULL, server, args);
    pthread_create(&clientThread, NULL, client, args);
    pthread_join(serverThread, NULL);
    pthread_join(clientThread, NULL);
}

SETUP {
    pthread_mutex_init(&mutex, NULL);

    mem = Memory.new();
    serverSock = Memory.make(mem, TCPSocket.new);
    clientSock = Memory.make(mem, TCPSocket.new);
    
    filex = Memory.make(mem, Path.new);
    Path.setrel(filex, __FILE__);
    dir = Path.dirname(filex, mem);
    binfilep = Path.addcstr(dir, binfilen, mem);
    textfilep = Path.addcstr(dir, textfilen, mem);
    binfilep2 = Path.addcstr(dir, binfilen2, mem);
    textfilep2 = Path.addcstr(dir, textfilen2, mem);
    
    binfile = Memory.make(mem, File.new);
    File.namepath(binfile, binfilep);
    
    textfile = Memory.make(mem, File.new);
    File.namepath(textfile, textfilep);
    
    binfile2 = Memory.make(mem, File.new);
    File.namepath(binfile2, binfilep2);
    
    textfile2 = Memory.make(mem, File.new);
    File.namepath(textfile2, textfilep2);
}

TEARDOWN {
    decref(mem);
    
    pthread_mutex_destroy(&mutex);
}

RUN

    CASE("ip address")
        ASSERT(TCPSocket.bind(serverSock, LOCAL_IP, PORT));
        ASSERT(strcmp(TCPSocket.getIpAddr(serverSock), LOCAL_IP) == 0);
    END

    CASE("bad vs good ip binding")
        ASSERT(!TCPSocket.bind(serverSock, "100.0.0.1", 8080));
        ASSERT(TCPSocket.bind(serverSock, LOCAL_IP, PORT));
    END
    
    CASE("null message")
        runServerAndClient(&serverNullMsg, &clientNullMsg, _testCase);
    END
    
    CASE("nonexistent file transfer")
        runServerAndClient(&serverNonexistentFile, &clientNonexistentFile, _testCase);
    END
    
    CASE("interaction-cstr")
        runServerAndClient(&serverOneMsg, &clientOneMsg, _testCase);
    END
    
    CASE("multiple interactions")
        runServerAndClient(&serverMultipleMsgs, &clientMultipleMsgs, _testCase);
    END
    
    CASE("large data")
        runServerAndClient(&serverLargeMsg, &clientLargeMsg, _testCase);
    END
    
    CASE("read-write txtfile")
        ASSERT(File.exists(binfile));
        ASSERT(!File.exists(binfile2));
    
        ASSERT(File.exists(textfile));
        ASSERT(!File.exists(textfile2));
        runServerAndClient(&serverTxtFile, &clientTxtFile, _testCase);
        ASSERT(File.exists(textfile));
        ASSERT(File.exists(textfile2));
        ASSERT(File.remove(textfile2));
        
        ASSERT(File.exists(binfile));
        ASSERT(File.exists(binfile2));
        ASSERT(File.remove(binfile2));
    END
    
    CASE("read-write binfile")
        ASSERT(File.exists(binfile));
        ASSERT(!File.exists(binfile2));
    
        ASSERT(File.exists(textfile));
        ASSERT(!File.exists(textfile2));
        runServerAndClient(&serverBinFile, &clientBinFile, _testCase);
        ASSERT(File.exists(textfile));
        ASSERT(File.exists(textfile2));
        ASSERT(File.remove(textfile2));
        
        ASSERT(File.exists(binfile));
        ASSERT(File.exists(binfile2));
        ASSERT(File.remove(binfile2));
    END
    
    CASE("dir transfer")
        runServerAndClient(&serverDirTransfer, &clientDirTransfer, _testCase);
    END

STOP
