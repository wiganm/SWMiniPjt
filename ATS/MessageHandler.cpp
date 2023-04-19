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
		case 1501: // �������� �ó����� �޽���
			memcpy(&atsScenarioMsg, temp, sizeof(AtsScenarioMsg));
			break;

		case 1510: // �������� �⵿ ��� �޽���
			memcpy(&atsOpCommandMsg, temp, sizeof(AtsOpCommandMsg));
			break;

		case 1520: // ��� �̺�Ʈ
			memcpy(&interceptMsg, temp, sizeof(InterceptMsg));
			break;
		}
		if (atsStateMsg.AstState != atsOpCommandMsg.AstCommand) { // �⵿ ����� ���� ���(UpdateAtsPostion ����)
			if (atsOpCommandMsg.AstCommand) {
				atsSimulation.Start(&atsScenarioMsg);
			}
			else {
				//atsSimulation.Stop(&atsScenarioMsg, &atsPositionMsg, &interceptMsg);
			}
			atsStateMsg.AstState = atsOpCommandMsg.AstCommand;
			SendAtsState();
		}
		else{ // �⵿ ����� ��ȭ�� ���� ���
			if ((atsOpCommandMsg.AstCommand) && (!interceptMsg.SuccessDef)) { // ���������� �⵿�ؾ� �ϴ� ���(�⵿��� & �����)
				atsSimulation.UpdateAtsPostion(&atsPositionMsg);
				SendAtsPosition();
				
			}
			else { // ��� ���� or �⵿ ��� ���� ���
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
void MessageHandler::SendAtsState(){ // AtsSimulation::UpdateAtsState()�� ����
	char buf[1024] = { 0, };
	memcpy(buf, &atsStateMsg, sizeof(atsStateMsg));
	udpClient->send(buf);
}