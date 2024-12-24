#include "GameThreads.h"

std::vector<Thread*>* GameThreads::threads = new std::vector<Thread*>();

void GameThreads::AddThread(Thread* thread)
{
	Thread* t = GetThread(thread->GetTitle());

	if (t) {
		delete t;
		t = thread;
		return;
	}

	threads->push_back(thread);
}

Thread* GameThreads::GetThread(const int id)
{
	if (id < 0 || id >= GameThreads::threads->size()) {
		return nullptr;
	}
	return (*GameThreads::threads)[id];
}

Thread* GameThreads::GetThread(const char* title)
{
	for(Thread* thread : *GameThreads::threads) {
		if (!strcmp(thread->GetTitle(), title)) {
			return thread;
		}
	}
	return nullptr;
}

void GameThreads::RemoveThread(const char* title)
{
	Thread* t = GetThread(title);

	if (t) {
		delete t;
		return;
	}
}

void GameThreads::RemoveThread(const int id)
{
	Thread* t = GetThread(id);

	if (t) {
		delete t;
		return;
	}
}

void GameThreads::Clear()
{
	if (threads->empty()) {
		return;
	}

	threads->clear();
}
