#include "Keyboard.h"


void Keyboard::AddToHistory(KeyboardKey key)
{
	keys[key_history_index] = key;
	key_history_index = (key_history_index + 1) == KEY_HISTORY_SIZE ? 0 : key_history_index + 1;
}

Keyboard::Keyboard()
{
	window = nullptr;
}

Keyboard::Keyboard(GLFWwindow* window)
{
	this->window = window;

	keys = new KeyboardKey[KEY_HISTORY_SIZE];
	key_history_index = 0;

	HookOnKeyPress([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowPointer<Keyboard>* keyboard = WindowPointerController::GetValue<Keyboard>("Keyboard");
		if (keyboard == nullptr) {
			return;
		}

		if (action == GLFW_RELEASE && keyboard->GetValue().lock()->GetKey().key != key) {
			return;
		}

		//std::cout << "Key: " << key << " Action: " << action << std::endl;

		keyboard->GetValue().lock()->SetKey(KeyboardKey(key, action, action >= GLFW_PRESS));
	});
}

Keyboard::Keyboard(GLFWwindow* window, GLFWkeyfun handler)
{
	this->window = window;
	keys = new KeyboardKey[KEY_HISTORY_SIZE];
	key_history_index = 0;

	HookOnKeyPress(handler);
}

void Keyboard::Update()
{

}

void Keyboard::HookOnKeyPress(GLFWkeyfun handler)
{
	glfwSetKeyCallback(window, handler);
}

KeyboardKey* Keyboard::GetLastKey(int index)
{
	if (index < 0 || index >= KEY_HISTORY_SIZE) {
		return nullptr;
	}

	return &keys[
		index > key_history_index 
			? KEY_HISTORY_SIZE - (index - key_history_index) 
			: index
	];
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
