#pragma once
#include <iostream>
#include "functions.h"

template <typename T>
struct WindowPointer
{
private:
	std::string title;
	T* value;
	bool undefined;

public:

	WindowPointer();
	WindowPointer(std::string title, T* value);

	std::string_view GetTitle();

	void SetValue(T* value);
	T& GetValue();

	const bool IsUndefined();

	bool operator==(const WindowPointer& other) const;
	bool operator!=(const WindowPointer& other) const;
	WindowPointer& operator=(const WindowPointer& other);
};

template<typename T>
inline WindowPointer<T>::WindowPointer()
{
	title = "Undefined";
	value = nullptr;
	undefined = true;
}

template<typename T>
inline WindowPointer<T>::WindowPointer(std::string title, T* value)
{
<<<<<<< Updated upstream
	copyStr(title, this->title);
=======
	this->title = title;
>>>>>>> Stashed changes

	this->value = value;
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
inline T& WindowPointer<T>::GetValue()
{
	return *value;
}

template<typename T>
inline const bool WindowPointer<T>::IsUndefined()
{
	return undefined;
}

template<typename T>
inline bool WindowPointer<T>::operator==(const WindowPointer& other) const
{
	return value == other.value && title == other.title && undefined == other.undefined;
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
		value = other.value;
<<<<<<< Updated upstream
		copyStr(other.title, this->title);
=======
		title = other.title;
>>>>>>> Stashed changes
		undefined = other.undefined;
	}
	return *this;
}
