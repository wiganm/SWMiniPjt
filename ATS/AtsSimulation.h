#pragma once
#include <cmath>
#include "MsgDatas.h"

class AtsSimulation {
public:
	void ScenarioSetting(AtsScenarioMsg* atsScenarioMsg);
	void Start();
	void Stop();
	// void Stop(AtsScenarioMsg *atsScenarioMsg, AtsPositionMsg *atsPositionMsg, InterceptMsg *interceptMsg);
	void UpdateAtsPostion();
	AtsSimulation();
	bool GetState();
	AtsPositionMsg GetPos();
private:
	int time;
	double startX;
	double startY;
	double velocity;
	double unitVectorX;
	double unitVectorY;
	bool state = false;
	AtsPositionMsg atsPositionMsg;
};