#include "MessageHandler.h"
#include "MSS.h"
#include <thread>
#include <iostream>

using namespace std;

int main()
{
	MssSimulator mssSimulator = MssSimulator();
	MessageHandler* messageHandler = new MessageHandler(mssSimulator);
	messageHandler->ListenStart();

	

	while (true)
	{
		messageHandler->SendMssPosition();
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	cout << "Mss Simulation을 종료합니다." << endl;

	return 0;
}