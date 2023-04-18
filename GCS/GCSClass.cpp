#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "MsgDatas.h"
#include "GCSClass.h"

using namespace std;

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
}

void ScenarioSetting::SetMssScenarioMsg(double initX, double initY) {
	mssScenarioMsg.MssStartX = initX;
	mssScenarioMsg.MssStartY = initY;
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
MssOpCommandMsg MissileCalculator::SetAndGetMssOp(double mssPosX, double mssPosY, double atsPosX, double atsPosY, bool launch) {
	double x = atsPosX - mssPosX;
	double y = atsPosY - mssPosY;
	double absize = sqrt(x*x + y*y);
	
	mssOpCommandMsg.XDir = x / absize;
	mssOpCommandMsg.YDir = y / absize;
	mssOpCommandMsg.Launch = launch;

	return mssOpCommandMsg;
}

void MissileCalculator::SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist) {
	double distance = sqrt(pow(atsPosX - mssPosX, 2) + pow(atsPosY - mssPosY, 2));
	if (distance <= interDist) {
		interceptMsg.SuccessDef = true;
		SendSuccessMsg();
	}
	double destAtsDist = sqrt(pow(atsDestPosX - atsPosX, 2) + pow(atsDestPosY - atsPosY, 2));
	if (destAtsDist <= 5) {
		interceptMsg.SuccessDef = false;
		SendSuccessMsg();
	}
}

void MissileCalculator::SendSuccessMsg() {
	// 통신 클래스에 전달 interceptMsg를
}

/// <summary>
/// Warning
/// </summary>
bool Warning::LaunchOk(double mssX, double mssY, double atsX, double atsY) {
	double distance = sqrt(pow(atsX - mssX, 2) + pow(atsY - mssY, 2));
	if (distance <= 50)
		return true;
	else
		return false;
}