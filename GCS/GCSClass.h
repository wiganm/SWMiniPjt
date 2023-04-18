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

class MissileCalculator { // 미사일 방향벡터 게산
public:
	MssDirectionMsg SetAndGetDirMss(double mssPosX, double mssPosY, double atsPosX, double atsPosY);
	// 미사일 방향 세팅 함수
	void SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist);
	void SendSuccessMsg(); // 구현해야함 통신사용 // 스테이트변경도 추가해서 전송
private:
	MssDirectionMsg mssDirectionMsg;
	InterceptMsg interceptMsg;
};

class Warning {
	bool LaunchOk(double mssX, double mssY, double atsX, double atsY);
};
