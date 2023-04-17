#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;


class UdpClient {
private:
    SOCKET sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char buffer[1024] = { 0 }; // ���� �ʱ�ȭ

public:
    UdpClient(const string& ip, int client_port, int server_port) {
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
        if (inet_addr(ip.c_str()) <= 0){
        // if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
            cout << "invalid address" << endl;
            closesocket(sock);
            WSACleanup();
        }
    }

    ~UdpClient() {
        closesocket(sock);
        WSACleanup();
    }

    void send(const string& message) {
        sendto(sock, message.c_str(), message.size(), 0,
            (const struct sockaddr*)&server_addr, sizeof(server_addr));
    }

    string recv() {
        ZeroMemory(buffer, 1024);
        int len;
        struct sockaddr_in addr;
        int addr_len = sizeof(addr);
        len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
        if (len == SOCKET_ERROR) {
            cout << "receive failed: " << WSAGetLastError() << endl;
        }
        return string(buffer, len);
    }
};
