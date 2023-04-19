#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "UdpClient.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;


UdpClient::UdpClient(const string ip, int client_port, int server_port) {
    // winsock �ʱ�ȭ
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        cout << "WSAStartup failed" << endl;
    }

    // ���� ����
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        cout << "socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
    }

    // Ŭ���̾�Ʈ ��Ʈ ����
    client_addr.sin_family = AF_INET; // ipv4 ���
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ��� ip
    client_addr.sin_port = htons(client_port); // Ŭ���̾�Ʈ ������Ʈ
    if (bind(sock, (struct sockaddr*)&client_addr, sizeof(client_addr)) == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << "\n";
        closesocket(sock);
        WSACleanup();
    }

    // ������ ����
    server_addr.sin_family = AF_INET; // ipv4 ���
    server_addr.sin_port = htons(server_port); // ������Ʈ ����
    server_addr_len = sizeof(server_addr);
    //if (inet_addr(ip.c_str()) <= 0) {
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        cout << "invalid address" << endl;
        closesocket(sock);
        WSACleanup();
    }
}

UdpClient::~UdpClient() {
    closesocket(sock);
    WSACleanup();
}

void UdpClient::send(const char* message) {
    sendto(sock, message, sizeof(message), 0,
        (const struct sockaddr*)&server_addr, sizeof(server_addr));
}

char* UdpClient::recv() {
    ZeroMemory(buffer, 1024);
    int len = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&server_addr, &server_addr_len);
    if (len == SOCKET_ERROR) {
        cout << "receive failed: " << WSAGetLastError() << endl;
    }
    return buffer;
}