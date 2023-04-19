#include "UdpClient.h"
#include <thread>
#include <iostream>
#include <MessageHandler.h>
#include "MSS.h"
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
		{
			MssScenarioMsg scen_msg;
			memcpy(&scen_msg, temp, sizeof(MssScenarioMsg));

			mssSimulator.Initialize(scen_msg.MssStartX, scen_msg.MssStartY); // 시나리오 시작값 세팅

			break;
		}
		case 1310: // 운용msg
		{
			MssOpCommandMsg op_msg;
			memcpy(&op_msg, temp, sizeof(MssOpCommandMsg));

			mssSimulator.Start(op_msg.Launch); // 메시지에 따라 운용 시작
			//mssSimulator.
			break;
		}
		case 1320: // 방향msg
		{
			MssDirectionMsg dir_msg;
			memcpy(&dir_msg, temp, sizeof(MssDirectionMsg));
			mssSimulator.Move(dir_msg.XDir, dir_msg.YDir);
			break;
		}
		}
	}
}

MessageHandler::MessageHandler(MssSimulator mssSimulator)
{
	const string ip = "127.0.0.1";
	int client_port = 7777;
	int server_port = 4444;
	udpClient = new UdpClient(ip, client_port, server_port);
	this->mssSimulator = mssSimulator;
}

void MessageHandler::ListenStart()
{
	thread t(&MessageHandler::Listen, this);
	t.detach();
}

void MessageHandler::SendMssPosition()
{
	char buf[sizeof(MssPositionMsg)] = { 0 };
	MssPositionMsg pos;
	pos.X_Pos = mssSimulator.GetX();
	pos.Y_Pos = mssSimulator.GetY();
	memcpy(buf, &pos, sizeof(pos));

	udpClient->send(buf, sizeof(pos));
}