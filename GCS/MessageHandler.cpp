#include "pch.h"

#include "UdpServer.h"
#include <thread>
#include <iostream>
#include "MessageHandler.h"
#include "MsgDatas.h"
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
		case 3110: // 미사일 상태 메시지
			cout << "미사일 상태메시지 수신" << endl;// 구현 부분
			MssStateMsg mssStateMsg;
			memcpy(&mssStateMsg, temp, sizeof(MssStateMsg));

			opControl.SetMssState(mssStateMsg.MssState);
			// gui 전달
			break;
		case 3120: // 미사일 포지션 메시지
			MssPositionMsg mssPositionMsg;
			memcpy(&mssPositionMsg, temp, sizeof(MssPositionMsg));

			opControl.SetMssPosMsg(mssPositionMsg);

			MssPositionX = mssPositionMsg.X_Pos; MssPositionY = mssPositionMsg.Y_Pos;
			missileCalculator.SetDirMss(MssPositionX, MssPositionY, AtsPositionX, AtsPositionY); // 미사일 포지션 수신시 미사일 방향 업데이트
			missileCalculator.SetInterceptSuccess(MssPositionX, MssPositionY, AtsPositionX, AtsPositionY, AtsDestPosX, AtsDestPosY, 5); // 성공 결과 확인

			// gui 연동
			break;
		case 5101: // 공중위협 상태 메시지
			cout << "공중위협 상태 메시지" << endl;// 구현 부분
			AtsStateMsg atsStateMsg;
			memcpy(&atsStateMsg, temp, sizeof(AtsStateMsg));
			opControl.SetAtsState(atsStateMsg.AstState);
			// gui 전달
			break;
		case 5110: // 공중위협 포지션 메시지
			cout << "공중위협 포지션 메시지" << endl;// 구현 부분
			AtsPositionMsg atsPosMsg;
			memcpy(&atsPosMsg, temp, sizeof(AtsPositionMsg));

			opControl.SetAtsPosMsg(atsPosMsg);
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

void MessageHandler::SendMssOpMsg(bool opMsg)
{
	char buf[1024] = { 0, };
	MssOpCommandMsg msg;
	msg.Launch = opMsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg)); // enum으로 ip 넣어도될듯 현재 7777이 Mss, 8888이 Ats
}

void MessageHandler::SendMssScenarioMsg(MssScenarioMsg mmsg) {
	char buf[1024] = { 0, };
	MssScenarioMsg msg;
	msg = mmsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg)); // enum으로 ip 넣어도될듯 현재 7777이 Mss, 8888이 Ats
}

void MessageHandler::SendAtsScenarioMsg(AtsScenarioMsg amsg) {
	char buf[1024] = { 0, };
	AtsScenarioMsg msg;
	
	msg = amsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(8888, buf, sizeof(msg)); // enum으로 ip 넣어도될듯 현재 7777이 Mss, 8888이 Ats
}

void MessageHandler::SendInterceptMsg(bool intermsg) {
	char buf[1024] = { 0, };
	InterceptMsg msg;
	msg.SuccessDef = intermsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg));
	udpServer->send(8888, buf, sizeof(msg)); // enum으로 ip 넣어도될듯 현재 7777이 Mss, 8888이 Ats
}

void MessageHandler::SendMssDir(MssDirectionMsg dirmsg) {
	char buf[1024] = { 0, };
	MssDirectionMsg msg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf, sizeof(msg));
}
