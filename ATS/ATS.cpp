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

	if((state == 1510) && (state != pre_state)){ // 명령을 수신한 상태 = 한 번만 송신(이전 상태 != 현재 상태)
		if (atsOpCommandMsg.AstCommand == 1) { // 기동 시작 명령
			atsStateMsg.AstState = atsSimulation.Start(&atsScenarioMsg);
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // 공중위협 상태를 buffer에 copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state;
		}
	}
	else if ((state == 1510) || (state == 1520) ) { //지속적인 송신
		if ((atsOpCommandMsg.AstCommand == 1) && (interceptMsg.SuccessDef == 0)) { // 기동 시작 & 요격 미완료
			atsSimulation.UpdateAtsPostion(&atsPositionMsg, atsScenarioMsg.AtsStartX, atsScenarioMsg.AtsStartY, atsScenarioMsg.Velocity);
			memcpy(send_buf, &atsPositionMsg, sizeof(atsPositionMsg)); // 공중위협 상태를 buffer에 copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
		}
		else {
			atsStateMsg.AstState = atsSimulation.Stop();
			memcpy(send_buf, &atsStateMsg, sizeof(atsStateMsg)); // 공중위협 상태를 buffer에 copy
			sendto(socket, send_buf, strlen(send_buf), 0, (struct sockaddr*)nullptr, 0);
			pre_state = state = 0;
		}
	}
}

void UdpClient::Receive(int socket) {
	
	char recv_buf[MAX_BUF_LEN];
	

	// UDP 통신 - 수신파트 코드 (수정필요)
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	int len = recvfrom(socket, recv_buf, MAX_BUF_LEN, 0, (struct sockaddr*)&addr, &addr_len); //송신받은 buf가 0나오기 전까지 복사?
	recv_buf[len] = '\0'; // 0이 나오기 시작한 부분까지의 메시지만 다룸.

	memcpy(&state, recv_buf, sizeof(int)); // 수신한 통신 데이터로부터 MessageID만 분리

	if (state == 1501) { //시나리오 입력
		memcpy(&atsScenarioMsg, recv_buf, sizeof(atsScenarioMsg));
	}
	else if (state == 1510) { // 공중위협 명령(기동 시작, 종료)
		memcpy(&atsOpCommandMsg, recv_buf, sizeof(atsOpCommandMsg));
	}
	else if (state == 1520) { // 요격이벤트 (운용통제기->공중위협모의기)
		memcpy(&interceptMsg, recv_buf, sizeof(interceptMsg));
	}
}

/// <summary>
/// MessaageHandler
/// </summary>
void MessaageHandler::MessageParser(int sockfd, int cur_state) {
	while (1) {
		// 수신측 thread 생성 -> 계속 수신 대기
		thread receive_thread(&UdpClient::Receive, sockfd);
		// 송신측 thread 생성 -> 계속 송신 대기
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