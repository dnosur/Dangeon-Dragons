#pragma once
#include <tinyxml2.h>

#include "../Coord.h"
#include "../Size.h"

struct TinyChunk
{
	Coord coord;
	Size size;

	int** tileIds;

	TinyChunk();
	TinyChunk(Coord coord, Size size, int** tileIds);
	TinyChunk(tinyxml2::XMLElement* element);

	bool Undefined();

	~TinyChunk();

	int* operator[](int index);

	bool operator==(const TinyChunk& other) const;
	bool operator!=(const TinyChunk& other) const;

	TinyChunk& operator=(const TinyChunk& other);
};

