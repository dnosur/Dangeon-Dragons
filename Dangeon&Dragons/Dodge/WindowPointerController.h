#pragma once
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowPointer.h"

#include <vector>
#include <unordered_map>
#include <typeindex>

#include <memory>

class WindowPointerController
{
	static std::unordered_map<std::type_index, std::unordered_map<std::string, std::unique_ptr<WindowPointerBase>>> pointers;
public:
	template <typename T>
	static void SetPointer(WindowPointer<T> pointer);

	template <typename T>
	static WindowPointer<T>* GetValue(std::string_view title);
};

template<typename T>
inline void WindowPointerController::SetPointer(WindowPointer<T> pointer)
{
	pointers[typeid(T)][std::string(pointer.GetTitle())] = std::make_unique<WindowPointer<T>>(pointer);
}

template<typename T>
inline WindowPointer<T>* WindowPointerController::GetValue(std::string_view title)
{
	auto typeIt = pointers.find(typeid(T));
	if (typeIt == pointers.end()) {
		return nullptr;
	}

	auto it = typeIt->second.find(std::string(title));

	if (it == typeIt->second.end()) {
		return nullptr;
	}

	WindowPointer<T>* pointer = dynamic_cast<WindowPointer<T>*>(it->second.get());;
	if (!pointer) return nullptr;
	return pointer;
}