#pragma once
#pragma once
#define DISTDIVIDE 5000

<<<<<<< .merge_file_PS5ZVV
struct AtsScenarioMsg { //공중위협 시나리오 메시지
	int MessageID = 1501;
	int MessageSize = sizeof(AtsScenarioMsg);
=======
struct AtsScenarioMsg {

>>>>>>> .merge_file_ItTG77
	double  AtsStartX, AtsStartY;
	double AtsDestiationX, AtsDestiationY;
	double Velocity;
	int atsType; // 0 : 오류 1 : 탄도탄 2 : 항공기
};

struct AtsOpCommandMsg { //공중위협 제어명령 메시지
	int MessageID = 1510;
	int MessageSize = sizeof(AtsOpCommandMsg);
	bool AstCommand;
};

struct InterceptMsg { //요격이벤트 메시지
	int MessageID = 1520; // 1520 OR 1320
	int MessageSize = sizeof(InterceptMsg);
	bool  SuccessDef;
};

struct AtsStateMsg { //공중위협 상태 메시지
	int MessageID = 5101;
	int MessageSize = sizeof(AtsStateMsg);
	bool AstState;
};

struct AtsPositionMsg { // 공중위협 위치 정보 메시지
	int MessageID = 5110;
	int MessageSize = sizeof(AtsPositionMsg);
	double  X_AstLoc, Y_AstLoc;
};

struct MssScenarioMsg { // 대공유도탄 시나리오 메시지
	int MessageID = 1301;
	int MessageSize = sizeof(MssScenarioMsg);
	double MssStartX, MssStartY;
	double Velocity = 5;
};

struct MssOpCommandMsg { //대공유도탄 제어명령 메시지
	int MessageID = 1310;
	int MessageSize = sizeof(MssOpCommandMsg);
	bool Launch;
};

<<<<<<< .merge_file_PS5ZVV
struct MssStateMsg { //대공유도탄 상태 메시지
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

struct MssPositionMsg { //대공유도탄 위치 정보 메시지
	int MessageID = 3120;
	int MessageSize = sizeof(MssPositionMsg);
	double X_Pos, Y_Pos;
};