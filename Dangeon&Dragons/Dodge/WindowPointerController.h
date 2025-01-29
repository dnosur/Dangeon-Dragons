#pragma once
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowPointer.h"
#include <vector>

class WindowPointerController
{
	template <typename T>
	static void Save(GLFWwindow* window, std::vector<WindowPointer<T>>* pointers);
public:
	template <typename T>
	static void SetPointer(GLFWwindow* window, WindowPointer<T> pointer);

	template <typename T>
	static WindowPointer<T>* GetValue(GLFWwindow* window, std::string_view title);
};

template<typename T>
inline void WindowPointerController::Save(GLFWwindow* window, std::vector<WindowPointer<T>>* pointers)
{
	glfwSetWindowUserPointer(window, pointers);
}

template<typename T>
inline void WindowPointerController::SetPointer(GLFWwindow* window, WindowPointer<T> pointer)
{
	std::vector<WindowPointer<T>>* pointers = static_cast<std::vector<WindowPointer<T>>*>(glfwGetWindowUserPointer(window));
	if (pointers == nullptr || !pointers->capacity() || pointers->empty()) {
		pointers = new std::vector<WindowPointer<T>>();
		pointers->push_back(pointer);
		WindowPointerController::Save(window, pointers);
		return;
	}

	for (WindowPointer<T> &item : *pointers) {
		if (item.GetTitle() == pointer.GetTitle()) {
			item = pointer;
			WindowPointerController::Save(window, pointers);
			return;
		}
	}

	pointers->push_back(pointer);
}

template<typename T>
inline WindowPointer<T>* WindowPointerController::GetValue(GLFWwindow* window, std::string_view title)
{
	std::vector<WindowPointer<T>>* pointers = static_cast<std::vector<WindowPointer<T>>*>(glfwGetWindowUserPointer(window));
	if (!pointers->capacity() || pointers->empty() || pointers == nullptr) {
		return new WindowPointer<T>();
	}

	for (WindowPointer<T>& item : *pointers) {
		if (item.GetTitle() == title) {
			return &item;
		}
	}
}
