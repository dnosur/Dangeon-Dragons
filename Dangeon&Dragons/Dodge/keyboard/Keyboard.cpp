#include "Keyboard.h"
#include "../Window.h"

Keyboard::Keyboard()
{
	window = nullptr;

	down = nullptr;
	up = nullptr;
}

Keyboard::Keyboard(GLFWwindow* window)
{
	this->window = window;

	down = nullptr;
	up = nullptr;

	HookOnKeyPress([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		std::shared_ptr<Keyboard> keyboard = Window::GetKeyboard().lock();
		if (!keyboard) {
			return;
		}

		std::cout << "Key: " << key << " Action: " << action << std::endl;

		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			keyboard->KeyDown(KeyboardKey(key, action, true));
		}
		
		if (action == GLFW_RELEASE) {
			keyboard->KeyUp(KeyboardKey(key, action));
		}
	});
}

Keyboard::Keyboard(GLFWwindow* window, GLFWkeyfun handler)
{
	this->window = window;

	down = nullptr;
	up = nullptr;

	HookOnKeyPress(handler);
}

void Keyboard::Update()
{
	if (up && !down) {
		up.release();
		return;
	}

	if (!down || !up) {
		return;
	}

	if (down->keyProcessed && up->keyProcessed) {
		std::cout << "Release" << std::endl;

		down.release();
		up.release();
	}
}

void Keyboard::Release()
{
	down.release();
	up.release();
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

	return nullptr;
}

void Keyboard::KeyDown(KeyboardKey key)
{
	if (onKeyDown) {
		onKeyDown(key);
	}

	down = std::make_unique<KeyboardKey>(key);
	unuppedKeys[KeyboardKeys(down->key)] = key;

	if (up) {
		up.release();
	}
}

void Keyboard::KeyUp(KeyboardKey key)
{
	if (onKeyUp) {
		onKeyUp(key);
	}

	unuppedKeys.erase(KeyboardKeys(key.key));
	std::cout << "Unupped keys: " << unuppedKeys.size() << std::endl;

	if (!unuppedKeys.empty()) {
		Release();

		down = std::make_unique<KeyboardKey>(std::prev(unuppedKeys.end())->second);
		return;
	}

	up = std::make_unique<KeyboardKey>(key);
}

bool Keyboard::Pressed(KeyboardKeys keyboardKey, bool release)
{
	auto it = unuppedKeys.find(keyboardKey);
	bool result = (down && down->Pressed(keyboardKey)) || 
		(it != unuppedKeys.end() && it->second.Pressed(keyboardKey));

	if (result) {
		down->keyProcessed = true;
	}

	if (up) {
		up->keyProcessed = true;
	}

	if (release && result) {
		Release();
	}

	return result;
}

bool Keyboard::Click(KeyboardKeys keyboardKey, bool release)
{
	if (!(down && up && down->Pressed(keyboardKey) && up->Up(keyboardKey))) {
		return false;
	}

	down->keyProcessed = true;
	up->keyProcessed = true;

	if (release) {
		Release();
	}

	return true;
}

KeyboardKey* Keyboard::GetKeyDown()
{
	return down ? down.get() : nullptr;
}

KeyboardKey* Keyboard::GetKeyUp()
{
	return up ? up.get() : nullptr;
}

void Keyboard::OnKeyDown(std::function<void(KeyboardKey&)> handler)
{
	onKeyDown = handler;
}

void Keyboard::OnKeyUp(std::function<void(KeyboardKey&)> handler)
{
	onKeyUp = handler;
}
