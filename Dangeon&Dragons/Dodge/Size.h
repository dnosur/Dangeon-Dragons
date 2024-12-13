#pragma once
struct alignas(16) Size
{
	double width, height;
public:

	Size();
	constexpr Size(const double width, const double height);

	double GetWidth();
	double GetHeight();

	void SetWidth(double width);
	void SetHeight(double height);

	bool operator==(const Size& other) const;
	bool operator!=(const Size& other) const;
	Size& operator=(const Size& other);

	Size& operator+=(const Size& other);
	Size& operator-=(const Size& other);

	Size& operator*=(const Size& other);
	Size& operator/=(const Size& other);

	Size operator+(const Size& other) const;
	Size operator-(const Size& other) const;
	Size operator*(const Size& other) const;
	Size operator/(const Size& other) const;
};