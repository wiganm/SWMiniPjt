#include "pch.h"
#include "framework.h"
#include "MSS.h"
#include <cmath>
#include <iostream>

using namespace std;


void MssSimulator::Initialize(double MssStartX, double MssStartY) {
	//Set start position
	double InitX = MssStartX;
	double InitY = MssStartY;
	//Set current position
	double currentX = InitX;
	double currentY = InitY;
}

void MssSimulator::Start(bool SimulationState) {
	//Initialize();
	if (SimulationState)
		cout << "Mss Simulator get Started." << endl;
	else
		cout << "Mss Simulator get Stopped." << endl;
}


void MssSimulator::Move(double vectorX, double vectorY) {
	//Get next position
	currentX += vectorX * 2.5;
	currentY += vectorY * 2.5; // 5마하의 0.5초만큼 이동
}


void MssSimulator::UpdateSimulationState() {
	if (SimulationState == 0) {

	}
	if (SimulationState == 1) {

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