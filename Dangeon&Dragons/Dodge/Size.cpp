#include "Size.h"

Size::Size()
{
	width = height = 0;
}

constexpr Size::Size(const double width, const double height)
	: width(width), height(height)
{

}

double Size::GetWidth()
{
	return width;
}

double Size::GetHeight()
{
	return height;
}

void Size::SetWidth(double width)
{
	if (width < 0) {
		return;
	}
	this->width = width;
}

void Size::SetHeight(double height)
{
	if (height < 0) {
		return;
	}
	this->height = height;
}

bool Size::operator==(const Size& other) const
{
	return other.height == height && other.width == width;
}

bool Size::operator!=(const Size& other) const
{
	return !(*this == other);
}

Size& Size::operator=(const Size& other)
{
	if (this != &other)
	{
		width = other.width;
		height = other.height;
	}
	return *this;
}

Size& Size::operator+=(const Size& other)
{
	width += other.width;
	height += other.height;
	return *this;
}

Size& Size::operator-=(const Size& other)
{
	width -= other.width;
	height -= other.height;
	return *this;
}

Size& Size::operator*=(const Size& other)
{
	width *= other.width;
	height *= other.height;
	return *this;
}

Size& Size::operator/=(const Size& other)
{
	width /= other.width;
	height /= other.height;
	return *this;
}

Size Size::operator+(const Size& other) const
{
	return Size(
		width + other.width,
		height + other.height
	);
}

Size Size::operator-(const Size& other) const
{
	return Size(
		width - other.width,
		height - other.height
	);
}

Size Size::operator*(const Size& other) const
{
	return Size(
		width * other.width,
		height * other.height
	);
}

Size Size::operator/(const Size& other) const
{
	return Size(
		width / other.width,
		height / other.height
	);
}

Size Size::operator+(const int value) const
{
	return Size(width + value, height + value);
}

Size Size::operator-(const int value) const
{
	return Size(width - value, height - value);
}

Size Size::operator*(const int value) const
{
	return Size(width * value, height * value);
}

Size Size::operator/(const int value) const
{
	return Size(width / value, height / value);
}
