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

	//�޽��� ����ü
	AtsScenarioMsg atsScenarioMsg;
	AtsOpCommandMsg atsOpCommandMsg;
	InterceptMsg interceptMsg;
	AtsStateMsg atsStateMsg;
	//AtsPositionMsg atsPositionMsg;

	//�ùķ��̼� ����ü
	AtsSimulation* atsSimulation;
public:
	MessageHandler(AtsSimulation* atsSim);
	//~MessageHandler();
	void ListenStart();
	void SendAtsPosition();
	void SendAtsState();
};