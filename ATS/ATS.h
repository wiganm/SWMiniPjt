#pragma once
#include "MsgDatas.h"

#define MAX_BUF_LEN 1024

class UdpClient {
public:
	void Send(int socket); // AtsStateMsg, AtsPositionMsg
	void Receive(int socket); // AtsScenarioMsg, AtsOpCommandMsg, InterceptMsg
private:
	int pre_state = 0;
	int state = 0;

	AtsScenarioMsg atsScenarioMsg;
	AtsOpCommandMsg atsOpCommandMsg;
	InterceptMsg interceptMsg;
	AtsStateMsg atsStateMsg;
	AtsPositionMsg atsPositionMsg;

	AtsSimulation atsSimulation;
};

class MessaageHandler {
public:
	void MessageParser(int sockfd, int cur_state);

private:
	UdpClient udpClient;
};

class AtsSimulation {
public:
	bool Start(AtsScenarioMsg* atsScenarioMsg);
	bool Stop();
	void UpdateAtsPostion(AtsPositionMsg *atsPositionMsg, double initX, double initY, double velocity);
private:
	int period;
	double slope;
	double interceptY;
};


