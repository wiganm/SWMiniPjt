#include "UdpServer.h"
#include <thread>
#include <iostream>
#include "MessageHandler.h"
#include "MsgDatas.h"

using namespace std;


void MessageHandler::Listen()
{
	while (true)
	{
		int messageId;
		const char* temp = udpServer->recv();
		memcpy(&messageId, temp, 4);
		
		switch (messageId)
		{
		case 3110: // 미사일 상태 메시지
			// 구현 부분
			break;
		case 3120: // 미사일 포지션 메시지
			// 구현 부분
			break;
		case 5101: // 공중위협 상태 메시지
			// 구현 부분
			break;
		case 5110: // 공중위협 포지션 메시지
			// 구현 부분
			break;
		}

	}
}

MessageHandler::MessageHandler()
{
	const string ip = "127.0.0.1";
	int server_port = 4444;
	udpServer = new UdpServer(ip, server_port);
}

void MessageHandler::ListenStart()
{
	thread t(&MessageHandler::Listen, this);
	t.detach();
}
