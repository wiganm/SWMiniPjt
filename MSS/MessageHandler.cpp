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
		case 1301: // �ó�����
		{
			cout << "1301 : ����" << endl;// ���� �κ�
			MssScenarioMsg mssScenarioMsg;
			memcpy(&mssScenarioMsg, temp, sizeof(mssScenarioMsg));

			cout << mssScenarioMsg.MssStartX << mssScenarioMsg.MssStartY << mssScenarioMsg.Velocity << endl;

			// gui ����
			break;
		}
		case 1310: // �������
		{
			cout << "1310 : ����" << endl;
			MssOpCommandMsg mssOpCommandMsg;
			memcpy(&mssOpCommandMsg, temp, sizeof(MssOpCommandMsg));

			if (mssOpCommandMsg.Launch == true)
				mssSimulator.Start();
			else
				mssSimulator.Stop();
			cout << mssOpCommandMsg.MessageID << mssOpCommandMsg.Launch << endl;
			// gui ����
			break;
		}
		case 1320: // ���
		{
			cout << "1320 : ����" << endl;
			MssDirectionMsg mssDirectionMsg;
			memcpy(&mssDirectionMsg, temp, sizeof(MssDirectionMsg));

			cout << mssDirectionMsg.XDir << mssDirectionMsg.YDir << endl;

			// gui ����
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