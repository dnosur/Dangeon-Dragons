#pragma once
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowPointer.h"
#include <vector>

#include <boost/container/small_vector.hpp>

class WindowPointerController
{
	template <typename T>
	static void Save(GLFWwindow* window, boost::container::small_vector<WindowPointer<T>, 32>* pointers);
public:
	template <typename T>
	static void SetPointer(GLFWwindow* window, WindowPointer<T> pointer);

	template <typename T>
	static WindowPointer<T>* GetValue(GLFWwindow* window, const char* title);
};

template<typename T>
inline void WindowPointerController::Save(
	GLFWwindow* window, 
	boost::container::small_vector<WindowPointer<T>, 32>* pointers)
{
	glfwSetWindowUserPointer(window, pointers);
}

template<typename T>
inline void WindowPointerController::SetPointer(GLFWwindow* window, WindowPointer<T> pointer)
{
	boost::container::small_vector<WindowPointer<T>, 32>* pointers = static_cast<boost::container::small_vector<WindowPointer<T>, 32>*>(glfwGetWindowUserPointer(window));
	if (pointers == nullptr || !pointers->capacity() || pointers->empty()) {
		pointers = new boost::container::small_vector<WindowPointer<T>, 32>();
		pointers->push_back(pointer);
		WindowPointerController::Save(window, pointers);
		return;
	}

	for (WindowPointer<T> &item : *pointers) {
		if (!strcmp(item.GetTitle(), pointer.GetTitle())) {
			item = pointer;
			WindowPointerController::Save(window, pointers);
			return;
		}
	}

	pointers->push_back(pointer);
}

template<typename T>
inline WindowPointer<T>* WindowPointerController::GetValue(GLFWwindow* window, const char* title)
{
	boost::container::small_vector<WindowPointer<T>, 32>* pointers = static_cast<boost::container::small_vector<WindowPointer<T>, 32>*>(glfwGetWindowUserPointer(window));
	if (!pointers->capacity() || pointers->empty() || pointers == nullptr) {
		return new WindowPointer<T>();
	}

	for (WindowPointer<T>& item : *pointers) {
		if (!strcmp(item.GetTitle(), title)) {
			return &item;
		}
	}
}
