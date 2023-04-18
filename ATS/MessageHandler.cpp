#include <thread>
#include <iostream>
#include "MsgDatas.h"
#include "UdpClient.h"
#include "MessageHandler.h"

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
		case 1501: // �������� �ó����� �޽��� > 
			
			break;

		case 1510: // �������� �⵿ ��� �޽���
			// ���� �κ�
			break;

		case 1520: // 
			// ���� �κ�
			break;
		}

	}
}

/*
	if (state == 1501) { //�ó����� �Է�
		memcpy(&atsScenarioMsg, recv_buf, sizeof(atsScenarioMsg));
	}
	else if (state == 1510) { // �������� ���(�⵿ ����, ����)
		memcpy(&atsOpCommandMsg, recv_buf, sizeof(atsOpCommandMsg));
	}
	else if (state == 1520) { // ����̺�Ʈ (���������->�����������Ǳ�)
		memcpy(&interceptMsg, recv_buf, sizeof(interceptMsg));
	}
*/

MessageHandler::MessageHandler()
{
	const string ip = "127.0.0.1";
	int client_port = 8888;
	int server_port = 4444;
	udpClient = new UdpClient(ip, client_port, server_port);
}

void MessageHandler::ListenStart()
{
	thread t(&MessageHandler::Listen, this);
	t.detach();
}

void MessageHandler::SendAtsPosition(double x, double y)
{
	char buf[1024] = { 0, };
	AtsPositionMsg pos;
	pos.X_AstLoc = x;
	pos.Y_AstLoc = y;

	memcpy(buf, &pos, sizeof(pos));

	udpClient->send(buf);
}
void MessageHandler::SendAtsState()
{
	char buf[1024] = { 0, };
	MssPositionMsg pos;

	memcpy(buf, &pos, sizeof(pos));

	udpClient->send(buf);
}