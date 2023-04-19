#include "UdpClient.h"
#include <thread>
#include <iostream>
#include <MessageHandler.h>
#include "MsgDatas.h"

using namespace std;


void MessageHandler::Listen()
{
	while (true)
	{
		int messageId;
		const char* temp = udpClient->recv();
		memcpy(&messageId, temp, 4);

		switch (messageId)
		{
		case 1301: // �ó�����
			cout << "�̻��� ���¸޽��� ����" << endl;// ���� �κ�
			MssPositionMsg data;
			memcpy(&data, temp, sizeof(MssPositionMsg));
			int x = data.X_Pos;
			int y = data.Y_Pos;
			break;
		case 1310: // ���msg
		
			break;
		case 1320: // ����msg
			cout << "�������� ���� �޽���" << endl;// ���� �κ�
			break;
		}
	}
}

MessageHandler::MessageHandler()
{
	const string ip = "127.0.0.1";
	int client_port = 7777;
	int server_port = 4444;
	udpClient = new UdpClient(ip, client_port, server_port);
}

void MessageHandler::ListenStart()
{
	thread t(&MessageHandler::Listen, this);
	t.detach();
}

void MessageHandler::SendMssPosition(double x, double y)
{
	char buf[sizeof(MssPositionMsg)] = { 0 };
	MssPositionMsg pos;
	pos.X_Pos = x;
	pos.Y_Pos = y;
	memcpy(buf, &pos, sizeof(pos));

	udpClient->send(buf, sizeof(pos));
}