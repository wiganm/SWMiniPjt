#include "UdpServer.h"
#include <thread>
#include <iostream>
#include "MessageHandler.h"
#include "MsgDatas.h"
#include "GCSClass.h"

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
		case 3110: // �̻��� ���� �޽���
			cout << "�̻��� ���¸޽��� ����" << endl;// ���� �κ�
			break;
		case 3120: // �̻��� ������ �޽���
			missileCalculator.SetAndGetDirMss(MssPositionX, MssPositionY, AtsPositionX, AtsPositionY); // �̻��� ������ ���Ž� �̻��� ���� ������Ʈ
			missileCalculator.SetInterceptSuccess(MssPositionX, MssPositionY, AtsPositionX, AtsPositionY, AtsDestPosX, AtsDestPosY, 5); // ���� ��� Ȯ��
			break;
		case 5101: // �������� ���� �޽���
			cout << "�������� ���� �޽���" << endl;// ���� �κ�
			break;
		case 5110: // �������� ������ �޽���
			cout << "�������� ������ �޽���" << endl;// ���� �κ�
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

void MessageHandler::SendMssOpMsg(bool opMsg)
{
	char buf[1024] = { 0, };
	MssOpCommandMsg msg;
	msg.Launch = opMsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendMssScenarioMsg(MssScenarioMsg mmsg) {
	char buf[1024] = { 0, };
	MssScenarioMsg msg;
	msg = mmsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendAtsScenarioMsg(AtsScenarioMsg amsg) {
	char buf[1024] = { 0, };
	AtsScenarioMsg msg;
	
	msg = amsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(8888, buf); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendInterceptMsg(bool intermsg) {
	char buf[1024] = { 0, };
	InterceptMsg msg;
	msg.SuccessDef = intermsg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf);
	udpServer->send(8888, buf); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendMssDir(MssDirectionMsg dirmsg) {
	char buf[1024] = { 0, };
	MssDirectionMsg msg;

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf);
}
