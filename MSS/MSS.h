#pragma once
#include "pch.h"
#include "framework.h"
#include <cmath>


class MssSimulator {
private:
	double InitX;
	double InitY;
	double currentX;
	double currentY;

	int SimulationState;

public:
	void Initialize(double, double);
	void Start(bool);
	void Move(double, double);
	void UpdateSimulationState();
	double GetX();
	double GetY();
};