#pragma once
#include "TinySpriteLayer.h"

class TinySrpiteLayersController
{
	std::vector<TinySpriteLayer> spriteLayers;
public:
	TinySrpiteLayersController();
	TinySrpiteLayersController(std::vector<TinySpriteLayer> spriteLayers);
	TinySrpiteLayersController(tinyxml2::XMLElement* element);
	~TinySrpiteLayersController();

	static void LoadSpriteLayers(tinyxml2::XMLElement* element, std::vector<TinySpriteLayer>& spriteLayers);

	int GetSize();

	TinySpriteLayer* GetById(int id);

	std::vector<TinySpriteLayer>::iterator begin();
	std::vector<TinySpriteLayer>::iterator end();

	TinySpriteLayer* operator[](int index);
	TinySpriteLayer* operator[](std::string name);
};

