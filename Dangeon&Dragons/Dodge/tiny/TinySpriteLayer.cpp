#include "TinySpriteLayer.h"

TinySpriteLayer::TinySpriteLayer()
{
	id = -1;
	name = nullptr;
	size = Size(0, 0);

	offset = Coord(0, 0);
}

TinySpriteLayer::TinySpriteLayer(
	int id, 
	std::string name, 
	Size size, 
	int** tileIds, 
	Coord offset
): id(id), name(name), size(size), offset(offset){
}

TinySpriteLayer::TinySpriteLayer(tinyxml2::XMLElement* element)
{
	if (element == nullptr) {
		id = -1;
		size = Size(0, 0);
		return;
	}

	id = element->IntAttribute("id");

	std::string name = element->Attribute("name");
	this->name = name;

	size = Size(element->DoubleAttribute("width"), element->DoubleAttribute("height"));
	offset = Coord(element->DoubleAttribute("offsetx"), element->DoubleAttribute("offsety"));

	GetSprites(element, chunks);
}

TinySpriteLayer::~TinySpriteLayer()
{
}

bool TinySpriteLayer::Undefined()
{
	return id < 0 && name.empty() && size == Size(0, 0) && !chunks.size();
}

void TinySpriteLayer::GetSprites(
	tinyxml2::XMLElement* element, 
	std::vector<std::shared_ptr<TinyChunk>>& chunks
)
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

	for (tinyxml2::XMLElement* child = dataLayer->FirstChildElement("chunk");
		child != nullptr;
		child = child->NextSiblingElement("chunk")
		) {
		chunks.push_back(std::make_shared<TinyChunk>(child));

		std::cout << "chunk " << child->IntAttribute("x") << " " << child->IntAttribute("y") << std::endl;
		for (int i = 0; i < chunks[chunks.size() - 1]->size.height; i++) {
			for (int j = 0; j < chunks[chunks.size() - 1]->size.width; j++) {
				std::cout << chunks[chunks.size() - 1]->tileIds[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	if (!chunks.empty()) {
		return;
	}

	TinyChunk chunk;
	chunk.size = Size(width, height);

	std::string data = dataLayer->GetText();
	LoadChunkIds(data, chunk.tileIds, Size(width, height));

	for (int i = 0; i < chunk.size.height; i++) {
		for (int j = 0; j < chunk.size.width; j++) {
			std::cout << chunk.tileIds[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void TinySpriteLayer::LoadChunkIds(std::string data, int**& ids, Size size)
{
	ids = new int* [size.height];

	std::istringstream stream(data);
	std::string line;

	int i = 0;
	while (std::getline(stream, line, '\n')) {
		if (!line.length()) {
			continue;
		}

		std::istringstream lineStream(line);
		std::string point;

		ids[i] = new int[size.width];
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

std::string_view TinySpriteLayer::GetName()
{
	return name;
}

Size TinySpriteLayer::GetSize()
{
	return size;
}

int TinySpriteLayer::GetChunksCount()
{
	return chunks.size();
}

std::weak_ptr<TinyChunk> TinySpriteLayer::operator[](int index)
{
	if (index < 0 || index >= chunks.size()) {
		return std::make_shared<TinyChunk>();
	}
	return chunks[index];
}
