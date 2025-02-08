#include "Mouse.h"

#include "Window.h"

Mouse::Mouse()
{
	click = false;
	window = NULL;
}

Mouse::Mouse(GLFWwindow* window)
{
	this->window = window;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	prev = Coord(mouseX, mouseY);
	curr = Coord(mouseX, mouseY);
	click = false;

	HookMouseHandler([](GLFWwindow* window, int button, int action, int mods) {
		std::shared_ptr<Mouse> mouse = Window::GetMouse().lock();
		if (!mouse) {
			return;
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			mouse->Click();
		}
	});
}

Mouse::Mouse(GLFWwindow* window, GLFWmousebuttonfun handler)
{
	this->window = window;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	prev = Coord(mouseX, mouseY);
	curr = Coord(mouseX, mouseY);
	click = false;

	HookMouseHandler(handler);
}

void Mouse::Update()
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	prev = curr;
	curr = Coord(mouseX, mouseY);

	if (click) {
		std::cout << "Click!\n";
	}
	click = false;
}

Coord Mouse::GetMouseCoord()
{
	return curr;
}

Coord Mouse::GetPrevMouseCoord()
{
	return prev;
}

void Mouse::HookMouseHandler(GLFWmousebuttonfun handler)
{
	glfwSetMouseButtonCallback(window, handler);
}

bool Mouse::isClick()
{
	return click;
}

void Mouse::Click()
{
	click = true;
}

bool Mouse::IsEqual()
{
	return prev == curr;
}
