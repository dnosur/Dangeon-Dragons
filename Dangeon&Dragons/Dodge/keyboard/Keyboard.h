#pragma once
#include "KeyboardKey.h"

#define KEY_HISTORY_SIZE 10

class Keyboard
{
	GLFWwindow* window;

	KeyboardKey key;

	KeyboardKey* keys;
	int key_history_index;

	void AddToHistory(KeyboardKey key);
public: 
	Keyboard();
	Keyboard(GLFWwindow* window);
	Keyboard(GLFWwindow* window, GLFWkeyfun handler);

	void Update();

	void HookOnKeyPress(GLFWkeyfun handler);

	KeyboardKey* GetLastKey(int index = 0);

	void SetKey(KeyboardKey key);
	KeyboardKey GetKey();
	KeyboardKey GetKey(KeyboardKeys keyboardKey);
};