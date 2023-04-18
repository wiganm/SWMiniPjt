#include <string>
#include "UdpServer.h"
#include "GCSClass.h"
#pragma once

using namespace std;

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

	MissileCalculator missileCalculator;
	UdpServer* udpServer;
	void Listen();
public:
	MessageHandler();
	//~MessageHandler();
	void ListenStart();
	void SendMssOpMsg(bool opMsg);
	void SendMssScenarioMsg(double xStart, double yStart);
	void SendAtsScenarioMsg(double xStart, double yStart, double xDest, double yDest, double velocity, int type);
};