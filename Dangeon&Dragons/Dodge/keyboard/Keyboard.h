#pragma once
#include "KeyboardKey.h"

#include <functional>

#define KEY_HISTORY_SIZE 10

class Keyboard
{
	GLFWwindow* window;

	std::unique_ptr<KeyboardKey> down;
	std::unique_ptr<KeyboardKey> up;

	std::function<void(KeyboardKey&)> onKeyDown;
	std::function<void(KeyboardKey&)> onKeyUp;
public: 
	Keyboard();
	Keyboard(GLFWwindow* window);
	Keyboard(GLFWwindow* window, GLFWkeyfun handler);

	void Update();

	void Release();

	void HookOnKeyPress(GLFWkeyfun handler);

	KeyboardKey* GetLastKey(int index = 0);

	void KeyDown(KeyboardKey key);
	void KeyUp(KeyboardKey key);

	bool Pressed(KeyboardKeys keyboardKey, bool release = false);

	bool Click(KeyboardKeys keyboardKey, bool release = false);

	KeyboardKey* GetKeyDown();
	KeyboardKey* GetKeyUp();

	void OnKeyDown(std::function<void(KeyboardKey&)> handler);
	void OnKeyUp(std::function<void(KeyboardKey&)> handler);
};