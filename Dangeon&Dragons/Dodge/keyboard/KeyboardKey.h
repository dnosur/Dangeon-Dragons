#pragma once
#include "../WindowPointerController.h"
#include "KeyboardKeys.h"

struct KeyboardKey
{
	int key;
	int action;

	bool pressed;
	bool clamping;

	bool keyProcessed;

	KeyboardKey();
	KeyboardKey(int key, int action, bool pressed = false);

	bool Pressed(KeyboardKeys keyboardKey);

	bool operator==(const KeyboardKey& other) const;
	bool operator!=(const KeyboardKey& other) const;

	KeyboardKey& operator=(const KeyboardKey& other);
};

