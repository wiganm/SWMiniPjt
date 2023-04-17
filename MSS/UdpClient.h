#include <iostream>
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
    char buffer[1024];

public:
    void send(const string& message);
    string recv();
};