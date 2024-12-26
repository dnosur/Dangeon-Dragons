#pragma once
#include <filesystem>
#include <iostream>

struct TileMap;

class Tileset;
class TilesetsController;

class TinyClass;
class TinyClassController;

class TinySpriteLayer;
class TinySpriteLayersController;

__interface ICollision;

#include "tinyxml2.h"

#include "../collisions/BoxCollision.h"
#include "../collisions/PoligonCollision.h"

#include <boost/container/vector.hpp>

namespace fs = std::filesystem;

static class TinyXml
{
	static const char* root_dir;
public:
	static tinyxml2::XMLError ReadDoc(tinyxml2::XMLDocument& doc, const char* path);
	static TileMap* LoadMap(const char* path, const char* title = "sampleMap");

	static boost::container::vector<Coord> ParsePolygon(std::string polygon, const Coord& offset);
	static std::string GetPathToTileSource(std::string path);
};

