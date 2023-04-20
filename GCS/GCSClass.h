#pragma once
#include "MsgDatas.h"
// #include "MessageHandler.h"

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

class MissileCalculator { // 미사일 방향벡터 게산
public:
	//MissileCalculator();
	static MssDirectionMsg SetDirMss(double mssPosX, double mssPosY, double atsPosX, double atsPosY);
	// 미사일 방향 세팅 함수
	static bool SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist);
	void SendSuccessMsg(bool success); // 구현해야함 통신사용 // 스테이트변경도 추가해서 전송
private:
	InterceptMsg interceptMsg;
};

class Warning {
public:
	bool LaunchOk(double mssStartX, double mssStartY, double atsX, double atsY);
};


class OperationControl {
public:
	OperationControl();
	~OperationControl();

	void SetMssOpCommandMsg(double mssStartX, double mssStartY, double atsPosX, double atsPosY, bool launch); //발사 버튼 누를 때 사용
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