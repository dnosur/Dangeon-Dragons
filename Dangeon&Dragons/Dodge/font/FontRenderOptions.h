#pragma once
#include "Padding.h"

#include "../Color.h"
#include "../Size.h"

#include <memory>"

struct FontRenderOptions
{
private:
	float scale;
	float spacing;

	std::shared_ptr<Size> renderArea;
	std::shared_ptr<Padding> padding;

	Color color;
public:
	FontRenderOptions(
		float scale = 1.0f, 
		float spacing = 0.0f, 
		std::shared_ptr<Size> renderArea = nullptr, 
		std::shared_ptr<Padding> padding = nullptr, 
		Color color = Color(1.0f, 1.0f, 1.0f, 1.0f)
	);

	const Color& GetColor();

	std::weak_ptr<Size> GetRenderArea();

	std::weak_ptr<Padding> GetPadding();

	const float& GetScale();

	const float& GetSpacing();
};