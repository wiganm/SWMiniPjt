#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "MsgDatas.h"
#include "GCSClass.h"
#include "MessageHandler.h"

using namespace std;

MessageHandler msgHandle;

/// <summary>
/// ScenarioSetting
/// </summary>
void ScenarioSetting::SetAtsScenarioMsg(double initX, double initY, double destX, double destY, double velocity, int atstype) {
	atsScenarioMsg.AtsStartX = initX;
	atsScenarioMsg.AtsStartY = initY;
	atsScenarioMsg.AtsDestiationX = destX;
	atsScenarioMsg.AtsDestiationY = destY;
	atsScenarioMsg.Velocity = velocity;
	atsScenarioMsg.atsType = atstype;

	msgHandle.SendAtsScenarioMsg(atsScenarioMsg);
}

void ScenarioSetting::SetMssScenarioMsg(double initX, double initY) {
	mssScenarioMsg.MssStartX = initX;
	mssScenarioMsg.MssStartY = initY;

	msgHandle.SendMssScenarioMsg(mssScenarioMsg);
}

AtsScenarioMsg ScenarioSetting::GetAtsScenarioMsg() {
	return atsScenarioMsg;
}

MssScenarioMsg ScenarioSetting::GetMssScenarioMsg() {
	return mssScenarioMsg;
}

ScenarioSetting::ScenarioSetting()
{
}

ScenarioSetting::~ScenarioSetting()
{
}

/// <summary>
/// MissileCalculator
/// </summary>
void MissileCalculator::SetDirMss(double mssPosX, double mssPosY, double atsPosX, double atsPosY) {
	double x = atsPosX - mssPosX;
	double y = atsPosY - mssPosY;
	double absize = sqrt(x*x + y*y);
	
	mssDirectionMsg.XDir = x / absize;
	mssDirectionMsg.YDir = y / absize; 

	msgHandle.SendMssDir(mssDirectionMsg);
	// send dir
	//mssOpCommandMsg.Launch = launch;


}

void MissileCalculator::SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist) {
	double distance = sqrt(pow(atsPosX - mssPosX, 2) + pow(atsPosY - mssPosY, 2));
	if (distance <= interDist) {
		interceptMsg.SuccessDef = true;
		SendSuccessMsg(true);
	}
	double destAtsDist = sqrt(pow(atsDestPosX - atsPosX, 2) + pow(atsDestPosY - atsPosY, 2));
	if (destAtsDist <= 5) {
		interceptMsg.SuccessDef = false;
		SendSuccessMsg(false);
	}
}

void MissileCalculator::SendSuccessMsg(bool success) {
	// 통신 클래스에 전달 interceptMsg를
	msgHandle.SendInterceptMsg(success);

}

/// <summary>
/// Warning
/// </summary>
bool Warning::LaunchOk(double mssStartX, double mssStartY, double atsX, double atsY) {
	double distance = sqrt(pow(atsX - mssStartX, 2) + pow(atsY - mssStartY, 2));
	if (distance <= 50)
		return true;
	else
		return false;
}

class OperationControl {
public:
	void SetMssOpCommandMsg(double mssStartX, double mssStartY, double atsPosX, double atsPosY, bool launch);
	void LaunchMss();
private:
	MssOpCommandMsg mssOpCommandMsg;
	MissileCalculator mssCalculator;
};

void OperationControl::SetMssOpCommandMsg(double mssStartX, double mssStartY, double atsPosX, double atsPosY, bool launch) {
	
	if (launch) {
		Warning warning;
		if (warning.LaunchOk(mssStartX, mssStartY, atsPosX, atsPosY)) {
			LaunchMss(); // 미사일 발사
			mssOpCommandMsg.Launch = false;
		}
	}
}

void OperationControl::LaunchMss() { // 구현해야함
	msgHandle.SendMssOpMsg(true);
}