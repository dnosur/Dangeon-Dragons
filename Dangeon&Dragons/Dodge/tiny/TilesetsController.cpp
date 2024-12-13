#include "TilesetsController.h"

TilesetsController::TilesetsController()
{
	tilesets = std::vector<Tileset*>();
}

TilesetsController::TilesetsController(std::vector<Tileset*> tilesets)
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

void TilesetsController::LoadTilesets(tinyxml2::XMLElement* element, std::vector<Tileset*>& tilesets, std::string path)
{
	for (tinyxml2::XMLElement* tileset = element->FirstChildElement("tileset");
		tileset != nullptr;
		tileset = tileset->NextSiblingElement("tileset")
		) {

		const char* source = tileset->Attribute("source");
		if (source) {
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

Tileset* TilesetsController::LoadTileset(int firstgId, const char* path)
{
    tinyxml2::XMLDocument doc;
    if (TinyXml::ReadDoc(doc, path) != tinyxml2::XML_SUCCESS) {
        return nullptr;
    } 

    tinyxml2::XMLElement* tilesetElement = doc.FirstChildElement("tileset");
    const char* name = tilesetElement->Attribute("name");

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
    if (image_obj.image <= 0) {
        return nullptr;
    }

    std::vector<Tile> tiles;

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

        Animation* animation_obj = nullptr;
        if (animation != nullptr) {
            animation_obj = new Animation(animation);
        }
        //Object group
        tinyxml2::XMLElement* objectGroup = tileset->FirstChildElement("objectgroup");

        if (objectGroup == nullptr) {
            Tile tile = Tile(
                tile_id,
                nullptr,
                animation_obj
            );

            tile.SetTilesetProperties(tilesetProperties);

            tiles.push_back(tile);
            continue;
        }

        //Object
        tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");

        if (object == nullptr) {
            Tile tile = Tile(
                tile_id,
                nullptr,
                animation_obj
            );

			tile.SetTilesetProperties(tilesetProperties);
            tiles.push_back(tile);
            continue;
        }

        int object_id = object->IntAttribute("id");
        const char* object_name = object->Attribute("name");
        const char* object_type = object->Attribute("type");

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
            Tile tile = Tile(
                tile_id,
                new BoxCollision(
                    object_pos,
                    object_size,
                    object_id,
                    (char*)object_name,
                    (char*)object_type
                ),
                animation_obj
            );

			tile.SetTilesetProperties(tilesetProperties);

            tiles.push_back(
				tile
            );
            continue;
        }

        Tile tile = Tile(
            tile_id,
            new PoligonCollision(
                TinyXml::ParsePolygon(polygon->Attribute("points"), object_pos),
                object_id,
                (char*)object_name,
                (char*)object_type
            ),
            animation_obj
        );

        tile.SetTilesetProperties(tilesetProperties);

        tiles.push_back(
            tile
        );
    }

    return new Tileset(
        firstgId, tileWidth, tileHeight, width, height,
        tileCount, columns, name, source.c_str(), 
        image_obj, tiles, tilesetProperties
    );
}

int TilesetsController::GetSize()
{
	return tilesets.size();
}

Tileset* TilesetsController::GetTilesetByTileId(int tileId)
{
    for (Tileset* tileset : tilesets) {
		if (tileset->IsContains(tileId)) {
			return tileset;
		}
	}
	return nullptr;
}

Tileset* TilesetsController::operator[](int index)
{
	for (int i = 0; i < tilesets.size(); i++)
	{
		if (i == index)
		{
			return tilesets[i];
		}
	}
	return nullptr;
}

Tileset* TilesetsController::operator[](const char* name)
{
	for (int i = 0; i < tilesets.size(); i++)
	{
		if (strcmp(tilesets[i]->GetName(), name) == 0)
		{
			return tilesets[i];
		}
	}
	return nullptr;
}
