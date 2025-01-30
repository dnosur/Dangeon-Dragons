#include "TinySrpiteLayersController.h"

TinySrpiteLayersController::TinySrpiteLayersController()
{
}

TinySrpiteLayersController::TinySrpiteLayersController(std::unordered_map<int, std::shared_ptr<TinySpriteLayer>> spriteLayers)
{
	this->spriteLayers = spriteLayers;
}

TinySrpiteLayersController::TinySrpiteLayersController(tinyxml2::XMLElement* element)
{
	LoadSpriteLayers(element, spriteLayers);
}

TinySrpiteLayersController::~TinySrpiteLayersController()
{
}

void TinySrpiteLayersController::LoadSpriteLayers(tinyxml2::XMLElement* element, std::unordered_map<int, std::shared_ptr<TinySpriteLayer>>& spriteLayers)
{
	for (tinyxml2::XMLElement* group = element->FirstChildElement("group");
		group != nullptr;
		group = group->NextSiblingElement("group")
		) {
		for (tinyxml2::XMLElement* layer = group->FirstChildElement("layer");
			layer != nullptr;
			layer = layer->NextSiblingElement("layer")
			) {
			if (layer) {
				std::unique_ptr<TinySpriteLayer> temp = std::make_unique<TinySpriteLayer>(layer);
				spriteLayers[temp->GetId()] = std::move(temp);
				std::cout << layer->Attribute("name") << " OK" << std::endl;
				continue;
			}
			std::cout << layer->Attribute("name") << " ERROR!" << std::endl;
		}
	}
}

int TinySrpiteLayersController::GetSize()
{
	return spriteLayers.size();
}

std::weak_ptr<TinySpriteLayer> TinySrpiteLayersController::GetById(int id)
{
	auto it = spriteLayers.find(id);
	if (it == spriteLayers.end())
	{
		return {};
	}
	return it->second;
}

std::unordered_map<int, std::shared_ptr<TinySpriteLayer>>::iterator TinySrpiteLayersController::begin()
{
	return spriteLayers.begin();
}

std::unordered_map<int, std::shared_ptr<TinySpriteLayer>>::iterator TinySrpiteLayersController::end()
{
	return spriteLayers.end();
}

std::weak_ptr<TinySpriteLayer> TinySrpiteLayersController::operator[](int index)
{
	if (index < 0 || index >= spriteLayers.size())
	{
		return {};
	}

	auto it = spriteLayers.begin();
	std::advance(it, index);
	return it->second;
}

std::weak_ptr<TinySpriteLayer> TinySrpiteLayersController::operator[](std::string name)
{
	for (auto& item : spriteLayers)
	{
		if (item.second->GetName() == name)
		{
			return item.second;
		}
	}
	return {};
}
