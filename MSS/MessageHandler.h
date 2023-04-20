#include "UdpClient.h"
#include "MSS.h"
#pragma once


class MessageHandler
{
private:
	UdpClient* udpClient;
	MssSimulator mssSimulator;
	void Listen();
public:
	MessageHandler(MssSimulator mssSimulator);
	void ListenStart();
	void SendMssPosition();
	void SendMssState();

};