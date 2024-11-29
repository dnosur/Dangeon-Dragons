#pragma once

struct Color
{
	float r, g, b, a;

	Color();
	Color(float r, float g, float b, float a = 1);

	Color ConvertToGl();

	bool operator==(const Color& other) const;
	bool operator!=(const Color& other) const;

	Color& operator=(const Color& other);
};