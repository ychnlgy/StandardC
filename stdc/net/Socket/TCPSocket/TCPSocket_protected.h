#ifndef STDC_NET_SOCKET_PROTECTED
#define STDC_NET_SOCKET_PROTECTED

#include <netinet/in.h>
// sockaddr_in

#include "stdc/lib.h"

#define BUFSIZE 1024

struct TCPSocketObject {
    int                     filedesciptor;
    struct sockaddr_in      address;
    size_t                  addrlen;
    char                    buffer[BUFSIZE];
};

#endif
