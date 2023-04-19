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