#include "MessageHandler.h"

int main()
{

	MessageHandler* messageHandler = new MessageHandler();
	messageHandler->ListenStart();

	return 0;
}