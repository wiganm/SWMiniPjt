#include "pch.h"

void AtsSimulation::ScenarioSetting(AtsScenarioMsg* atsScenarioMsg){ // 시나리오를 입력 받음
	time = 0; // 시작과 동시에 time은 0으로 초기화
	startX = atsScenarioMsg->AtsStartX; //편의성을 위해 시나리오의 시작 위치 X좌표 저장
	startY = atsScenarioMsg->AtsStartY; //편의성을 위해 시나리오의 시작 위치 Y좌표 저장
	double distance; // 거리를 저장한 지역 변수 선언 (단위벡터 계산용)
	double distanceAxisX = atsScenarioMsg->AtsDestiationX - atsScenarioMsg->AtsStartX; // 도착~시작 X좌표 거리 (단위벡터 계산용)
	double distanceAxisY = atsScenarioMsg->AtsDestiationY - atsScenarioMsg->AtsStartY; // 도착~시작 X좌표 거리 (단위벡터 계산용)
	distance = sqrt(pow((distanceAxisX), 2) + pow((distanceAxisY), 2)); // 도착~시작좌표 사이 간 거리 계산
	unitVectorX = distanceAxisX / distance; // X좌표 단위벡터
	unitVectorY = distanceAxisY / distance; // Y좌표 단위벡터
	velocity = atsScenarioMsg->Velocity; // 편의성을 위해 시나리오의 속도 저장

	cout << "----- 시나리오 정보 수신 -----" << endl;
	cout << "속도 : " << atsScenarioMsg->Velocity << " / " << "타입 : " << atsScenarioMsg->atsType << endl;
	cout << "시작위치 : " << atsScenarioMsg->AtsStartX << ", " << atsScenarioMsg->AtsStartY << endl;
	cout << "종료위치 : " << atsScenarioMsg->AtsDestiationX << ", " << atsScenarioMsg->AtsDestiationY << endl;
	
}

void AtsSimulation::Start()
{
	state = true;
}

void AtsSimulation::Stop() {
	state = false;
	cout << "요격을 중지합니다." << endl;
	// 변수 초기화 함수 따로 만들건지에 따라 구현 필요성 정해질 수도?
	// 아래에 변수 초기화용 함수 따로 만들기는 함.
}

/*
void AtsSimulation::Stop(AtsScenarioMsg *atsScenarioMsg, AtsPositionMsg *atsPositionMsg, InterceptMsg *interceptMsg) {
	//각 구조체 메시지에서 MessageID와 MessageSize를 제외하고 0으로 초기화
	// memset(atsScenarioMsg+2*sizeof(int), 0, sizeof(AtsScenarioMsg)-2*sizeof(int)); // 공중위협 시나리오 메시지 초기화
	// memset(atsPositionMsg+2*sizeof(int), 0, sizeof(AtsScenarioMsg)-2*sizeof(int)); // 공중위협 위치 초기화
	// memset(InterceptMsg+2*sizeof(int), 0, sizeof(AtsScenarioMsg)-2*sizeof(int)); // 시나리오 구조체 초기화
}
*/

void AtsSimulation::UpdateAtsPostion() { // 지도 축척비를 고려해야 할지?
	this->atsPositionMsg.X_AstLoc = startX + unitVectorX * time * velocity * 0.5;
	this->atsPositionMsg.Y_AstLoc = startY + unitVectorY * time * velocity * 0.5;
	time += 1;
}

AtsSimulation::AtsSimulation()
{

}

bool AtsSimulation::GetState()
{
	return state;
}

AtsPositionMsg AtsSimulation::GetPos()
{
	return atsPositionMsg;
}