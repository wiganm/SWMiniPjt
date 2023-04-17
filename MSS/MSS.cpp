// MSS.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include <cmath>

// TODO: 라이브러리 함수의 예제입니다.
void fnMSS()
{
}

class MssPositionDeliverer {
	void SendMssPosition(double, double);
};

void MssPositionDeliverer::SendMssPosition(double MssPositionX, double MssPositionY) {
	//???
}

class MssSimulator {
public:
	double InitX;
	double InitY;
	double currentX;
	double currentY;

	double MssPositionX;
	double MssPositionY;
	int SimulationState;
private:
	void Initialize(double, double);
	void Start(int);
	void Stop(int);
	void Move(double, double);
	void UpdateMssPosition();
	void UpdateSimulationState();
};

void MssSimulator::Initialize(double MssStartX, double MssStartY) {
	//Set start position
	double InitX = MssStartX;
	double InitY = MssStartY;
	//Set current position
	double currentX = InitX;
	double currentY = InitY;
}

void MssSimulator::Start(int SimulationState) {
	//Initialize();
	while (SimulationState == 1) {
		Move();
	}
}

void MssSimulator::Stop(int SimulationState) {
	while (SimulationState == 0) {
		//???
	}
}

void MssSimulator::Move(double vectorX, double vectorY) {
	//Get next position
	currentX += vectorX;
	currentY += vectorY;
}

void MssSimulator::UpdateMssPosition() {
	MssPositionX = currentX;
	MssPositionY = currentY;
}

void MssSimulator::UpdateSimulationState() {
	if (SimulationState == 0) { 

	}
	if (SimulationState == 1) {

	}
}