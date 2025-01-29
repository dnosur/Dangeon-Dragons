#include "TilesetPropertiesController.h"
#include "PropertiesFactory.h"

TilesetPropertiesController::TilesetPropertiesController()
{
}

TilesetPropertiesController::TilesetPropertiesController(std::vector<Propertie*> tilesetProperties)
	: tilesetProperties(tilesetProperties)
{
	this->tilesetProperties = tilesetProperties;
}

TilesetPropertiesController::TilesetPropertiesController(tinyxml2::XMLElement* tileset)
{
	readTilesetProperties(tileset, tilesetProperties);
}

TilesetPropertiesController::~TilesetPropertiesController()
{
}

std::vector<Propertie*>::iterator TilesetPropertiesController::begin()
{
	return tilesetProperties.begin();
}

std::vector<Propertie*>::iterator TilesetPropertiesController::end()
{
	return tilesetProperties.end();
}

int TilesetPropertiesController::GetSize()
{
	return tilesetProperties.size();
}

Propertie* TilesetPropertiesController::operator[](std::string name)
{
	for (Propertie*& propertie : tilesetProperties) {
		if (propertie->getTitle() == name) {
			return propertie;
		}
	}
	return nullptr;
}

Propertie* TilesetPropertiesController::operator[](int index)
{
	return nullptr;
}

void TilesetPropertiesController::readTilesetProperties(tinyxml2::XMLElement* tileset, std::vector<Propertie*>& tilesetProperties)
{
	//tinyxml2::XMLElement* properties = getTilesetProperties(tileset);

	for (
		tinyxml2::XMLElement* child = tileset->FirstChildElement("property");
		child != nullptr;
		child = child->NextSiblingElement("property")
		) {
		tilesetProperties.push_back(
			PropertiesFactory::createPropertie(
				(char*)child->Attribute("name"),
				(char*)child->Attribute("value"),
				(char*)child->Attribute("type")
			)
		);
	}
}

tinyxml2::XMLElement* TilesetPropertiesController::getTilesetProperties(tinyxml2::XMLElement* tileset)
{
	for (
		tinyxml2::XMLElement* child = tileset->FirstChildElement();
		child != nullptr;
		child = child->NextSiblingElement()
		) {
		if (strcmp(child->Attribute("type"), "TilesetProperties")) {
			break;
		}

		return child->FirstChildElement("properties");
	}
	return nullptr;
}
