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
Thread::Thread(std::string title)
{
	this->title = title;

	m = nullptr;
	t = nullptr;
}

Thread::Thread(
	std::string title, 
	std::function<void()> func
)
{
	this->title = title;

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

std::string_view Thread::GetTitle()
{
	return title;
}

bool Thread::IsJoinable()
{
	return t != nullptr && t->joinable();
}

bool Thread::operator==(Thread* thread)
{
	return thread->title == title;
}

Thread::~Thread()
{
	RemoveThread();

	if (m != nullptr)
	{
		delete m;
		m = nullptr;
	}
}
