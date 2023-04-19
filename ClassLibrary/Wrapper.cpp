#include "pch.h"

#include "Wrapper.h"
#include "GCSClass.h"

void Run()
{
	std::thread t1([&]() {
		for (int i = 0; i < 5; i++) {
			// 실행할 것 하라
			std::this_thread::sleep_for(std::chrono::seconds(1/2));
		}
		});

	// detach 가 없으면 안되는 이유와,
	// join() 하면 안되는 이유를 생각해보자
	t1.detach();
	//t1.join();
}