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

void MessageHandler::SendMssScenarioMsg(double xStart, double yStart) {
	char buf[1024] = { 0, };
	MssScenarioMsg msg;
	ScenarioSetting setting;
	setting.SetMssScenarioMsg(xStart, yStart);
	msg = setting.GetMssScenarioMsg();

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(7777, buf); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

void MessageHandler::SendAtsScenarioMsg(double xStart, double yStart, double xDest, double yDest, double velocity, int type) {
	char buf[1024] = { 0, };
	AtsScenarioMsg msg;
	ScenarioSetting setting;
	setting.SetAtsScenarioMsg(xStart, yStart, xDest, yDest, velocity,type);
	msg = setting.GetAtsScenarioMsg();

	memcpy(buf, &msg, sizeof(msg));
	udpServer->send(8888, buf); // enum���� ip �־�ɵ� ���� 7777�� Mss, 8888�� Ats
}

// mss���� recv �� ���� GCSClass���� �����ͼ� ���
// �߻� ��ɵ� recv �� ���