#include "TilesetsController.h"

TilesetsController::TilesetsController()
{
	tilesets = std::vector<std::shared_ptr<Tileset>>();
}

TilesetsController::TilesetsController(std::vector<std::shared_ptr<Tileset>> tilesets)
{
	this->tilesets = tilesets;
}

TilesetsController::TilesetsController(tinyxml2::XMLElement* element, std::string path)
{
	LoadTilesets(element, tilesets, path);
}

TilesetsController::~TilesetsController()
{
}

void TilesetsController::LoadTilesets(tinyxml2::XMLElement* element, std::vector<std::shared_ptr<Tileset>>& tilesets, std::string path)
{
	for (tinyxml2::XMLElement* tileset = element->FirstChildElement("tileset");
		tileset != nullptr;
		tileset = tileset->NextSiblingElement("tileset")
		) {

		std::string source = tileset->Attribute("source");
		if (!source.empty()) {
			std::string pth = fs::path(path).parent_path().string() + "/";
			tilesets.push_back(
				LoadTileset(
					tileset->IntAttribute("firstgid"),
					(pth + source).c_str()
				)
			);
			std::cout << source << " OK" << std::endl;
			continue;
		}
		std::cout << source << " ERROR!" << std::endl;
	}
}

std::shared_ptr<Tileset> TilesetsController::LoadTileset(int firstgId, std::string path)
{
    tinyxml2::XMLDocument doc;
    if (TinyXml::ReadDoc(doc, path) != tinyxml2::XML_SUCCESS) {
        return nullptr;
    } 

    tinyxml2::XMLElement* tilesetElement = doc.FirstChildElement("tileset");
    std::string name = tilesetElement->Attribute("name");

    int tileWidth = tilesetElement->IntAttribute("tilewidth");
    int tileHeight = tilesetElement->IntAttribute("tileheight");

    int tileCount = tilesetElement->IntAttribute("tilecount");
    int columns = tilesetElement->IntAttribute("columns");

    TilesetPropertiesController tilesetProperties = TilesetPropertiesController();

    //Load image
    tinyxml2::XMLElement* image = tilesetElement->FirstChildElement("image");
    std::string source = image->Attribute("source");

    int width = image->IntAttribute("width");
    int height = image->IntAttribute("height");

    if (source.length() == 0) {
        return nullptr;
    }

    source = TinyXml::GetPathToTileSource(source);
    Image image_obj = ImagesController::LoadImg(source.c_str(), name);
    if (image_obj.GetImage() <= 0) {
        return nullptr;
    }

    std::unordered_map<int, std::shared_ptr<Tile>> tiles;

    //Tiles
    for (tinyxml2::XMLElement* tileset = tilesetElement->FirstChildElement("tile");
        tileset != nullptr;
        tileset = tileset->NextSiblingElement("tile")
        ) {

        int tile_id = tileset->IntAttribute("id");

        //Properties
		tinyxml2::XMLElement* properties = tileset->FirstChildElement("properties");
		if (properties != nullptr) {
			tilesetProperties = TilesetPropertiesController(properties);
		}

        //animation
        tinyxml2::XMLElement* animation = tileset->FirstChildElement("animation");

        std::shared_ptr<Animation> animation_obj = nullptr;
        if (animation != nullptr) {
            animation_obj = std::make_shared<Animation>(animation);
        }
        //Object group
        tinyxml2::XMLElement* objectGroup = tileset->FirstChildElement("objectgroup");

        if (objectGroup == nullptr) {
            std::unique_ptr<Tile> tile = std::make_unique<Tile>(
                tile_id,
                nullptr,
                animation_obj
            );

            tile->SetTilesetProperties(tilesetProperties);

            tiles[tile_id] = std::move(tile);
            continue;
        }

        //Object
        tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");

        if (object == nullptr) {
            std::unique_ptr<Tile> tile = std::make_unique<Tile>(
                tile_id,
                nullptr,
                animation_obj
            );

			tile->SetTilesetProperties(tilesetProperties);
            tiles[tile_id] = std::move(tile);
            continue;
        }

        int object_id = object->IntAttribute("id");
        std::string object_name = "";
        std::string object_type = "";

        {
            const char* temp_name = object->Attribute("name");
            const char* temp_type = object->Attribute("type");

            if (temp_name != nullptr) {
				object_name = temp_name;
			}
			if (temp_type != nullptr) {
				object_type = temp_type;
			}
        }

        Coord object_pos = {
            object->DoubleAttribute("x"),
            object->DoubleAttribute("y")
        };

        Size object_size = {
            object->DoubleAttribute("width"),
            object->DoubleAttribute("height")
        };

        tinyxml2::XMLElement* polygon = object->FirstChildElement("polygon");

        if (polygon == nullptr) {
            std::unique_ptr<Tile> tile = std::make_unique<Tile>(
                tile_id,
                std::make_shared<BoxCollision>(
                    object_pos,
                    object_size,
                    object_id,
                    object_name,
                    object_type
                ),
                animation_obj
            );

			tile->SetTilesetProperties(tilesetProperties);

            tiles[tile_id] = std::move(tile);
            continue;
        }

        std::unique_ptr<Tile> tile = std::make_unique<Tile>(
            tile_id,
            std::make_shared<PoligonCollision>(
                TinyXml::ParsePolygon(polygon->Attribute("points"), object_pos),
                object_id,
                object_name,
                object_type
            ),
            animation_obj
        );

        tile->SetTilesetProperties(tilesetProperties);

        tiles[tile_id] = std::move(tile);
    }

    return std::make_shared<Tileset>(
        firstgId, tileWidth, tileHeight, width, height,
        tileCount, columns, name, source.c_str(), 
        image_obj, tiles, tilesetProperties
    );
}

int TilesetsController::GetSize()
{
	return tilesets.size();
}

std::weak_ptr<Tileset> TilesetsController::GetTilesetByTileId(int tileId)
{
    for (std::shared_ptr<Tileset>& tileset : tilesets) {
		if (tileset->IsContains(tileId)) {
			return tileset;
		}
	}
	return std::make_shared<Tileset>();
}

std::weak_ptr<Tileset> TilesetsController::operator[](int index)
{
	for (int i = 0; i < tilesets.size(); i++)
	{
		if (i == index)
		{
			return tilesets[i];
		}
	}
	return std::make_shared<Tileset>();
}

std::weak_ptr<Tileset> TilesetsController::operator[](std::string name)
{
	for (int i = 0; i < tilesets.size(); i++)
	{
		if (tilesets[i]->GetName() == name)
		{
			return tilesets[i];
		}
	}
	return std::make_shared<Tileset>();
}
