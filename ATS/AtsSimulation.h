#pragma once
#include "MsgDatas.h"

class AtsSimulation {
public:
	void Start(AtsScenarioMsg* atsScenarioMsg);
	void Stop();
	// void Stop(AtsScenarioMsg *atsScenarioMsg, AtsPositionMsg *atsPositionMsg, InterceptMsg *interceptMsg);
	void UpdateAtsPostion(AtsPositionMsg* atsPositionMsg);
private:
	int time;
	double startX;
	double startY;
	double velocity;
	double unitVectorX;
	double unitVectorY;
};