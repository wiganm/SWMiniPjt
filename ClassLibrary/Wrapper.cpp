#include "pch.h"

#include "Wrapper.h"
#include "GCSClass.h"

void Run()
{
	std::thread t1([&]() {
		for (int i = 0; i < 5; i++) {
			// ������ �� �϶�
			std::this_thread::sleep_for(std::chrono::seconds(1/2));
		}
		});

	// detach �� ������ �ȵǴ� ������,
	// join() �ϸ� �ȵǴ� ������ �����غ���
	t1.detach();
	//t1.join();
}