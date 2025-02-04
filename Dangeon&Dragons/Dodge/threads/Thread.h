#pragma once
#include <functional>
#include <mutex>

class Thread
{
	std::string title;

	std::mutex* m;
	std::thread* t;

	void RemoveThread();
public:
	Thread(std::string title = nullptr);
	Thread(std::string title, std::function<void()> func);
	~Thread();

	bool Start(std::function<void()> func);

	void Join();
	void Detach();

	std::string_view GetTitle();

	std::mutex*& GetMutex();

	bool IsJoinable();
	bool operator==(Thread* thread);
};