#pragma once
struct Frame
{
	int tileId;
	float duration;

	Frame();
	Frame(int tileId, float duration = 0);

	bool operator==(const Frame& other) const;
	bool operator!=(const Frame& other) const;

	Frame& operator=(const Frame& other);
};