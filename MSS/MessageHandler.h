#include "UdpClient.h"
#pragma once

class MessageHandler
{
private:
	UdpClient* udpClient;
	//void MessageParse();
	void Listen();
public:
	MessageHandler();
	//~MessageHandler();
	void ListenStart();
	//void SendMssPosition();
	//void SendMssState();

};