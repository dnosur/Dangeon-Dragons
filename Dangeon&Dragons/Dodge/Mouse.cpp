#include "Mouse.h"

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
		WindowPointer<Mouse>* mouse = WindowPointerController::GetValue<Mouse>("Mouse");
		if (mouse == nullptr) {
			return;
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			mouse->GetValue().lock()->Click();
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
