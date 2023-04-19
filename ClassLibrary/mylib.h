#pragma once
#include <thread>

// 함수포인터(function pointer) 타입 정의
typedef void(*CALLBACK_FUNC)(int);

// 함수포인터(function pointer) 하나 생성
CALLBACK_FUNC cbf = nullptr;

// C++/CLI 에서 호출되길 원하는 cli_cb 를 알려준다.
void SetHandler(CALLBACK_FUNC cli_cb)
{
	cbf = cli_cb;
}

// 뭔가 처리하는 함수 예제
// x 좌표를 증가시킨다.
int step(int x)
{
	x = x + 1;

	// C++/CLI 로 보낸다.
	// 즉, 이벤트 발생 효과
	if (cbf)
		cbf(x);

	return 0;
}

// 스레드 예제
void run()
{
	std::thread t1([&]() {
		for (int i = 0; i < 5; i++) {
			step(i);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		});

	// detach 가 없으면 안되는 이유와,
	// join() 하면 안되는 이유를 생각해보자
	t1.detach();
	//t1.join();
}
