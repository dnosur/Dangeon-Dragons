#pragma once
#include <iostream>

#include "functions.h"
#include "WindowPointerBase.h"

template <typename T>
struct WindowPointer : public WindowPointerBase
{
private:
	std::string title;
	std::shared_ptr<T> value;
	bool undefined;

public:
	WindowPointer();
	WindowPointer(std::string title, std::shared_ptr<T> value);
	WindowPointer(std::string title, std::weak_ptr<T> value);
	WindowPointer(std::string title, T* value);

	std::string_view GetTitle();

	void SetValue(T* value);
	std::weak_ptr<T> GetValue();

	const bool IsUndefined();

	bool operator==(const WindowPointer& other) const;
	bool operator!=(const WindowPointer& other) const;
	WindowPointer& operator=(const WindowPointer& other);
};

template<typename T>
inline WindowPointer<T>::WindowPointer()
{
	title = "Undefined";
	undefined = true;
}

template<typename T>
inline WindowPointer<T>::WindowPointer(std::string title, std::shared_ptr<T> value)
{
	this->title = title;
	this->value = std::move(value);
	undefined = false;
}

template<typename T>
inline WindowPointer<T>::WindowPointer(std::string title, std::weak_ptr<T> value)
{
	this->title = title;
	if (value.lock()) {
		this->value = value.lock();
	}
	undefined = false;
}

template<typename T>
inline WindowPointer<T>::WindowPointer(std::string title, T* value)
{
	this->title = title;
	this->value = std::make_shared<T>(*value);
	undefined = false;
}

template<typename T>
inline std::string_view WindowPointer<T>::GetTitle()
{
	return title;
}

template<typename T>
inline void WindowPointer<T>::SetValue(T* value)
{
	this->value = value;
}

template<typename T>
inline std::weak_ptr<T> WindowPointer<T>::GetValue()
{
	return value;
}

template<typename T>
inline const bool WindowPointer<T>::IsUndefined()
{
	return undefined;
}

template<typename T>
inline bool WindowPointer<T>::operator==(const WindowPointer& other) const
{
	return value.get() == other.value.get() && title == other.title && undefined == other.undefined;
}

template<typename T>
inline bool WindowPointer<T>::operator!=(const WindowPointer& other) const
{
	return !(*this == other);
}

template<typename T>
inline WindowPointer<T>& WindowPointer<T>::operator=(const WindowPointer& other)
{
	if (this != &other)
	{
		value = std::move(other.value);
		title = other.title;
		undefined = other.undefined;
	}
	return *this;
}
