#pragma once
#include "KeyboardKey.h"

class Keyboard
{
	GLFWwindow* window;

	KeyboardKey key;
public: 
	Keyboard();
	Keyboard(GLFWwindow* window);
	Keyboard(GLFWwindow* window, GLFWkeyfun handler);

	void Update();

	void HookOnKeyPress(GLFWkeyfun handler);

	void SetKey(KeyboardKey key);
	KeyboardKey GetKey();
	KeyboardKey GetKey(KeyboardKeys keyboardKey);
};