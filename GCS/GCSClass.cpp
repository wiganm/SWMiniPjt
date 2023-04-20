#include "pch.h"
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
	//msgHandle->SendAtsScenarioMsg(atsScenarioMsg);
}

void ScenarioSetting::SetMssScenarioMsg(double initX, double initY) {
	mssScenarioMsg.MssStartX = initX;
	mssScenarioMsg.MssStartY = initY;

	//msgHandle->SendMssScenarioMsg(mssScenarioMsg);
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


MssDirectionMsg MissileCalculator::SetDirMss(double mssPosX, double mssPosY, double atsPosX, double atsPosY) {
	double x = atsPosX - mssPosX;
	double y = atsPosY - mssPosY;
	double absize = sqrt(x*x + y*y);
	
	MssDirectionMsg mssDirectionMsg;
	mssDirectionMsg.XDir = x / absize;
	mssDirectionMsg.YDir = y / absize; 

	return mssDirectionMsg;
	// send dir
	//mssOpCommandMsg.Launch = launch;


}

bool MissileCalculator::SetInterceptSuccess(double mssPosX, double mssPosY, double atsPosX, double atsPosY, double atsDestPosX, double atsDestPosY, double interDist) {
	double distance = sqrt(pow(atsPosX - mssPosX, 2) + pow(atsPosY - mssPosY, 2));
	if (distance <= interDist) { // 입력값보다 작은 거리면 성공
		//interceptMsg.SuccessDef = true;
		return 1;
	}
	double destAtsDist = sqrt(pow(atsDestPosX - atsPosX, 2) + pow(atsDestPosY - atsPosY, 2));
	if (destAtsDist <= 5) { // 목적지랑 위치 5이하면 실패
		//interceptMsg.SuccessDef = false;
		return 0;
	}
	return 0;
}

//void MissileCalculator::SendSuccessMsg(bool success) {
//	// 통신 클래스에 전달 interceptMsg를
//	msgHandle->SendInterceptMsg(success);
//
//}

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


void OperationControl::SetMssOpCommandMsg(double mssStartX, double mssStartY, double atsPosX, double atsPosY, bool launch) { 
	
	if (launch) {
		Warning warning;
		if (warning.LaunchOk(mssStartX, mssStartY, atsPosX, atsPosY)) {
			LaunchMss(); // 미사일 발사
			mssOpCommandMsg.Launch = false;
		}
	}
}

OperationControl::OperationControl() {

}

OperationControl::~OperationControl()
{

}

void OperationControl::SetApsOpCommandMsg(bool command) {
	//msgHandle->SendAtsOpMsg(command);
}

void OperationControl::LaunchMss() { // 구현해야함
	//msgHandle->SendMssOpMsg(true);
}

void OperationControl::SetMssState(bool state) {
	mssState = state;
}

void OperationControl::SetAtsState(bool state) {
	atsState = state;
}

void OperationControl::SetMssDirMsg(MssDirectionMsg msg) {
	mssDirectionMsg = msg;
}

void OperationControl::SetMssPosMsg(MssPositionMsg msg) {
	mssPosMsg = msg;
}

void OperationControl::SetAtsPosMsg(AtsPositionMsg msg) {
	atsPosMsg = msg;
}

bool OperationControl::GetMssState() {
	return mssState;
}

bool OperationControl::GetAtsState() {
	return atsState;
}

MssDirectionMsg OperationControl::GetMssDirMsg() {
	return mssDirectionMsg;
}
MssPositionMsg OperationControl::GetMssPosMsg() {
	return mssPosMsg;
}

AtsPositionMsg OperationControl::GetAtsPosMsg() {
	return atsPosMsg;
}