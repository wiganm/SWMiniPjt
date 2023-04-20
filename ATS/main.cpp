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
		if(atsSimulation->GetState()) // �����ϸ� state�� true�� �ٲ�
		{
			messageHandler->SendAtsPosition();
			atsSimulation->UpdateAtsPostion();
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	cout << "Mss Simulation�� �����մϴ�." << endl;

	return 0;
}