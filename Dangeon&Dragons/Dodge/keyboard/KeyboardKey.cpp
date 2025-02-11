#include "KeyboardKey.h"

KeyboardKey::KeyboardKey()
{
	key = action = -1;
	keyProcessed = clamping = pressed = false;
}

KeyboardKey::KeyboardKey(int key, int action, bool pressed)
{
	this->key = key;
	this->action = action;
	this->pressed = pressed;

	clamping = action >= 2;
}

bool KeyboardKey::Pressed(KeyboardKeys keyboardKey)
{
	return key == keyboardKey && pressed;
}

bool KeyboardKey::Up(KeyboardKeys keyboardKey)
{
	return key == keyboardKey && !pressed;
}

bool KeyboardKey::operator==(const KeyboardKey& other) const
{
	return other.key == key && other.action == action 
		&& other.pressed == pressed && other.clamping == clamping;
}

bool KeyboardKey::operator==(const KeyboardKeys& other) const
{
	return key == other;
}

bool KeyboardKey::operator!=(const KeyboardKey& other) const
{
	return !(*this == other);
}

KeyboardKey& KeyboardKey::operator=(const KeyboardKey& other)
{
	if (this == &other) {
		return *this;
	}

	this->key = other.key;
	this->action = other.action;
	this->pressed = other.pressed;
	this->clamping = other.clamping;

	return *this;
}
