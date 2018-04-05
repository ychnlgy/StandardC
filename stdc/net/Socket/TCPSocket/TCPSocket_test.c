#include "stdc/unittest.h"

#include <string.h>
#include <unistd.h>
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

// One message

Ptr serverOneMsg(Ptr args) {
    pthread_mutex_lock(&mutex);
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 1));
    
    started = true;
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(strlen(serverHello) == TCPSocket.write(connectedSock, serverHello));
    
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    FileData* fd = TCPSocket.read(connectedSock, mem);
    ASSERT(fd->n == strlen(clientGoodbye));
    ASSERT(strcmp(fd->d, clientGoodbye) == 0);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

Ptr clientOneMsg(Ptr args) {
    pthread_mutex_lock(&mutex);
    _TestCase* _testCase = args;
    
    if (!started)
        pthread_cond_wait(&cond, &mutex);
    
    ASSERT(TCPSocket.connect(clientSock, LOCAL_IP, PORT));
    
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    FileData* fd = TCPSocket.read(clientSock, mem);
    ASSERT(fd->n == strlen(serverHello));
    ASSERT(strcmp(fd->d, serverHello) == 0);
    
    ASSERT(strlen(clientGoodbye) == TCPSocket.write(clientSock, clientGoodbye));
    pthread_cond_signal(&cond);
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Multiple messages

long MULTIPLE = 100;
CStr HELLO_WORLD = "Hello world!";
CStr FOO_BAZ_BAR = "Foo Baz Bar";

Ptr serverMultipleMsgs(Ptr args) {
    pthread_mutex_lock(&mutex);
    _TestCase* _testCase = args;

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 1));
    
    started = true;
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    
    long i;
    for (i=0; i<MULTIPLE; i++) {
        ASSERT(strlen(HELLO_WORLD) == TCPSocket.write(connectedSock, HELLO_WORLD));
        
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond, &mutex);
        
        FileData* fd;
        while((fd = TCPSocket.read(connectedSock, mem)) == NULL) {
            sleep(1);
        }
        ASSERT(fd->n == strlen(FOO_BAZ_BAR));
        ASSERT(strcmp(fd->d, FOO_BAZ_BAR) == 0);
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

Ptr clientMultipleMsgs(Ptr args) {
    pthread_mutex_lock(&mutex);
    _TestCase* _testCase = args;
    
    if (!started)
        pthread_cond_wait(&cond, &mutex);
    
    ASSERT(TCPSocket.connect(clientSock, LOCAL_IP, PORT));
    
    int i = 0;
    for (i=0; i<MULTIPLE; i++) {
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond, &mutex);
        
        FileData* fd;
        while((fd = TCPSocket.read(clientSock, mem)) == NULL) {
            sleep(1);
        }
        ASSERT(fd->n == strlen(HELLO_WORLD));
        ASSERT(strcmp(fd->d, HELLO_WORLD) == 0);
        ASSERT(strlen(FOO_BAZ_BAR) == TCPSocket.write(clientSock, FOO_BAZ_BAR));
    }
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
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
    pthread_mutex_lock(&mutex);
    _TestCase* _testCase = args;

    StringObject* serverMsg = multiplyString(SERVER_LARGE, SERVER_REPEAT, mem);

    ASSERT(TCPSocket.bindany(serverSock, PORT));
    ASSERT(TCPSocket.listen(serverSock, 1));
    
    started = true;
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    TCPSocketObject* connectedSock = TCPSocket.accept(serverSock, mem);
    ASSERT(String.size(serverMsg) == TCPSocket.writestr(connectedSock, serverMsg));
    
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    FileData* fd;
    while((fd = TCPSocket.read(connectedSock, mem)) == NULL) {
        sleep(1);
    }
    ASSERT(fd->n == CLIENT_REPEAT*strlen(CLIENT_LARGE));
    
    int i;
    for (i=0; i<fd->n; i++)
        ASSERT(fd->d[i] == CLIENT_LARGE[MOD(i, strlen(CLIENT_LARGE))]);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

Ptr clientLargeMsg(Ptr args) {
    pthread_mutex_lock(&mutex);
    _TestCase* _testCase = args;
    
    StringObject* clientMsg = multiplyString(CLIENT_LARGE, CLIENT_REPEAT, mem);
    
    if (!started)
        pthread_cond_wait(&cond, &mutex);
    
    ASSERT(TCPSocket.connect(clientSock, LOCAL_IP, PORT));
    
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &mutex);
    
    FileData* fd;
    while((fd = TCPSocket.read(clientSock, mem)) == NULL) {
        sleep(1);
    }
    ASSERT(fd->n == strlen(SERVER_LARGE)*SERVER_REPEAT);
    
    int i;
    for (i=0; i<fd->n; i++)
        ASSERT(fd->d[i] == SERVER_LARGE[MOD(i, strlen(SERVER_LARGE))]);
    
    ASSERT(String.size(clientMsg) == TCPSocket.writestr(clientSock, clientMsg));
    pthread_cond_signal(&cond);
    
    pthread_mutex_unlock(&mutex);
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
}

TEARDOWN {
    decref(mem);
    
    pthread_mutex_destroy(&mutex);
}

RUN

    CASE("bad vs good ip binding")
        ASSERT(!TCPSocket.bind(serverSock, "100.0.0.1", 8080));
        ASSERT(TCPSocket.bind(serverSock, LOCAL_IP, PORT));
    END
    
    CASE("interaction-cstr")
        runServerAndClient(&serverOneMsg, &clientOneMsg, _testCase);
    END
    
    CASE("multiple interactions")
        runServerAndClient(&serverMultipleMsgs, &clientMultipleMsgs, _testCase);
    END
/*    */
/*    CASE("large data")*/
/*        runServerAndClient(&serverLargeMsg, &clientLargeMsg, _testCase);*/
/*    END*/

STOP
