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
	return 0;
}

class MssSimulator {
public:
	double MssPositionX;
	double MssPositionY;
	int SimulationState;
	void Start();
	void Stop();
	void Move();
	void UpdateMssPosition();
	void UpdateSimulationState();
};

void MssSimulator::Move(double vectorX, double vectorY) {
	//double tempX = MssPositionX;
	//double tempY = MssPositionY;
	MssPositionX += vectorX;
	MssPositionY += vectorY;
}