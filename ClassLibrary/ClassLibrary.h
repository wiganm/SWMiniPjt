#pragma once
#include <thread>
#include <GCSClass.h>
#include <MessageHandler.h>
#include <cstring>
#include <windows.h>

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Wrapper
{
	public ref class GcsWrapper
	{
	private:
		MessageHandler* messagehandler = new MessageHandler();

		// 관리되지 않는 메모리에서 관리되는 객체에 액세스하기 위한 방법을 제공함
	public:
		
		//- ----------------------------------------------------------------

		void UdpStart() {
			messagehandler->ListenStart();
		}

		void SendScenarioMsg(int ats, double atsVel, double mssX, double mssY, double atsStartX, double atsStartY, double atsDesX, double atsDesY)
		{
			messagehandler->scenarioSetting->SetAtsScenarioMsg(atsStartX, atsStartY, atsDesX, atsDesY, atsVel, ats);
			messagehandler->scenarioSetting->SetMssScenarioMsg(mssX, mssY);
			messagehandler->SendMssScenarioMsg();
			messagehandler->SendAtsScenarioMsg();
		}

		void Start()
		{
			// messagehandler->SendMssOpMsg(true);
			messagehandler->SendAtsOpMsg(true);
		}

		void mssStart()
		{
			messagehandler->SendMssOpMsg(true);
		}
		
		void StopMss()
		{
			messagehandler->SendMssOpMsg(false);
			messagehandler->SendAtsOpMsg(false);
		}


	};
}