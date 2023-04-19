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
	void SetDirMss(double mssPosX, double mssPosY, double atsPosX, double atsPosY);
	// �̻��� ���� ���� �Լ�
	void SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist);
	void SendSuccessMsg(bool success); // �����ؾ��� ��Ż�� // ������Ʈ���浵 �߰��ؼ� ����
private:
	MssDirectionMsg mssDirectionMsg;
	InterceptMsg interceptMsg;
};

class Warning {
public:
	bool LaunchOk(double mssStartX, double mssStartY, double atsX, double atsY);
};


class OperationControl {
public:
	void SetMssOpCommandMsg(double mssStartX, double mssStartY, double atsPosX, double atsPosY, bool launch); //�߻� ��ư ���� �� ���
	void LaunchMss();
	void SetApsOpCommandMsg(bool command);

	void SetMssState(bool state);
	void SetAtsState(bool state);
	void SetMssDirMsg(MssDirectionMsg mssDirectionMsg);
	void SetMssPosMsg(MssPositionMsg msg);
	void SetAtsPosMsg(AtsPositionMsg msg);

	bool GetMssState();
	bool GetAtsState();
	MssDirectionMsg GetMssDirMsg();
	MssPositionMsg GetMssPosMsg();
	AtsPositionMsg GetAtsPosMsg();
private:
	MssOpCommandMsg mssOpCommandMsg;
	MissileCalculator mssCalculator;

	bool mssState;
	bool atsState;
	MssDirectionMsg mssDirectionMsg;
	MssPositionMsg mssPosMsg;
	AtsPositionMsg atsPosMsg;
};

OperationControl opControl; // gui ���� ������ ����ִ� ��ü