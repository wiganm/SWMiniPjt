#include <iostream>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "UdpServer.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;


UdpServer::UdpServer(const string ip, int server_port) {
    // winsock 초기화
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        cout << "WSAStartup failed" << endl;
    }

    // 소켓 생성
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        cout << "socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
    }

    // 서버 소켓 바인딩
    server_addr.sin_family = AF_INET; // ipv4 사용
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 허용 ip
    server_addr.sin_port = htons(server_port); //  지정포트
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << "\n";
        closesocket(sock);
        WSACleanup();
    }

    // 클라이언트 init
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
