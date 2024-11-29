#include "TinySpriteLayer.h"

TinySpriteLayer::TinySpriteLayer()
{
	id = -1;
	name = nullptr;
	size = Size(0, 0);
	tileIds = nullptr;

	offset = Coord(0, 0);
}

TinySpriteLayer::TinySpriteLayer(
	int id, 
	const char* name, 
	Size size, 
	int** tileIds, 
	Coord offset
){
	this->id = id;
	copyStr(name, this->name);
	this->size = size;
	this->tileIds = tileIds;
}

TinySpriteLayer::TinySpriteLayer(tinyxml2::XMLElement* element)
{
	if (element == nullptr) {
		id = -1;
		name = nullptr;
		size = Size(0, 0);
		tileIds = nullptr;
		return;
	}

	id = element->IntAttribute("id");

	const char* name = element->Attribute("name");
	copyStr(name, this->name);

	size = Size(element->DoubleAttribute("width"), element->DoubleAttribute("height"));
	offset = Coord(element->DoubleAttribute("offsetx"), element->DoubleAttribute("offsety"));

	GetSprites(element, tileIds);

	for (int i = 0; i < size.height; i++) {
		for (int j = 0; j < size.width; j++) {
			std::cout << tileIds[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

TinySpriteLayer::~TinySpriteLayer()
{
}

bool TinySpriteLayer::Undefined()
{
	return id < 0 && name == nullptr && size == Size(0, 0) && tileIds == nullptr;
}

void TinySpriteLayer::GetSprites(tinyxml2::XMLElement* element, int**& ids)
{
	int height = element->IntAttribute("height");
	int width = element->IntAttribute("width");

	if (!height || !width) {
		return;
	}

	tinyxml2::XMLElement* dataLayer = element->FirstChildElement("data");
	if (dataLayer == nullptr) {
		return;
	}

	std::string data = dataLayer->GetText();

	ids = new int*[height];

	std::istringstream stream(data);
	std::string line;

	int i = 0;
	while (std::getline(stream, line, '\n')) {
		if (!line.length()) {
			continue;
		}

		std::istringstream lineStream(line);
		std::string point;

		ids[i] = new int[width];
		int j = 0;
		while (std::getline(lineStream, point, ',')) {
			ids[i][j] = std::stoi(point);
			j++;
		}
		i++;
	}
}

int TinySpriteLayer::GetId()
{
	return id;
}

char* TinySpriteLayer::GetName()
{
	return name;
}

Size TinySpriteLayer::GetSize()
{
	return size;
}

int* TinySpriteLayer::operator[](int index)
{
	if (index < 0 || index >= size.height) {
		return nullptr;
	}
	return tileIds[index];
}
