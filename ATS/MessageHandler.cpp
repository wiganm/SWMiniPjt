#include <thread>
#include <iostream>
#include "pch.h"
#include "MessageHandler.h"


void MessageHandler::Listen()
{
	while (true)
	{
		int messageId;
		const char* temp = udpClient->recv();
		memcpy(&messageId, temp, 4);

		switch (messageId)
		{
		case 1501: // 공중위협 시나리오 메시지
			memcpy(&atsScenarioMsg, temp, sizeof(AtsScenarioMsg));
			break;

		case 1510: // 공중위협 기동 명령 메시지
			memcpy(&atsOpCommandMsg, temp, sizeof(AtsOpCommandMsg));
			break;

		case 1520: // 요격 이벤트
			memcpy(&interceptMsg, temp, sizeof(InterceptMsg));
			break;
		}
		if (atsStateMsg.AstState != atsOpCommandMsg.AstCommand) { // 기동 명령이 들어온 경우(UpdateAtsPostion 역할)
			if (atsOpCommandMsg.AstCommand) {
				atsSimulation.Start(&atsScenarioMsg);
			}
			else {
				//atsSimulation.Stop(&atsScenarioMsg, &atsPositionMsg, &interceptMsg);
			}
			atsStateMsg.AstState = atsOpCommandMsg.AstCommand;
			SendAtsState();
		}
		else{ // 기동 명령이 변화가 없는 경우
			if ((atsOpCommandMsg.AstCommand) && (!interceptMsg.SuccessDef)) { // 정상적으로 기동해야 하는 경우(기동명령 & 요격중)
				atsSimulation.UpdateAtsPostion(&atsPositionMsg);
				SendAtsPosition();
				
			}
			else { // 요격 성공 or 기동 명령 없는 경우
				//atsSimulation.Stop(&atsScenarioMsg, &atsPositionMsg, &interceptMsg);
				//continue;
			}
		}
	}
}

MessageHandler::MessageHandler(){
	const string ip = "127.0.0.1";
	int client_port = 8888;
	int server_port = 4444;
	udpClient = new UdpClient(ip, client_port, server_port);
}

void MessageHandler::ListenStart(){
	thread t(&MessageHandler::Listen, this);
	t.detach();
}

void MessageHandler::SendAtsPosition(){
	char buf[1024] = { 0, };
	memcpy(buf, &atsPositionMsg, sizeof(atsPositionMsg));
	udpClient->send(buf);
}
void MessageHandler::SendAtsState(){ // AtsSimulation::UpdateAtsState()는 생략
	char buf[1024] = { 0, };
	memcpy(buf, &atsStateMsg, sizeof(atsStateMsg));
	udpClient->send(buf);
}