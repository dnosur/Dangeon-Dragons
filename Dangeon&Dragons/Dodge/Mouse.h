#pragma once
#include <iostream>

#include "Coord.h"
#include "WindowPointerController.h"

class Mouse
{
	GLFWwindow* window;

	Coord prev;
	Coord curr;

	bool click;
public:
	Mouse();
	Mouse(GLFWwindow* window);
	Mouse(GLFWwindow* window, GLFWmousebuttonfun handler);

	void Update();

	Coord GetMouseCoord();
	Coord GetPrevMouseCoord();

	void HookMouseHandler(GLFWmousebuttonfun handler);

	bool isClick();
	void Click();

	bool IsEqual();
};