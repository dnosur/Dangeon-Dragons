#pragma once
#include <tinyxml2.h>
#include <vector>

#include "../figures/Rect.h"
#include "TinyChunk.h"

class TinySpriteLayer
{
	int id;
	char* name;
	Size size;

	Coord offset;

	std::vector<TinyChunk*> chunks;
public:
	TinySpriteLayer();
	TinySpriteLayer(int id, const char* name, Size size, int** tileIds, Coord offset = Coord(0, 0));
	TinySpriteLayer(tinyxml2::XMLElement* element);
	~TinySpriteLayer();

	bool Undefined();

	static void GetSprites(tinyxml2::XMLElement* element, std::vector<TinyChunk*>& chunks);
	static void LoadChunkIds(std::string data, int**& ids, Size size);

	int GetId();
	char* GetName();
	Size GetSize();

	int GetChunksCount();

	TinyChunk* operator[](int index);
};