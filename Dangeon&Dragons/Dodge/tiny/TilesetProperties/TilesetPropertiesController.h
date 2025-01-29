#pragma once
#include <tinyxml2.h>
#include <vector>

#include "Propertie.h"

class TilesetPropertiesController
{
	std::vector<Propertie*> tilesetProperties;
public:
	TilesetPropertiesController();
	TilesetPropertiesController(std::vector<Propertie*> tilesetProperties);
	TilesetPropertiesController(tinyxml2::XMLElement* tileset);
	~TilesetPropertiesController();

	std::vector<Propertie*>::iterator begin();
	std::vector<Propertie*>::iterator end();

	int GetSize();

	Propertie* operator[](std::string name);
	Propertie* operator[](int index);

	static void readTilesetProperties(tinyxml2::XMLElement* tileset, std::vector<Propertie*>& tilesetProperties);
	static tinyxml2::XMLElement* getTilesetProperties(tinyxml2::XMLElement* tileset);
};