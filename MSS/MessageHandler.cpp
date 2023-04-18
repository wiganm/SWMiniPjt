#include "UdpClient.h"
#include <thread>
#include <iostream>
#include "MessageHandler.h"
#include "MsgDatas.h"

using namespace std;


void MessageHandler::Listen()
{
	while (true)
	{
		string msg;
		msg = udpClient->recv();
		cout << msg << endl;
	}
}

MessageHandler::MessageHandler()
{
	const string ip = "127.0.0.1";
	int client_port = 7777;
	int server_port = 4444;
	udpClient = new UdpClient(ip, client_port, server_port);
}

void MessageHandler::ListenStart()
{
	thread t(&MessageHandler::Listen, this);
	t.detach();
}

void MessageHandler::SendMssPosition(double x, double y)
{
	char buf[1024] = { 0, };
	MssPositionMsg pos;
	pos.X_Pos = x;
	pos.Y_Pos = y;

	memcpy(buf, &pos, sizeof(pos));

	udpClient->send(buf);
}