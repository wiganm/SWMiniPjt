#pragma once

class AtsSimulation {
public:
	bool Start(AtsScenarioMsg* atsScenarioMsg);
	bool Stop();
	void UpdateAtsPostion(AtsPositionMsg* atsPositionMsg, double initX, double initY, double velocity);
	void UpdateAtsState();
private:
	int period;
	double slope;
	double interceptY;
};