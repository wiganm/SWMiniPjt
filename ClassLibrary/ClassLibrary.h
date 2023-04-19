#pragma once
#include <thread>
#include <GCSClass.h>
#include <MessageHandler.h>


namespace Wrapper
{
	public ref class GcsWrapper
	{
	private:
		MessageHandler* messagehandler = new MessageHandler();
	public:
		void SendMssScenarioMsg()
		{
			messagehandler->SendMssScenarioMsg();
			printf("tetewtwetew");
		}

	};
}