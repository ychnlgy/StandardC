# TCPSocket

For communicating between programs across a network.

## Methods chart
| Interface | Method |
|-----------|--------|
| Object | ```Ptr TCPSocket.new();``` |
|        | ```TCPSocketObject* TCPSocket.copy(TCPSocketObject* this, long filedescriptor, MemoryObject* mem);``` |
| Server | ```bool TCPSocket.bind(TCPSocketObject* this, CStr ip, long port);``` |
|        | ```bool TCPSocket.bindany(TCPSocketObject* this, long port);``` |
|        | ```bool TCPSocket.listen(TCPSocketObject* this, long maxlisteners);``` |
|        | ```TCPSocketObject* TCPSocket.accept(TCPSocketObject* this, MemoryObject* mem);``` |
| Client | ```bool TCPSocket.connect(TCPSocketObject* this, CStr ip, long port);``` |
| File | ```FileData* TCPSocket.read(TCPSocketObject* this, MemoryObject* mem);``` |
|      | ```FileObject* TCPSocket.readfile(TCPSocketObject* this, MemoryObject* mem);``` |
|      | ```long TCPSocket.write(TCPSocketObject* this, CStr msg);``` |
|      | ```long TCPSocket.writestr(TCPSocketObject* this, StringObject* msg);``` |
|      | ```long TCPSocket.writefile(TCPSocketObject* this, FileObject* file);``` |

## Files
 * [stdc/net/Socket/TCPSocket/TCPSocket.h](../stdc/net/Socket/TCPSocket/TCPSocket.h)
 * [stdc/net/Socket/TCPSocket/TCPSocket_protected.h](../stdc/net/Socket/TCPSocket/TCPSocket_protected.h)
 
## Demonstration
To run a server:
```c
#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
long maxclients = 3;

int main() {
    MemoryObject* mem = Memory.new();

    TCPSocketObject* server = Memory.make(mem, TCPSocket.new);
    TCPSocket.bindany(server, port);
    TCPSocket.listen(server, maxclients);
    
    // The following line blocks until a client connects.
    printf("Waiting for connections...\n");
    TCPSocketObject* connectedSock = TCPSocket.accept(server, mem);
    printf("Recieved a connection!\n");
    
    // Interact with client via the new socket: connectedSock
    FileData* data = TCPSocket.read(connectedSock, mem);
    printf("Client: %s\n", data->d);
    
    TCPSocket.write(connectedSock, "hello");

    decref(mem);
    return 0;
}
```
To run the client that interacts with this server, write:
```c
#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
CStr ip = "127.0.0.1"; // local computer

int main() {
    MemoryObject* mem = Memory.new();
    
    TCPSocketObject* client = Memory.make(mem, TCPSocket.new);
    TCPSocket.connect(client, ip, port);
    
    // Interact with server
    TCPSocket.write(client, "my name is Client");

    FileData* data = TCPSocket.read(client, mem);
    printf("Server: %s\n", data->d);
    
    decref(mem);
    return 0;
}
```
## Object
#### TCPSocket.new();
```c
Ptr TCPSocket.new();
```
Returns the pointer to a new TCPSocketObject.

#### TCPSocket.copy(_this_, _filedescriptor_, _mem_)
```c
TCPSocketObject* TCPSocket.copy(TCPSocketObject* this, long filedescriptor, MemoryObject* mem);
```
Returns a copy of **this** socket (i.e. same IP address and port) and set its **filedescriptor**.

## Server
#### TCPSocket.bind(_this_, _ip_, _port_)
```c
bool TCPSocket.bind(TCPSocketObject* this, CStr ip, long port);
```
Binds **this** server to a specific **ip** address and **port**.

Returns false if not successful.

#### TCPSocket.bindany(_this_, _port_)
```c
bool TCPSocket.bindany(TCPSocketObject* this, long port);
```
Binds **this** server to any of its **ip** addresses at the specific **port**. **This is recommended.**

Returns false if not successful.

#### TCPSocket.listen(_this_, _maxlisteners_)
```c
bool TCPSocket.listen(TCPSocketObject* this, long maxlisteners);
```
Sets the maximum clients that **this** server will service before refusing any more connections.

Returns false if not successful.

#### TCPSocket.accept(_this_, _mem_)
```c
TCPSocketObject* TCPSocket.accept(TCPSocketObject* this, MemoryObject* mem);
```
Blocks the current thread until a client connects. 

Upon connection, returns a copy of **this** socket with its filedescriptor set appropriately.

## Client
#### TCPSocket.connect(_this_, _ip_, _port_)
```c
bool TCPSocket.connect(TCPSocketObject* this, CStr ip, long port);
```
Attempts to connect to the server bound to **ip** at **port**.

Returns false if not successful.

## File
#### TCPSocket.read(_this_, _mem_)
```c
FileData* TCPSocket.read(TCPSocketObject* this, MemoryObject* mem);
```
Returns the [FileData](File.md) struct corresponding to the recieved data. See the demonstration above.

#### TCPSocket.readfile(_this_, _mem_)
```c
FileObject* TCPSocket.readfile(TCPSocketObject* this, MemoryObject* mem);
```
Returns the [FileObject] corresponding to the recieved data.

To save the file, first name the file path, then flush the file.

Here is the server:
```c
#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
long maxclients = 3;

// This program sends a copy of its 
// own binary executable to the client.
CStr filename = "TCPServer2.exe";

int main() {
    MemoryObject* mem = Memory.new();
    
    // the following assumes you are executing
    // TCPServer2.exe at its directory.
    FileObject* file = Memory.make(mem, File.new);
    File.name(file, filename);

    TCPSocketObject* server = Memory.make(mem, TCPSocket.new);
    TCPSocket.bindany(server, port);
    TCPSocket.listen(server, maxclients);
    
    // The following line blocks until a client connects.
    printf("Waiting for connections...\n");
    TCPSocketObject* connectedSock = TCPSocket.accept(server, mem);
    printf("Recieved a connection!\n");
    
    // Send the file
    long bytesSent = TCPSocket.writefile(connectedSock, file);
    printf("Sent the %ld bytes of %s to the connected client.\n", bytesSent, filename);

    decref(mem);
    return 0;
}
```
Here is the client that recieves the file:
```c
#include "stdc/lib.h"
#include <stdio.h>

long port = 5489;
CStr ip = "127.0.0.1";
CStr outfile = "temp.exe";

int main() {
    MemoryObject* mem = Memory.new();
    
    TCPSocketObject* client = Memory.make(mem, TCPSocket.new);
    TCPSocket.connect(client, ip, port);

    FileObject* data = TCPSocket.readfile(client, mem);
    printf("Server sent a file!\n");
    
    // Save the file
    File.name(data, outfile);
    long bytes = File.flush(data);
    printf("Saved the new file at \"%s\" (%ld bytes).\n", outfile, bytes);
    
    decref(mem);
    return 0;
}
```

#### TCPSocket.write(_this_, _msg_)
```c
long TCPSocket.write(TCPSocketObject* this, CStr msg);
```
Writes **msg** to the TCP buffer of **this**. 

Returns the number of bytes sent.

#### TCPSocket.writestr(_this_, _msg_)
```c
long TCPSocket.writestr(TCPSocketObject* this, StringObject* msg);
```
Writes the StringObject **msg** to the TCP buffer of **this**.

Returns the number of bytes sent.

#### TCPSocket.writefile(_this_, _file_)
```c
long TCPSocket.writefile(TCPSocketObject* this, FileObject* file);
```
Writes the bytes of **file** to the TCP buffer of **this**.

Returns the number of bytes sent.
