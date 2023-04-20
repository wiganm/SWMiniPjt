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

	double MssStartPositionX;
	double MssStartPositionY;

	bool BWarning;
	
	OperationControl* operationControl = new OperationControl();

	double AtsPositionX;
	double AtsPositionY;
	bool AtsState;
	double AtsDestPosX;
	double AtsDestPosY;

	int interstella = 0;

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

	double GetMssPositionX();
	double GetMssPositionY();
	double GetAtsPositionX();
	double GetAtsPositionY();

	bool GetWarning();

	int isEnd();
};