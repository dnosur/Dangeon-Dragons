#pragma once
#include <memory>

template <typename T>
bool ValidWeakPtr(const std::weak_ptr<T>& ptr);

template<typename T>
inline bool ValidWeakPtr(const std::weak_ptr<T>& ptr)
{
	return !ptr.expired() || ptr.lock();
}
