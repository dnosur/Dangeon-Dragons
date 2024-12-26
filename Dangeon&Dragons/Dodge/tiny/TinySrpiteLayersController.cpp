#include "TinySrpiteLayersController.h"

TinySrpiteLayersController::TinySrpiteLayersController()
{
	spriteLayers = boost::container::vector<TinySpriteLayer>();
}

TinySrpiteLayersController::TinySrpiteLayersController(boost::container::vector<TinySpriteLayer> spriteLayers)
{
	this->spriteLayers = spriteLayers;
}

TinySrpiteLayersController::TinySrpiteLayersController(tinyxml2::XMLElement* element)
{
	LoadSpriteLayers(element, spriteLayers);
}

TinySrpiteLayersController::~TinySrpiteLayersController()
{
	if (spriteLayers.empty()) {
		return;
	}
	spriteLayers.clear();
}

void TinySrpiteLayersController::LoadSpriteLayers(
	tinyxml2::XMLElement* element, 
	boost::container::vector<TinySpriteLayer>& spriteLayers
){
	for (tinyxml2::XMLElement* group = element->FirstChildElement("group");
		group != nullptr;
		group = group->NextSiblingElement("group")
		) {
		for (tinyxml2::XMLElement* layer = group->FirstChildElement("layer");
			layer != nullptr;
			layer = layer->NextSiblingElement("layer")
			) {
			if (layer) {
				spriteLayers.push_back(TinySpriteLayer(layer));
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

TinySpriteLayer* TinySrpiteLayersController::GetById(int id)
{
	for (int i = 0; i < spriteLayers.size(); i++)
	{
		if (spriteLayers[i].GetId() == id)
		{
			return &spriteLayers[i];
		}
	}
	return nullptr;
}

boost::container::vector<TinySpriteLayer>::iterator TinySrpiteLayersController::begin()
{
	return spriteLayers.begin();
}

boost::container::vector<TinySpriteLayer>::iterator TinySrpiteLayersController::end()
{
	return spriteLayers.end();
}

TinySpriteLayer* TinySrpiteLayersController::operator[](int index)
{
	if (index < 0 || index >= spriteLayers.size())
	{
		return nullptr;
	}
	return &spriteLayers[index];
}

TinySpriteLayer* TinySrpiteLayersController::operator[](const char* name)
{
	for (int i = 0; i < spriteLayers.size(); i++)
	{
		if (strcmp(spriteLayers[i].GetName(), name) == 0)
		{
			return &spriteLayers[i];
		}
	}
	return nullptr;
}
