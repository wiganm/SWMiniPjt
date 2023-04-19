#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma once

using namespace std;

class UdpServer
{
private:
    SOCKET sock;
    sockaddr_in server_addr;
    sockaddr_in clientaddr;
    int server_addr_len;
    char buffer[1024] = { 0, }; // 버퍼 초기화

public:
    UdpServer(const string ip, int server_port);
    ~UdpServer();
    void send(int port, const char* message);
    char* recv();
};