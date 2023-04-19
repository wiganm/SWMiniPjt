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

void Run();