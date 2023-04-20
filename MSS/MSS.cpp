#include "pch.h"
#include "framework.h"
#include "MSS.h"
#include <cmath>
#include <iostream>

using namespace std;


void MssSimulator::Initialize(double MssStartX, double MssStartY) {
	//Set start position
	InitX = MssStartX;
	InitY = MssStartY;
	//Set current position5
	currentX = InitX;
	currentY = InitY;
}

void MssSimulator::Start() {
	//Initialize();
	state = true;
}

void MssSimulator::Stop() {
	//Initialize();
	state = false;
	cout << "모의를 중지합니다." << endl;
}


void MssSimulator::Move(double vectorX, double vectorY) {
	//Get next position
	currentX += vectorX * 2.5;
	currentY += vectorY * 2.5; // 5마하의 0.5초만큼 이동
}


void MssSimulator::UpdateSimulationState() {
	if (state == 0) {

	}
	if (state == 1) {

	}
}

double MssSimulator::GetX()
{
	return currentX;
}

double MssSimulator::GetY()
{
	return currentY;
}

bool MssSimulator::GetState()
{
	return state;
}