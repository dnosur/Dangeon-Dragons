#pragma once
#include <tinyxml2.h>
#include <vector>

#include "../figures/Rect.h"
#include "TinyChunk.h"

class TinySpriteLayer
{
	int id;
	std::string name;
	Size size;

	Coord offset;

	std::vector<std::shared_ptr<TinyChunk>> chunks;
public:
	TinySpriteLayer();
	TinySpriteLayer(int id, std::string name, Size size, int** tileIds, Coord offset = Coord(0, 0));
	TinySpriteLayer(tinyxml2::XMLElement* element);
	~TinySpriteLayer();

	bool Undefined();

	static void GetSprites(tinyxml2::XMLElement* element, std::vector<std::shared_ptr<TinyChunk>>& chunks);
	static void LoadChunkIds(std::string data, int**& ids, Size size);

	int GetId();
	std::string GetName();
	Size GetSize();

	int GetChunksCount();

	std::weak_ptr<TinyChunk> operator[](int index);
};