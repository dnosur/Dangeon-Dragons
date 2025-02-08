#pragma once
#include "TinySpriteLayer.h"
#include <unordered_map>

class TinySrpiteLayersController
{
	std::unordered_map<int, std::shared_ptr<TinySpriteLayer>> spriteLayers;
	std::vector<int> spriteLayerOrders;
public:
	TinySrpiteLayersController();
	TinySrpiteLayersController(std::unordered_map<int, std::shared_ptr<TinySpriteLayer>> spriteLayers);
	TinySrpiteLayersController(tinyxml2::XMLElement* element);
	~TinySrpiteLayersController();

	static void LoadSpriteLayers(
		tinyxml2::XMLElement* element, 
		std::unordered_map<int, std::shared_ptr<TinySpriteLayer>>& spriteLayers,
		std::vector<int>& spriteLayerOrders
	);

	int GetSize();

	std::weak_ptr<TinySpriteLayer> GetById(int id);

	std::unordered_map<int, std::shared_ptr<TinySpriteLayer>>::iterator begin();
	std::unordered_map<int, std::shared_ptr<TinySpriteLayer>>::iterator end();

	const std::vector<int>& GetSpriteLayerOrders();

	std::weak_ptr<TinySpriteLayer> operator[](int index);
	std::weak_ptr<TinySpriteLayer> operator[](std::string name);
};

