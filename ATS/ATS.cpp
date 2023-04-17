// ATS.cpp : 정적 라이브러리를 위한 함수를 정의합니다.

#include "pch.h"
#include "framework.h"
#include "ATS.h"

using namespace std;

const int PORT = 1234;
const int MAX_BUF_LEN = 100;
const char* IP_ADDR = "127.0.0.1";

struct AtsScenario {
	int MessageID; // 1501
	int MessageSize; // 52 byte
	double AtsStartX;
	double AtsStartY;
	double AtsDestinationX;
	double AtsDestinationY;
	double AtsVelocity;
	int AtsType;
};

struct AtsCommand {
	int MessageID; // 1510
	int MessageSize; // 9 byte
	char Command; //
};

struct AtsState {
	int MessageID; // 5101
	int MessageSize; // 9 byte;
	char State; //0 : 대기 상태, 1: 모의 시작, 2: 모의 종료, 3: 기동 시작, 4: 기동 종료
};

struct AtsLocation {
	int MessageID; // 5110
	int MessageSize; // 24 byte;
	double AtsLocX;
	double AtsLocY;
};

class AtsSimulation {
public:
	void RcvAtsScenario(){ // 시나리오 정보 입력받고, 구동을 위한 

	}

private:
	AtsScenario AtSc;
	AtsScenario AtCmd;
};

class AtsMessageDeliver {
public:
	void RcvAtsCommand() { // 운용통제기 명령으로 while(command) 식이 될 수도?

	}
	void SendAtsState() { // RcvAtsCommand()에서 메시지 보낼 때 마다, 수신 상태 회신

	}
	void SendAtsLocation() { // 주기적으로 운용통제기에 보내는 방식이 될 것 같음.

	}

private:
	AtsScenario AtSt;
	AtsScenario AtLoc;
};

class MessageHandler {
public :

private :
	int messageID;
};

class UdpClient { //통신을 통해 받음.
public:
	// 송신측 thread
	void send_data(int sockfd) {
		char buf[MAX_BUF_LEN];
		while (1) {
			if (State == 0) continue;
			else if (State == 1) { //
				if (State != atsState.State) {
					atsState = { 5101, 9, 1 };
					//atsState.MessageID = 5101;
					//atsState.MessageSize = 9;
					//atsState.State = 1;

					//memset이나 memcpy로 바꿔야 할듯
					buf[] = atsState.MessageID; //
					buf[] = atsState.MessageSize;
					buf[] = atsState.State;
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
			}
			else if (State == 2) {
				if (State != atsState.State) {
					atsState = { 5101, 9, 2 };

					//memset이나 memcpy로 바꿔야 할듯
					buf[] = atsState.MessageID; //
					buf[] = atsState.MessageSize;
					buf[] = atsState.State;
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
			}
			else if (State == 3) {
				if (State != atsState.State) {
					atsState = { 5101, 9, 3 };

					//memset이나 memcpy로 바꿔야 할듯
					buf[] = atsState.MessageID; //
					buf[] = atsState.MessageSize;
					buf[] = atsState.State;
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
				else {
					//주기적으로 x, y좌표 계산 후 송신, period(현재 시점)를 어떻게 저장하고 있을지
					//memset이나 memcpy로 바꿔야 할듯
					buf[] = atsLocation.MessageID; //
					buf[] = atsLocation.MessageSize;
					buf[] = atsLocation.AtsLocX;
					buf[] = atsLocation.AtsLocY;
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
				}
			}
			else if (State == 4) {
				if (State != atsState.State) {
					atsState = { 5101, 9, 4 };

					//memset이나 memcpy로 바꿔야 할듯
					buf[] = atsState.MessageID; //
					buf[] = atsState.MessageSize;
					buf[] = atsState.State;
					sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);
					
					//공중위협 삭제, 시나리오 정보값 초기화?
				}
			}
			// 메시지 입력 받기
				cout << "Enter message to send: ";
				cin.getline(buf, MAX_BUF_LEN);

				// 메시지 보내기
				sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)nullptr, 0);

				// 송신 완료 메시지 출력
				cout << "Message sent: " << buf << endl;
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
			memcpy(*messageID, buf, sizeof(int));
			if (messageID == 1501) { //공중위협 시나리오 전달
				// 데이터 분할 (초기위치(x,y), 목적위치(x,y), 속도, 종류)
				atsScenario.AtsStartX = buf[]; // 9~16바이트
				atsScenario.AtsStartY = buf[]; // 17~24바이트
				atsScenario.AtsDestinationX = buf[]; //25~32바이트
				atsScenario.AtsDestinationY = buf[]; //33~40바이트
				atsScenario.AtsVelocity = buf[]; //41~48바이트
				atsScenario.AtsType = buf[]; //49~52바이트
				// 시나리오 설정 완료 상태 송신 (sendto 함수)
				atsState.State = 0;
			}
			else if (messageID == 1510) { // 운용통제기에서 명령
				// 데이터 분할 (명령 분리)
				State = buf[]; // 9 바이트
			}
			case 1510: // 명령 수신
				// 명령에 따른 함수 실행 (모의 시작, 모의 중지, 기동 시작, 기동 종료 -> state 변수 설정 필요, 수신은 계속 대기, 송신이 바뀔 수 있음)
				State = 
				// 명령 실행 완료 상태 송신 -> sendto 함수 or send data 호출
				break;
			}
			// 데이터 처리
			cout << "Data received from " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << ": " << buf << endl;
	}
private:
	AtsScenario atsScenario;
	int MessageID;
	AtsState atsState;
	int State; 
	AtsLocation atsLocation;
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
