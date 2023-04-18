#include <string>
#include "UdpServer.h"
#pragma once

using namespace std;

class MessageHandler
{
private:
	UdpServer* udpServer;
	void Listen();
public:
	MessageHandler();
	//~MessageHandler();
	void ListenStart();
	//void SendMsg(char* msg);

};