#pragma once
#pragma once
#define DISTDIVIDE 5000

<<<<<<< .merge_file_PS5ZVV
struct AtsScenarioMsg { //�������� �ó����� �޽���
	int MessageID = 1501;
	int MessageSize = sizeof(AtsScenarioMsg);
=======
struct AtsScenarioMsg {

>>>>>>> .merge_file_ItTG77
	double  AtsStartX, AtsStartY;
	double AtsDestiationX, AtsDestiationY;
	double Velocity;
	int atsType; // 0 : ���� 1 : ź��ź 2 : �װ���
};

struct AtsOpCommandMsg { //�������� ������ �޽���
	int MessageID = 1510;
	int MessageSize = sizeof(AtsOpCommandMsg);
	bool AstCommand;
};

struct InterceptMsg { //����̺�Ʈ �޽���
	int MessageID = 1520; // 1520 OR 1320
	int MessageSize = sizeof(InterceptMsg);
	bool  SuccessDef;
};

struct AtsStateMsg { //�������� ���� �޽���
	int MessageID = 5101;
	int MessageSize = sizeof(AtsStateMsg);
	bool AstState;
};

struct AtsPositionMsg { // �������� ��ġ ���� �޽���
	int MessageID = 5110;
	int MessageSize = sizeof(AtsPositionMsg);
	double  X_AstLoc, Y_AstLoc;
};

struct MssScenarioMsg { // �������ź �ó����� �޽���
	int MessageID = 1301;
	int MessageSize = sizeof(MssScenarioMsg);
	double MssStartX, MssStartY;
	double Velocity = 5;
};

struct MssOpCommandMsg { //�������ź ������ �޽���
	int MessageID = 1310;
	int MessageSize = sizeof(MssOpCommandMsg);
	bool Launch;
};

<<<<<<< .merge_file_PS5ZVV
struct MssStateMsg { //�������ź ���� �޽���
=======
struct MssDirectionMsg {
	int MessageID = 1320;
	int MessageSize = sizeof(MssOpCommandMsg);
	double  XDir, YDir;
};

struct MssStateMsg {
>>>>>>> .merge_file_ItTG77
	int MessageID = 3110;
	int MessageSize = sizeof(MssStateMsg);
	bool MssState;
};

struct MssPositionMsg { //�������ź ��ġ ���� �޽���
	int MessageID = 3120;
	int MessageSize = sizeof(MssPositionMsg);
	double X_Pos, Y_Pos;
};