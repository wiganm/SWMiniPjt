#pragma once
#include "UdpServer.h"
#include "MsgDatas.h"

class MessageHandler
{
private:
	double MssPositionX;
	double MssPositionY;
	bool MssState;

	double AtsPositionX;
	double AtsPositionY;
	bool AtsState;
	double AtsDestPosX;
	double AtsDestPosY;

	UdpServer* udpServer;
	void Listen();
public:
	MessageHandler();
	//~MessageHandler();
	void ListenStart();
	void SendMssOpMsg(bool opMsg);
	void SendAtsOpMsg(bool opMsg);
	void SendMssScenarioMsg(MssScenarioMsg mmsg);
	void SendAtsScenarioMsg(AtsScenarioMsg amsg);
	void SendInterceptMsg(bool intermsg);
	void SendMssDir(MssDirectionMsg dirmsg);
};