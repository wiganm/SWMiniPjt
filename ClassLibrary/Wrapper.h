#pragma once
#include <thread>

#include "../GCS/GCSClass.h"

namespace Wrapper
{
	public ref class GcsWrapper
	{
	private:
		ScenarioSetting* ss = new ScenarioSetting();
	public:
		void test()
		{
			ss->GetAtsScenarioMsg();
			printf("test");
		}
	};
}