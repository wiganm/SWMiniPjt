#pragma once
#include <thread>

// �Լ�������(function pointer) Ÿ�� ����
typedef void(*CALLBACK_FUNC)(int);

// �Լ�������(function pointer) �ϳ� ����
CALLBACK_FUNC cbf = nullptr;

// C++/CLI ���� ȣ��Ǳ� ���ϴ� cli_cb �� �˷��ش�.
void SetHandler(CALLBACK_FUNC cli_cb)
{
	cbf = cli_cb;
}

void Run();