#pragma once
#include "../../../Dodge/images/ImagesController.h"
#include "../../../Dodge/animator/AnimationController.h"

class Screen
{
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
public:
	Screen();
	~Screen() = default;

	virtual void Update() = 0;
};