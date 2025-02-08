#include "FontRenderOptions.h"

FontRenderOptions::FontRenderOptions(
	float scale, 
	float spacing, 
	std::shared_ptr<Size> renderArea, 
	std::shared_ptr<Padding> padding, 
	Color color
): scale(scale), spacing(spacing), renderArea(std::move(renderArea)), padding(std::move(padding)), color(color) {}

const Color& FontRenderOptions::GetColor()
{
	return color;
}

std::weak_ptr<Size> FontRenderOptions::GetRenderArea()
{
	return renderArea;
}

std::weak_ptr<Padding> FontRenderOptions::GetPadding()
{
	return padding;
}

const float& FontRenderOptions::GetScale()
{
	return scale;
}

const float& FontRenderOptions::GetSpacing()
{
	return spacing;
}
