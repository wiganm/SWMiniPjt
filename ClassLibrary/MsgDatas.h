#pragma once

enum AtsType {
	BallisticBullet = 1,
	Aircraft = 2,
};

struct AtsScenarioMsg {
	int MessageID = 1501;
	int MessageSize;
	double  AtsStartX, AtsStartY;
	double AtsDestiationX, AtsDestiationY;
	double Velocity;
	AtsType atsType;
};

struct AtsOpCommandMsg {
	int MessageID = 1510;
	int MessageSize;
	bool AstCommand;
};

struct InterceptMsg {
	int MessageID = 1520; // 1520 OR 1320
	int MessageSize;
	bool  SuccessDef;
};

struct AtsStateMsg {
	int MessageID = 5101;
	int MessageSize;
	bool AstState;
};

struct AtsPositionMsg {
	int MessageID = 5110;
	int MessageSize;
	double  X_AstLoc, Y_AstLoc;
};

struct MssScenarioMsg {
	int MessageID = 1301;
	int MessageSize;
	double MssStartX, MssStartY;
	double Velocity;
};

struct MssOpCommandMsg {
	int MessageID = 1310;
	int MessageSize;
	double  XDir, YDir;
	bool Launch;
};

struct MssStateMsg {
	int MessageID = 3110;
	int MessageSize;
	bool MssState;
};

struct MssPositionMsg {
	int MessageID = 3120;
	int MessageSize;
	double X_Pos, Y_Pos;
};