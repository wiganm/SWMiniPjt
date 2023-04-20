#pragma once
#include "UdpServer.h"
#include "MsgDatas.h"
#include "GCSClass.h"


class MessageHandler
{
private:
	double MssPositionX;
	double MssPositionY;
	bool MssState;

	
	OperationControl* operationControl = new OperationControl();

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
	void SendMssScenarioMsg();
	void SendAtsScenarioMsg();
	void SendInterceptMsg(bool intermsg);
	void SendMssDir(MssDirectionMsg dirmsg);
	ScenarioSetting* scenarioSetting = new ScenarioSetting();

};