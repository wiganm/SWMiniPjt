#pragma once
#include "MsgDatas.h"

class ScenarioSetting
{
public:
	ScenarioSetting();
	~ScenarioSetting();
	void SetAtsScenarioMsg(double initX, double initY, double destX, double destY, double velocity, int atstype);
	void SetMssScenarioMsg(double initX, double initY);
	AtsScenarioMsg GetAtsScenarioMsg();
	MssScenarioMsg GetMssScenarioMsg();
private:
	AtsScenarioMsg atsScenarioMsg;
	MssScenarioMsg mssScenarioMsg;
};

class MissileCalculator { // �̻��� ���⺤�� �Ի�
public:
	MssOpCommandMsg SetAndGetMssOp(double mssPosX, double mssPosY, double atsPosX, double atsPosY, bool Launch);
private:
	MssOpCommandMsg mssOpCommandMsg;
};
