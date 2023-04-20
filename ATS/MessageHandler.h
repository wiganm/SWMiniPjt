#pragma once
#include <thread>
#include <cstring>
#include "MsgDatas.h"
#include "UdpClient.h"
#include "AtsSimulation.h"



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
	//AtsPositionMsg atsPositionMsg;

	//시뮬레이션 구조체
	AtsSimulation* atsSimulation;
public:
	MessageHandler(AtsSimulation* atsSim);
	//~MessageHandler();
	void ListenStart();
	void SendAtsPosition();
	void SendAtsState();
};