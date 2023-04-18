#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "UdpServer.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;


UdpServer::UdpServer(const string ip, int server_port) {
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

    // ���� ���� ���ε�
    server_addr.sin_family = AF_INET; // ipv4 ���
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ��� ip
    server_addr.sin_port = htons(server_port); //  ������Ʈ
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << "\n";
        closesocket(sock);
        WSACleanup();
    }

    // Ŭ���̾�Ʈ init
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);

}

UdpServer::~UdpServer() {
    closesocket(sock);
    WSACleanup();
}

void UdpServer::send(int port, const char* message) {
    clientaddr.sin_port = htons(port);

    sendto(sock, message, sizeof(message), 0,
        (const struct sockaddr*)&server_addr, sizeof(server_addr));
}

char* UdpServer::recv() {
    int clientlen = sizeof(clientaddr);
    ZeroMemory(buffer, 1024);
    int len = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&clientaddr, &clientlen);
    if (len == SOCKET_ERROR) {
        cout << "receive failed: " << WSAGetLastError() << endl;
    }
    return buffer;
}
