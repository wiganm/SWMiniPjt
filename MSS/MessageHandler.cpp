#include "UdpClient.h"
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
		const char* temp = udpClient->recv();
		memcpy(&messageId, temp, 4);
		if (messageId == 1320 && !mssSimulator.GetState())
		{
			continue;
		}
		switch (messageId)
		{
		case 1301: // 시나리오
		{
			cout << "----- 시나리오 정보 수신 -----" << endl;// 구현 부분
			MssScenarioMsg mssScenarioMsg;
			memcpy(&mssScenarioMsg, temp, sizeof(mssScenarioMsg));

			cout << "시작위치 : " << mssScenarioMsg.MssStartX << ", " << mssScenarioMsg.MssStartY << endl;
			mssSimulator.Initialize(mssScenarioMsg.MssStartX, mssScenarioMsg.MssStartY);
			// gui 전달
			break;
		}
		case 1310: // 운용제어
		{
			
			MssOpCommandMsg mssOpCommandMsg;
			memcpy(&mssOpCommandMsg, temp, sizeof(MssOpCommandMsg));

			if (mssOpCommandMsg.Launch == true)
			{
				mssSimulator.Start();
				cout << "운용제어 시작 수신" << endl;
			}
			else
			{
				cout << "운용제어 중지 수신" << endl;
				mssSimulator.Stop();
				cout << mssOpCommandMsg.MessageID << mssOpCommandMsg.Launch << endl;
			}
			// gui 연동
			break;
		}
		case 1320: // 요격
		{
			MssDirectionMsg mssDirectionMsg;
			memcpy(&mssDirectionMsg, temp, sizeof(MssDirectionMsg));
			if (mssDirectionMsg.SuccessDef == 1)
			{
				cout << "요격 성공" << endl;
				mssSimulator.Stop();
			}
			if (mssDirectionMsg.SuccessDef == 2)
			{
				cout << "요격 실패" << endl;
				mssSimulator.Stop();
			}
			if (mssDirectionMsg.SuccessDef == 2)
				cout << "요격 중" << endl;

			cout << "유도 방향" <<mssDirectionMsg.XDir << ", " << mssDirectionMsg.YDir << endl;
			mssSimulator.Move(mssDirectionMsg.XDir, mssDirectionMsg.YDir);
			cout << "현재 위치 : " << mssSimulator.GetX() << ", " << mssSimulator.GetY() << endl;
			// gui 전달
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
	char buf[1024] = { 0, };
	MssPositionMsg pos;
	pos.X_Pos = mssSimulator.GetX();
	pos.Y_Pos = mssSimulator.GetY();

	memcpy(buf, &pos, sizeof(pos));

	udpClient->send(buf, sizeof(MssPositionMsg));
}

void MessageHandler::SendMssState()
{
	char buf[1024] = { 0, };
	MssStateMsg msg;
	msg.MssState = mssSimulator.GetState();

	memcpy(buf, &msg, sizeof(MssStateMsg));

	udpClient->send(buf, sizeof(MssStateMsg));
}