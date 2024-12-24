#pragma once
#include <functional>
#include <mutex>

class Thread
{
	char* title;

	std::mutex* m;
	std::thread* t;

	void RemoveThread();
public:
	Thread(const char* title = nullptr);
	Thread(const char* title, std::function<void()> func);
	~Thread();

	bool Start(std::function<void()> func);

	void Join();
	void Detach();

	const char* GetTitle();

	bool IsJoinable();
	bool operator==(Thread* thread);
};