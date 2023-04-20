#include "MessageHandler.h"
#include <thread>
#include <iostream>
#include "AtsSimulation.h"

using namespace std;

int main()
{
	AtsSimulation* atsSimulation = new AtsSimulation();
	MessageHandler* messageHandler = new MessageHandler(atsSimulation);
	messageHandler->ListenStart();



	while (true)
	{
		if(atsSimulation->GetState()) // 시작하면 state가 true로 바뀜
		{
			messageHandler->SendAtsPosition();
			atsSimulation->UpdateAtsPostion();
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	cout << "Mss Simulation을 종료합니다." << endl;

	return 0;
}