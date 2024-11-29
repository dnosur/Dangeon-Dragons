#pragma once
#include <tinyxml2.h>
#include <vector>

#include "../figures/Rect.h"

class TinySpriteLayer
{
	int id;
	char* name;
	Size size;

	Coord offset;

	int** tileIds;
public:
	TinySpriteLayer();
	TinySpriteLayer(int id, const char* name, Size size, int** tileIds, Coord offset = Coord(0, 0));
	TinySpriteLayer(tinyxml2::XMLElement* element);
	~TinySpriteLayer();

	bool Undefined();

	static void GetSprites(tinyxml2::XMLElement* element, int**& ids);

	int GetId();
	char* GetName();
	Size GetSize();

	int* operator[](int index);
};