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
	MssDirectionMsg SetAndGetDirMss(double mssPosX, double mssPosY, double atsPosX, double atsPosY);
	// �̻��� ���� ���� �Լ�
	void SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist);
	void SendSuccessMsg(); // �����ؾ��� ��Ż�� // ������Ʈ���浵 �߰��ؼ� ����
private:
	MssDirectionMsg mssDirectionMsg;
	InterceptMsg interceptMsg;
};

class Warning {
	bool LaunchOk(double mssX, double mssY, double atsX, double atsY);
};
