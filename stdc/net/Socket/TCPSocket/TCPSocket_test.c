#include "stdc/unittest.h"

#include <string.h>
#include <pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t serverThread;
pthread_t clientThread;
bool started = false;

MemoryObject* mem;
TCPSocketObject* serverSock;
TCPSocketObject* clientSock;

CStr serverHello = "Hello";
CStr clientGoodbye = "Goodbye (from Grook)";
CStr LOCAL_IP = "127.0.0.1";
int PORT = 8080;

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

STOP
