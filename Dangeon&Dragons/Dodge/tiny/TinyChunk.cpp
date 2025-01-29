#include "TinyChunk.h"
#include "../functions.h"

#include "TinySpriteLayer.h"

TinyChunk::TinyChunk()
{
	tileIds = nullptr;
}

TinyChunk::TinyChunk(Coord coord, Size size, int** tileIds)
{
	this->coord = coord;
	this->size = size;
	CopyArray<int>(tileIds, this->tileIds);
}

TinyChunk::TinyChunk(tinyxml2::XMLElement* element)
{
	coord = Coord(element->IntAttribute("x"), element->IntAttribute("y"));
	size = Size(element->IntAttribute("width"), element->IntAttribute("height"));
	TinySpriteLayer::LoadChunkIds(element->GetText(), tileIds, size);
}

bool TinyChunk::Undefined()
{
	return tileIds == nullptr;
}

TinyChunk::~TinyChunk()
{
	if (tileIds != nullptr) {
		for (int i = 0; i < size.height; i++) {
			delete[] tileIds[i];
		}
		delete[] tileIds;
	}
}

int* TinyChunk::operator[](int index)
{
	if (index < 0 || index >= size.height) {
		return nullptr;
	}
	return tileIds[index];
}

bool TinyChunk::operator==(const TinyChunk& other) const
{
	return other.tileIds == tileIds && other.size == size && other.coord == coord;
}

bool TinyChunk::operator!=(const TinyChunk& other) const
{
	return !(*this == other);
}

TinyChunk& TinyChunk::operator=(const TinyChunk& other)
{
	if (this != &other) {
		coord = other.coord;
		size = other.size;
		CopyArray<int>(other.tileIds, tileIds);
	}
	return *this;
}
