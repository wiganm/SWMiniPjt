// ATS.cpp : 정적 라이브러리를 위한 함수를 정의합니다.

#include "pch.h"
#include "framework.h"
#include "ATS.h"
#include <iostream>

using namespace std;

const int PORT = 1234;
const int MAX_BUF_LEN = 100;
const char* IP_ADDR = "127.0.0.1";

struct AtsScenario { //시나리오 수신 구조체
	int MessageID; // 메시지 ID : 1501
	int MessageSize; // 메시지 길이 : 52 byte
	double AtsStartX; // 공중위협 시작 위치(X좌표)
	double AtsStartY; // 공중위협 시작 위치(Y좌표)
	double AtsDestinationX; // 공중위협 목적 위치(X좌표)
	double AtsDestinationY; // 공중위협 목적 위치(Y좌표)
	double AtsVelocity; // 공중위협 이동 속도 (X좌표)
	int AtsType; // 공중위협 타입
};

struct AtsCommand { // 명령 수신
	int MessageID; // 1510
	int MessageSize; // 9 byte
	char Command; //
};

struct AtsState { // 상태 업데이트
	int MessageID; // 5101
	int MessageSize; // 9 byte;
	char State = 0; //0 : 대기 상태, 1: 모의 시작, 2: 모의 종료, 3: 기동 시작, 4: 기동 종료
};

struct AtsLocation { // 위치 계산
	int MessageID; // 5110
	int MessageSize; // 24 byte;
	double AtsLocX;
	double AtsLocY;
};

class AtsSimulation {
public:

private:

};

class AtsMessageDeliver {
public:

private:

};

class MessageHandler {
public :

private :

};

class UdpClient { //통신을 통해 받음.
public:
	// 송신측 thread
	void send_data(int sockfd) {
		char buf[MAX_BUF_LEN];
		while (1) {
			if (atsState.State == 0) continue; //아직 모의도 시작하지 않은 단계로, 아무 동작 안함.

			else if (atsState.State == 1) { // 모의 시작 명령
				if (State != atsState.State) {
					atsState = { 5101, 9, 1 };

					memcpy(&atsState, buf, sizeof(atsState));
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
			}

			else if (atsState.State == 2) { // 모의 종료 명령
				if (State != atsState.State) {
					atsState = { 5101, 9, 2 };

					memcpy(&atsState, buf, sizeof(atsState));
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
			}

			else if (atsState.State == 3) { //기동 시작 명령
				if (State != atsState.State) { //기동 시작 후 운용통제기에 상태 송신(최초 1회)
					atsState = { 5101, 9, 3 };
					Period = 0;
					memcpy(&atsState, buf, sizeof(atsState));
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
				else { // 기동 시작 후 지속적인 위치 송신
					
//[구현 필요] 주기적으로 x, y좌표 계산 후 송신, period(현재 시점)를 어떻게 저장하고 있을지

					memcpy(&atsLocation, buf, sizeof(atsLocation));
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
					Period++;
				}
			}

			else if (atsState.State == 4) { //기동 종료 명령
				if (State != atsState.State) {
					atsState = { 5101, 9, 4 };

					memcpy(&atsState, buf, sizeof(atsState));
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
					
					/*공중위협 삭제, 시나리오 정보값 초기화 ?*/
				}
			}
			State = atsState.State;
		}
	}

	void receive_data(int sockfd) {
		struct sockaddr_in addr;
		socklen_t addr_len = sizeof(addr);
		char buf[MAX_BUF_LEN];
		while (1) {
			// 데이터 받기
			int len = recvfrom(sockfd, buf, MAX_BUF_LEN, 0, (struct sockaddr*)&addr, &addr_len); //송신받은 buf가 0나오기 전까지 복사?
			buf[len] = '\0'; // 0이 나오기 시작한 부분까지의 메시지만 다룸.

			//메시지 ID 처리
			memcpy(&MessageID, buf, sizeof(int)); // 초기 ID만 읽어서 동작 결정

			if (MessageID == 1501) { //공중위협 시나리오 전달 받음
				memcpy(&atsScenario, buf, sizeof(atsScenario));
//[구현 필요] 시나리오 설정 파트 구현 필요 -> 어떤 함수에서 할지, 어떻게 저장하고 있을지
				atsLocation = { 5110, 24, atsScenario.AtsStartX, atsScenario.AtsStartY};
				atsState.State = 0;
			}
			else if (MessageID == 1510) { // 운용통제기에서 명령
				State = atsState.State; //이전 State 저장, State가 바뀌면 메시지 전파해야 하므로
				memcpy(&atsState, buf, sizeof(atsState));
			}
		}
	}
private:
	AtsScenario atsScenario;
	int MessageID;
	AtsState atsState;
	int State; 
	AtsLocation atsLocation;
	int Period;
};



// TODO: 라이브러리 함수의 예제입니다.
int main() {
	//소켓 설정
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		cerr << "Error: socket creation failed" << endl;
		return -1;
	}

	//포트 설정
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP_ADDR);

	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		cerr << "Error: bind failed" << endl;
		return -1;
	}

	// 송신측 thread 생성 -> 계속 송신 대기
	thread send_thread(UdpClient::send_data, sockfd);

	// 수신측 thread 생성 -> 계속 수신 대기
	thread receive_thread(UdpClient::receive_data, sockfd);


	// thread 종료 대기
	send_thread.join();
	receive_thread.join();
	close(sockfd);

	return 0;
}
