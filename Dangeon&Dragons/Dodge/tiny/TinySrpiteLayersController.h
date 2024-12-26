#pragma once
#include "TinySpriteLayer.h"

#include <boost/container/vector.hpp>

class TinySrpiteLayersController
{
	boost::container::vector<TinySpriteLayer> spriteLayers;
public:
	TinySrpiteLayersController();
	TinySrpiteLayersController(boost::container::vector<TinySpriteLayer> spriteLayers);
	TinySrpiteLayersController(tinyxml2::XMLElement* element);
	~TinySrpiteLayersController();

	static void LoadSpriteLayers(
		tinyxml2::XMLElement* element, 
		boost::container::vector<TinySpriteLayer>& spriteLayers
	);

	int GetSize();

	TinySpriteLayer* GetById(int id);

	boost::container::vector<TinySpriteLayer>::iterator begin();
	boost::container::vector<TinySpriteLayer>::iterator end();

	TinySpriteLayer* operator[](int index);
	TinySpriteLayer* operator[](const char* name);
};

