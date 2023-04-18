#include "MessageHandler.h"
#include <thread>

using namespace std;

int main()
{

	MessageHandler* messageHandler = new MessageHandler();
	messageHandler->ListenStart();

	while (true)
	{
		// 테스트용 1.1과 2.2을 지속 전송함
		messageHandler->SendMssPosition(1.1, 2.2);
		this_thread::sleep_for(chrono::milliseconds(500));
		
	}

	return 0;
}