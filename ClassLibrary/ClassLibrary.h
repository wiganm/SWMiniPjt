#pragma once
#include <thread>
#include <GCSClass.h>
#include <MessageHandler.h>
#include <cstring>
#include <windows.h>


namespace Wrapper
{
	public ref class GcsWrapper
	{
	private:
		MessageHandler* messagehandler = new MessageHandler();
	public:
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
			messagehandler->SendMssOpMsg(true);
			messagehandler->SendAtsOpMsg(true);
		}
		
		void StopMss()
		{
			messagehandler->SendMssOpMsg(false);
			messagehandler->SendAtsOpMsg(false);
		}


	};
}