#include "TinyXml.h"
#include "TileMap.h"

const char* TinyXml::root_dir = "Content/";

std::string TinyXml::GetPathToTileSource(std::string path)
{
    std::filesystem::path fullPath = std::filesystem::absolute(path);
    std::filesystem::path fullSource = std::filesystem::path(root_dir) / path.substr(8);
    return root_dir + fullSource.string();
}

std::vector<Coord> TinyXml::ParsePolygon(std::string polygon, const Coord& offset)
{
    std::vector<Coord> coords;
    std::istringstream stream(polygon);
    std::string point;

    while (std::getline(stream, point, ' ')) {
        std::istringstream coordStream(point);
        std::string xStr, yStr;

        if (std::getline(coordStream, xStr, ',') && std::getline(coordStream, yStr)) {
            try {
                double x = std::stod(xStr) + offset.X;
                double y = std::stod(yStr) + offset.Y;
                coords.emplace_back(x, y);
            }
            catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid coordinate format in points attribute");
            }
        }
        else {
            throw std::runtime_error("Invalid points format");
        }
    }

    return coords;
}

tinyxml2::XMLError TinyXml::ReadDoc(tinyxml2::XMLDocument& doc, const char* path)
{
    if (doc.LoadFile(path) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load map file." << std::endl;
        return tinyxml2::XML_ERROR_FILE_READ_ERROR;
    }
    return tinyxml2::XML_SUCCESS;
}

std::unique_ptr<TileMap> TinyXml::LoadMap(const char* path, const char* title)
{
	tinyxml2::XMLDocument doc;
    if (TinyXml::ReadDoc(doc, path) != tinyxml2::XML_SUCCESS) {
        return std::make_unique<TileMap>();
    }

    //Map
    std::unique_ptr<TileMap> map = std::make_unique<TileMap>();

    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");
    map->size.width = mapElement->IntAttribute("width");
    map->size.height = mapElement->IntAttribute("height"); 

    copyStr(title, map->title);

    map->infinite = mapElement->BoolAttribute("infinite");

	map->nextLayerId = mapElement->IntAttribute("nextlayerid");
	map->nextObjectId = mapElement->IntAttribute("nextobjectid");

    copyStr(mapElement->Attribute("orientation"), map->orientation);
	copyStr(mapElement->Attribute("renderorder"), map->renderOreder);

	map->tileSize.height = mapElement->IntAttribute("tileheight");
	map->tileSize.width = mapElement->IntAttribute("tilewidth");

    std::cout << "[MapLoad]::TILESETS::LOAD" << std::endl;

    //Tilesets
    TilesetsController tilesetsController(mapElement, path);

    std::cout << "[MapLoad]::TILESETS::OK" << std::endl << std::endl;

    std::cout << "[MapLoad]::CLASSES::LOAD" << std::endl;
    //Classes
    TinyClassController objects;
    tinyxml2::XMLElement* classes = mapElement->FirstChildElement("group");

    std::cout << classes->Attribute("name") << std::endl;

    if (classes != nullptr) {
		objects = TinyClassController(classes);
    }

    std::cout << "[MapLoad]::CLASSES::OK" << std::endl << std::endl;

    std::cout << "[MapLoad]::SPRITES::LOAD" << std::endl;
    //Sprites
    TinySrpiteLayersController layersController;
	tinyxml2::XMLElement* sprites = classes->NextSiblingElement("group");

	if (sprites != nullptr) {
        layersController = TinySrpiteLayersController(sprites);
	}

    map->tilesetsController = tilesetsController;
    map->classesController = objects;
    map->spriteLayersController = layersController;

    return std::move(map);
}

