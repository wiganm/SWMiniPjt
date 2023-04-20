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
		void SendMssScenarioMsg()
		{
			messagehandler->SendMssScenarioMsg();
			printf("ggsdg");
		}

	};
}