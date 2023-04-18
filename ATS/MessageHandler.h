#include <cstring>
#include "MsgDatas.h"
#include "UdpClient.h"
#include "AtsSimulation.h"
#pragma once


class MessageHandler
{
private:
	UdpClient* udpClient;
	//void MessageParse();
	void Listen();

	//�޽��� ����ü
	AtsScenarioMsg atsScenarioMsg;
	AtsOpCommandMsg atsOpCommandMsg;
	InterceptMsg interceptMsg;
	AtsStateMsg atsStateMsg;
	AtsPositionMsg atsPositionMsg;

	//�ùķ��̼� ����ü
	AtsSimulation atsSimulation;
public:
	MessageHandler();
	//~MessageHandler();
	void ListenStart();
	void SendAtsPosition();
	void SendAtsState();
};

/*
/// <summary>
/// UdpClient
/// </summary>
void UdpClient::Send(int socket) {
	char send_buf[MAX_BUF_LEN];

	if ((state == 1510) && (state != pre_state)) { // ����� ������ ���� = �� ���� �۽�(���� ���� != ���� ����)
		if (atsOpCommandMsg.AstCommand == 1) { // �⵿ ���� ���
			atsStateMsg.AstState = atsSimulation.Start(&atsScenarioMsg);
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // �������� ���¸� buffer�� copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state;
		}
	}
	else if ((state == 1510) || (state == 1520)) { //�������� �۽�
		if ((atsOpCommandMsg.AstCommand == 1) && (interceptMsg.SuccessDef == 0)) { // �⵿ ���� & ��� �̿Ϸ�
			atsSimulation.UpdateAtsPostion(&atsPositionMsg, atsScenarioMsg.AtsStartX, atsScenarioMsg.AtsStartY, atsScenarioMsg.Velocity);
			memcpy(send_buf, &atsPositionMsg, sizeof(atsPositionMsg)); // �������� ���¸� buffer�� copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
		}
		else {
			atsStateMsg.AstState = atsSimulation.Stop();
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // �������� ���¸� buffer�� copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state = 0;
		}
	}
}
*/