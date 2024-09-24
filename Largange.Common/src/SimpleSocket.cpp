#include "SimpleSocket.h"

SimpleSocket::SimpleSocket()
{
#ifdef _WIN_PLATFORM_
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        exit(1);
    }
#endif
}

SimpleSocket::~SimpleSocket()
{
#ifdef _WIN_PLATFORM_
    WSACleanup();
#endif
}

int SimpleSocket::create()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }
    return sockfd;
}

void SimpleSocket::connect(int sockfd, const std::string &address, int port)
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &server_addr.sin_addr);

    if (::connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        exit(1);
    }
}

void SimpleSocket::close(int sockfd)
{
#ifdef _WIN_PLATFORM_
    closesocket(sockfd);
#else
    ::close(sockfd);
#endif
}