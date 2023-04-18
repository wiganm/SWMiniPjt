#include "UdpServer.h"
#include <thread>
#include <iostream>
#include "MessageHandler.h"
#include "MsgDatas.h"

using namespace std;


void MessageHandler::Listen()
{
	while (true)
	{
		int messageId;
		const char* temp = udpServer->recv();
		memcpy(&messageId, temp, 4);
		
		switch (messageId)
		{
		case 3110: // �̻��� ���� �޽���
			// ���� �κ�
			break;
		case 3120: // �̻��� ������ �޽���
			// ���� �κ�
			break;
		case 5101: // �������� ���� �޽���
			// ���� �κ�
			break;
		case 5110: // �������� ������ �޽���
			// ���� �κ�
			break;
		}

	}
}

MessageHandler::MessageHandler()
{
	const string ip = "127.0.0.1";
	int server_port = 4444;
	udpServer = new UdpServer(ip, server_port);
}

void MessageHandler::ListenStart()
{
	thread t(&MessageHandler::Listen, this);
	t.detach();
}
