#pragma once
#include <vector>

#include "Thread.h"

static class GameThreads
{
	static std::vector<Thread*>* threads;
public:
	static void AddThread(Thread* thread);

	static Thread* GetThread(const int id);
	static Thread* GetThread(std::string_view title);

	static void RemoveThread(std::string_view title);
	static void RemoveThread(const int id);

	static void Clear();
};