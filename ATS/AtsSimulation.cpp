#include "pch.h"

void AtsSimulation::Start(AtsScenarioMsg* atsScenarioMsg){ // �ó������� �Է� ����
	time = 0; // ���۰� ���ÿ� time�� 0���� �ʱ�ȭ
	startX = atsScenarioMsg->AtsStartX; //���Ǽ��� ���� �ó������� ���� ��ġ X��ǥ ����
	startY = atsScenarioMsg->AtsStartY; //���Ǽ��� ���� �ó������� ���� ��ġ Y��ǥ ����
	double distance; // �Ÿ��� ������ ���� ���� ���� (�������� ����)
	double distanceAxisX = atsScenarioMsg->AtsDestiationX - atsScenarioMsg->AtsStartX; // ����~���� X��ǥ �Ÿ� (�������� ����)
	double distanceAxisY = atsScenarioMsg->AtsDestiationY - atsScenarioMsg->AtsStartY; // ����~���� X��ǥ �Ÿ� (�������� ����)
	distance = sqrt(pow((distanceAxisX), 2) + pow((distanceAxisY), 2)); // ����~������ǥ ���� �� �Ÿ� ���
	unitVectorX = distanceAxisX / distance; // X��ǥ ��������
	unitVectorY = distanceAxisY / distance; // Y��ǥ ��������
	velocity = atsScenarioMsg->Velocity; // ���Ǽ��� ���� �ó������� �ӵ� ����
}

void AtsSimulation::Stop() {
	// ���� �ʱ�ȭ �Լ� ���� ��������� ���� ���� �ʿ伺 ������ ����?
	// �Ʒ��� ���� �ʱ�ȭ�� �Լ� ���� ������ ��.
}

/*
void AtsSimulation::Stop(AtsScenarioMsg *atsScenarioMsg, AtsPositionMsg *atsPositionMsg, InterceptMsg *interceptMsg) {
	//�� ����ü �޽������� MessageID�� MessageSize�� �����ϰ� 0���� �ʱ�ȭ
	// memset(atsScenarioMsg+2*sizeof(int), 0, sizeof(AtsScenarioMsg)-2*sizeof(int)); // �������� �ó����� �޽��� �ʱ�ȭ
	// memset(atsPositionMsg+2*sizeof(int), 0, sizeof(AtsScenarioMsg)-2*sizeof(int)); // �������� ��ġ �ʱ�ȭ
	// memset(InterceptMsg+2*sizeof(int), 0, sizeof(AtsScenarioMsg)-2*sizeof(int)); // �ó����� ����ü �ʱ�ȭ
}
*/

void AtsSimulation::UpdateAtsPostion(AtsPositionMsg* atsPositionMsg) { // ���� ��ô�� ����ؾ� ����?
	atsPositionMsg->X_AstLoc = startX + unitVectorX * time * velocity;
	atsPositionMsg->Y_AstLoc = startY + unitVectorY * time * velocity;
	time += 1;
}