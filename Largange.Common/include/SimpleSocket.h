#ifndef SIMPLESOCKET_H
#define SIMPLESOCKET_H

#ifdef _WIN_PLATFORM_
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include <iostream>
#include <string>

class SimpleSocket
{
public:
    SimpleSocket();
    ~SimpleSocket();

    int create();
    void connect(int sockfd, const std::string &address, int port);
    void close(int sockfd);
};

#endif // SIMPLESOCKET_H