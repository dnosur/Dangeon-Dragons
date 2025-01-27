#include "Thread.h"
#include "../functions.h"

void Thread::RemoveThread()
{
	if (t == nullptr) 
	{
		return;
	}

	try {
		if (t->joinable()) {
			t->join();
		}
	}
	catch (const std::system_error& e) {
		std::cerr << "Thread join error: " << e.what() << std::endl;
	}

	delete t;
	t = nullptr;
}
Thread::Thread(const char* title)
{
	CopyStr(title, this->title);

	m = nullptr;
	t = nullptr;
}

Thread::Thread(
	const char* title, 
	std::function<void()> func
)
{
	CopyStr(title, this->title);
	m = new std::mutex();
	t = new std::thread([this, func]() {
		std::lock_guard<std::mutex> lock(*m);
		func();
	});
}

bool Thread::Start(std::function<void()> func)
{
	RemoveThread();
	if (t != nullptr) {
		return false;
	}

	if (m == nullptr)
	{
		m = new std::mutex();
	}

	t = new std::thread([this, func]() {
		std::lock_guard<std::mutex> lock(*m);
		func();
	});
	return true;
}

void Thread::Join()
{
	if (IsJoinable())
	{
		t->join();
	}
}

void Thread::Detach()
{
	if (t != nullptr)
	{
		t->detach();
	}
}

const char* Thread::GetTitle()
{
	return title;
}

bool Thread::IsJoinable()
{
	return t != nullptr && t->joinable();
}

bool Thread::operator==(Thread* thread)
{
	return !strcmp(thread->title, title);
}

Thread::~Thread()
{
	if (title != nullptr)
	{
		delete[] title;
		title = nullptr;
	}

	RemoveThread();

	if (m != nullptr)
	{
		delete m;
		m = nullptr;
	}
}
