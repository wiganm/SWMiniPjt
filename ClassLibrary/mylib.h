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

// ���� ó���ϴ� �Լ� ����
// x ��ǥ�� ������Ų��.
int step(int x)
{
	x = x + 1;

	// C++/CLI �� ������.
	// ��, �̺�Ʈ �߻� ȿ��
	if (cbf)
		cbf(x);

	return 0;
}

// ������ ����
void run()
{
	std::thread t1([&]() {
		for (int i = 0; i < 5; i++) {
			step(i);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		});

	// detach �� ������ �ȵǴ� ������,
	// join() �ϸ� �ȵǴ� ������ �����غ���
	t1.detach();
	//t1.join();
}
