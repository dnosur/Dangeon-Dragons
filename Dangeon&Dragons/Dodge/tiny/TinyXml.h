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

namespace fs = std::filesystem;

static class TinyXml
{
	static std::string root_dir;
public:
	static tinyxml2::XMLError ReadDoc(tinyxml2::XMLDocument& doc, std::string path);
	static std::unique_ptr<TileMap> LoadMap(std::string path, std::string title = "sampleMap");

	static std::vector<Coord> ParsePolygon(std::string polygon, const Coord& offset);
	static std::string GetPathToTileSource(std::string path);
};

