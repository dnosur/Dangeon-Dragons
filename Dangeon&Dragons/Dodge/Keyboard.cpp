#include "Keyboard.h"


Keyboard::Keyboard()
{
	window = nullptr;
}

Keyboard::Keyboard(GLFWwindow* window)
{
	this->window = window;
	HookOnKeyPress([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowPointer<Keyboard>* keyboard = WindowPointerController::GetValue<Keyboard>(window, "Keyboard");
		if (keyboard == nullptr) {
			return;
		}

		if (action == GLFW_RELEASE && keyboard->GetValue().GetKey().key != key) {
			return;
		}

		keyboard->GetValue().SetKey(KeyboardKey(key, action, action >= GLFW_PRESS));
	});
}

Keyboard::Keyboard(GLFWwindow* window, GLFWkeyfun handler)
{
	this->window = window;
	HookOnKeyPress(handler);
}

void Keyboard::Update()
{

}

void Keyboard::HookOnKeyPress(GLFWkeyfun handler)
{
	glfwSetKeyCallback(window, handler);
}

void Keyboard::SetKey(KeyboardKey key)
{
	this->key = key;
}

KeyboardKey Keyboard::GetKey()
{
	return key;
}

KeyboardKey Keyboard::GetKey(KeyboardKeys keyboardKey)
{
	if (key.key == keyboardKey) {
		return key;
	}
	return KeyboardKey();
}
