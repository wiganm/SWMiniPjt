#include "pch.h"

#include <thread>
#include <iostream>

#include "MessageHandler.h"
#include "GCSClass.h"

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
			{
				MssStateMsg mssStateMsg;
				memcpy(&mssStateMsg, temp, sizeof(MssStateMsg));

				MssState = mssStateMsg.MssState;
				operationControl->SetMssState(mssStateMsg.MssState);

				// gui ����
				break;
			}
			case 3120: // �̻��� ������ �޽���
			{
				MssPositionMsg mssPositionMsg;
				memcpy(&mssPositionMsg, temp, sizeof(MssPositionMsg));

				operationControl->SetMssPosMsg(mssPositionMsg);
				
				MssPositionX = mssPositionMsg.X_Pos; MssPositionY = mssPositionMsg.Y_Pos;
				SendMssDir(MissileCalculator::SetDirMss(MssPositionX, MssPositionY, AtsPositionX, AtsPositionY)); // �̻��� ������ ���Ž� �̻��� ���� ������Ʈ
				
				int result = MissileCalculator::SetInterceptSuccess(MssPositionX, MssPositionY, AtsPositionX, AtsPositionY, AtsDestPosX, AtsDestPosY, 5);
				SendInterceptMsg(result); // ��� ���� ����
				if (result == 1 || result == 2)
				{
					SendAtsOpMsg(false);
					SendMssOpMsg(false);
				}
				
				
				// gui ����
				break;
			}
			case 5101: // �������� ���� �޽���
			{
				AtsStateMsg atsStateMsg;
				memcpy(&atsStateMsg, temp, sizeof(AtsStateMsg));

				AtsState = atsStateMsg.AstState;
				operationControl->SetAtsState(atsStateMsg.AstState);

				// gui ����
				break;
			}
			case 5110: // �������� ������ �޽���
			{
				AtsPositionMsg atsPosMsg;
				memcpy(&atsPosMsg, temp, sizeof(AtsPositionMsg));

				AtsPositionX = atsPosMsg.X_AstLoc; AtsPositionY = atsPosMsg.Y_AstLoc;
				operationControl->SetAtsPosMsg(atsPosMsg);
				break;
			}
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

void MessageHandler::SendMssOpMsg(bool opMsg)
{
	char buf[1024] = { 0, };
	MssOpCommandMsg msg;
	msg.Launch = opMsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg)); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendAtsOpMsg(bool opMsg) {
	char buf[1024] = { 0, };
	AtsOpCommandMsg msg;
	msg.AstCommand = opMsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(8888, buf, sizeof(msg)); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendMssScenarioMsg() {
	char buf[1024] = { 0, };
	MssScenarioMsg msg;
	msg = scenarioSetting->GetMssScenarioMsg();

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg)); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendAtsScenarioMsg() {
	char buf[1024] = { 0, };
	AtsScenarioMsg msg;
	
	msg = scenarioSetting->GetAtsScenarioMsg();

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(8888, buf, sizeof(msg)); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendInterceptMsg(bool intermsg) {
	char buf[1024] = { 0, };
	InterceptMsg msg;
	msg.SuccessDef = intermsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg));
	udpServer->send(8888, buf, sizeof(msg)); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendMssDir(MssDirectionMsg dirmsg) {
	char buf[1024] = { 0, };
	MssDirectionMsg msg;
	msg = dirmsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg));
}