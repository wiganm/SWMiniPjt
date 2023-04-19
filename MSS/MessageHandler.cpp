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
		case 1301: // 시나리오
			cout << "미사일 상태메시지 수신" << endl;// 구현 부분
			MssPositionMsg data;
			memcpy(&data, temp, sizeof(MssPositionMsg));
			int x = data.X_Pos;
			int y = data.Y_Pos;
			break;
		case 1310: // 운용msg
		
			break;
		case 1320: // 방향msg
			cout << "공중위협 상태 메시지" << endl;// 구현 부분
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