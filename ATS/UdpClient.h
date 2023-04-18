#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma once

using namespace std;

class UdpClient
{
private:
    SOCKET sock;
    sockaddr_in server_addr;
    sockaddr_in client_addr;
    int server_addr_len;
    char buffer[1024] = { 0, }; // 버퍼 초기화

public:
    UdpClient(const string ip, int client_port, int server_port);
    ~UdpClient();
    void send(const char* message);
    char* recv();
};