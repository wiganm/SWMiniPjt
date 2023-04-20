#include "pch.h"

using namespace std;


void MessageHandler::Listen()
{
	while (true)
	{

		int messageId;
		const char* temp = udpClient->recv();
		memcpy(&messageId, temp, 4);
		if (messageId == 1520 && !atsSimulation->GetState())
		{
			continue;
		}
		switch (messageId)
		{
		case 1501: // 공중위협 시나리오 메시지
		{
			memcpy(&atsScenarioMsg, temp, sizeof(AtsScenarioMsg));
			atsSimulation->ScenarioSetting(&atsScenarioMsg);
			cout << "공중위협 시나리오 수신" << endl;
			break;
		}
		case 1510: // 공중위협 기동 명령 메시지
		{
			memcpy(&atsOpCommandMsg, temp, sizeof(AtsOpCommandMsg));
			cout << "공중위협 기동 명령 수신" << endl;
			if (atsOpCommandMsg.AstCommand == true)
				atsSimulation->Start();
			else
				atsSimulation->Stop();
			break;
		}
		case 1520: // 요격 이벤트
		{
			memcpy(&interceptMsg, temp, sizeof(InterceptMsg));
			cout << "공중위협 요격 이벤트 수신 : " << interceptMsg.SuccessDef << endl;
			break;
		}
		}
	}
}

MessageHandler::MessageHandler(AtsSimulation* atsSim){
	const string ip = "127.0.0.1";
	int client_port = 8888;
	int server_port = 4444;
	udpClient = new UdpClient(ip, client_port, server_port);
	atsSimulation = atsSim;
}

void MessageHandler::ListenStart(){
	thread t(&MessageHandler::Listen, this);
	t.detach();
}

void MessageHandler::SendAtsPosition(){
	char buf[sizeof(AtsPositionMsg)] = { 0, };
	AtsPositionMsg msg = atsSimulation->GetPos();
	memcpy(buf, &msg, sizeof(AtsPositionMsg));
	udpClient->send(buf, sizeof(AtsPositionMsg));
}
void MessageHandler::SendAtsState(){ // AtsSimulation::UpdateAtsState()는 생략
	char buf[sizeof(AtsStateMsg)] = { 0, };
	memcpy(buf, &atsStateMsg, sizeof(AtsStateMsg));
	udpClient->send(buf, sizeof(AtsStateMsg));
}