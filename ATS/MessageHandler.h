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

	//메시지 구조체
	AtsScenarioMsg atsScenarioMsg;
	AtsOpCommandMsg atsOpCommandMsg;
	InterceptMsg interceptMsg;
	AtsStateMsg atsStateMsg;
	AtsPositionMsg atsPositionMsg;

	//시뮬레이션 구조체
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

	if ((state == 1510) && (state != pre_state)) { // 명령을 수신한 상태 = 한 번만 송신(이전 상태 != 현재 상태)
		if (atsOpCommandMsg.AstCommand == 1) { // 기동 시작 명령
			atsStateMsg.AstState = atsSimulation.Start(&atsScenarioMsg);
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // 공중위협 상태를 buffer에 copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state;
		}
	}
	else if ((state == 1510) || (state == 1520)) { //지속적인 송신
		if ((atsOpCommandMsg.AstCommand == 1) && (interceptMsg.SuccessDef == 0)) { // 기동 시작 & 요격 미완료
			atsSimulation.UpdateAtsPostion(&atsPositionMsg, atsScenarioMsg.AtsStartX, atsScenarioMsg.AtsStartY, atsScenarioMsg.Velocity);
			memcpy(send_buf, &atsPositionMsg, sizeof(atsPositionMsg)); // 공중위협 상태를 buffer에 copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
		}
		else {
			atsStateMsg.AstState = atsSimulation.Stop();
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // 공중위협 상태를 buffer에 copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state = 0;
		}
	}
}
*/