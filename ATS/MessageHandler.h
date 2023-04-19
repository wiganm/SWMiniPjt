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