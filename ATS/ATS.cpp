#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "MsgDatas.h"
#include "ATS.h"

using namespace std;

/// <summary>
/// UdpClient
/// </summary>
void UdpClient::Send(int socket) {
	char send_buf[MAX_BUF_LEN];	

	if((state == 1510) && (state != pre_state)){ // ����� ������ ���� = �� ���� �۽�(���� ���� != ���� ����)
		if (atsOpCommandMsg.AstCommand == 1) { // �⵿ ���� ���
			atsStateMsg.AstState = atsSimulation.Start(&atsScenarioMsg);
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // �������� ���¸� buffer�� copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state;
		}
	}
	else if ((state == 1510) || (state == 1520) ) { //�������� �۽�
		if ((atsOpCommandMsg.AstCommand == 1) && (interceptMsg.SuccessDef == 0)) { // �⵿ ���� & ��� �̿Ϸ�
			atsSimulation.UpdateAtsPostion(&atsPositionMsg, atsScenarioMsg.AtsStartX, atsScenarioMsg.AtsStartY, atsScenarioMsg.Velocity);
			memcpy(send_buf, &atsPositionMsg, sizeof(atsPositionMsg)); // �������� ���¸� buffer�� copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
		}
		else {
			atsStateMsg.AstState = atsSimulation.Stop();
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // �������� ���¸� buffer�� copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state = 0;
		}
	}
}

void UdpClient::Receive(int socket) {
	
	char recv_buf[MAX_BUF_LEN];
	

	// UDP ��� - ������Ʈ �ڵ� (�����ʿ�)
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	int len = recvfrom(socket, recv_buf, MAX_BUF_LEN, 0, (struct sockaddr*)&addr, &addr_len); //�۽Ź��� buf�� 0������ ������ ����?
	recv_buf[len] = '\0'; // 0�� ������ ������ �κб����� �޽����� �ٷ�.

	memcpy(&state, recv_buf, sizeof(int)); // ������ ��� �����ͷκ��� MessageID�� �и�

	if (state == 1501) { //�ó����� �Է�
		memcpy(&atsScenarioMsg, recv_buf, sizeof(atsScenarioMsg));
	}
	else if (state == 1510) { // �������� ���(�⵿ ����, ����)
		memcpy(&atsOpCommandMsg, recv_buf, sizeof(atsOpCommandMsg));
	}
	else if (state == 1520) { // ����̺�Ʈ (���������->�����������Ǳ�)
		memcpy(&interceptMsg, recv_buf, sizeof(interceptMsg));
	}
}

/// <summary>
/// MessaageHandler
/// </summary>
void MessaageHandler::MessageParser(int sockfd, int cur_state) {
	while (1) {
		// ������ thread ���� -> ��� ���� ���
		thread receive_thread(&UdpClient::Receive, sockfd);
		// �۽��� thread ���� -> ��� �۽� ���
		thread send_thread(&UdpClient::Send, sockfd);
	};
}

/// <summary>
/// AtsSimulation
/// </summary>
bool AtsSimulation::Start(AtsScenarioMsg *atsScenarioMsg) { // if((interceptMsg.SuccessDef == 0)&&(atsOpCommandMsg.AstCommand == 1))
	period = 0;
	slope = (atsScenarioMsg->AtsDestiationY - atsScenarioMsg->AtsStartY) / (atsScenarioMsg->AtsDestiationX - atsScenarioMsg->AtsStartX);
	interceptY = atsScenarioMsg->AtsStartY - slope * atsScenarioMsg->AtsStartX;
	return 1;
}

bool AtsSimulation::Stop() { // if((interceptMsg.SuccessDef == 1)||(atsOpCommandMsg.AstCommand == 0))
	period = 0;
	slope = 0;
	interceptY = 0;
	return 0;
}

void AtsSimulation::UpdateAtsPostion(AtsPositionMsg* atsPositionMsg, double initX, double initY, double velocity) { // if(atsStateMsg.AstState==1)
	atsPositionMsg->X_AstLoc = initX + sqrt(1/((1*1)+(slope*slope)))*period*velocity;
	atsPositionMsg->Y_AstLoc = initX + sqrt(slope / ((1 * 1) + (slope * slope))) * period * velocity;
	period += 1;
}