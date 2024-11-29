#include "TinyMap.h"
#include "../figures/Circle.h"
#include "../GameStatuses.h"

void TinyMap::MoveCollison(ICollision* collision, Coord* pos)
{
	if (collision == nullptr) {
		return;
	}

	if (pos == nullptr) {
		pos = new Coord(this->pos);
	}

	std::vector<Coord> points;

	for (Coord& coord : collision->GetPoints()) {
		coord += *pos;
		points.push_back(coord);
	}

	collision->SetPoints(points);
}

void TinyMap::Initialize()
{
	//Math Map Texture Position
	for (TinySpriteLayer& spriteLayer : tileMap->spriteLayersController) {
		const Size spriteLayerSize = spriteLayer.GetSize();

		std::cout << "Layer: " << spriteLayer.GetName() << std::endl;

		for (int i = 0; i < spriteLayerSize.height; i++) {
			for (int j = 0; j < spriteLayerSize.width; j++) {
				const int tileId = spriteLayer[i][j];

				if (!tileId) {
					continue;
				}

				Tileset* tileset = tileMap->tilesetsController.GetTilesetByTileId(tileId);

				Tile* tile = tileset->GetTileById(tileId);
				if (tile != nullptr && !strcmp(tileset->GetName(), "map")) {
					std::cout << 123;
				}
				if (gameObjects.size() == 795) {
					std::cout << 795;
				}

				ICollision* collision = (tile == nullptr ? nullptr : tile->GetCollision()->Clone());

				const int tileWidth = tileset->GetTileWidth();
				const int tileHeight = tileset->GetTileHeight();

				const int width = tileset->GetWidth();
				const int height = tileset->GetHeight();

				const int columns = tileset->GetColumns();

				int tileValue = tileId - tileset->GetFirstgId();

				int atlasX = tileValue % columns;
				int atlasY =  tileValue / columns;

				float tileU = (float)tileWidth / (float)width;
				float tileV = (float)tileHeight / (float)height;

				Coord vertex1(window->PixelToGLX(((j + 1) * tileWidth) + pos.X), window->PixelToGLY(((i + 1) * tileHeight) + pos.Y));
				Coord vertex2(window->PixelToGLX(((j * tileWidth)) + pos.X), window->PixelToGLY((i * tileHeight) + pos.Y));

				Coord textureVertex1(((float)atlasX + 1.0f) * tileU, 1.0f - ((float)(atlasY + 1) * (float)tileV));
				Coord textureVertex2((float)atlasX * (float)tileU, 1.0f - ((float)atlasY * tileV));

				Rect* rect = new Rect(
					std::to_string(spriteLayer.GetId()).c_str(),
					*window,
					vertex1,
					vertex2,
					textureVertex1,
					textureVertex2
				);

				Coord rectPos = rect->GetPos();
				MoveCollison(collision, &rectPos);

				if (BoxCollision* boxCollision = dynamic_cast<BoxCollision*>(collision)) {
					boxCollision->SetSize(boxCollision->GetSize() * Size(.7f, .7f));
				}

				rect->SetCollision(collision);
				rect->GetMaterial()->SetDiffuseMap(new Image(tileset->GetImage()));

				if (collision) {
					rect->HookOnCollisionEnter([](IGameObject* object, IGameObject* sender, GLFWwindow* window) {

					});
				}

				gameObjects.push_back(
					rect
				);
			}
		}
		std::cout << std::endl;
	}

	IGameObject* sample = gameObjects[788];

	//Classes
	for (TinyClass& classes : tileMap->classesController) {
		std::cout << "Class: " << classes.GetName() << std::endl;
		std::cout << "Size: " << classes.GetSize() << std::endl;

		for (ICollision* collision : classes) {
			std::cout << "Collision: " << collision->GetRootTitle() << std::endl;

			MoveCollison(collision);
			Rect* circle = new Rect(
				std::to_string(classes.GetId()).c_str(),
				*window,
				collision->GetPoints()[0],
				Size(35, 35),
				Color(1, 1, 1)
			);

			circle->SetCollision(collision);

			circle->HookOnCollisionEnter([](IGameObject* object, IGameObject* sender, GLFWwindow* window) {
				std::cout << object->GetTitle() << " collided with " << sender->GetTitle() << std::endl;
			});

			gameClasses.push_back(circle);
		}
	}
}

TinyMap::TinyMap(Window* window, TileMap* tileMap, Coord pos)
{
	this->window = window;
	this->tileMap = tileMap;
	this->pos = pos;

	Initialize();
}

std::vector<IGameObject*> TinyMap::GetClassesByType(const char* type)
{
	std::vector<IGameObject*> result = std::vector<IGameObject*>();

	for (IGameObject* object : gameClasses) {
		if (!strcmp(object->GetCollision()->GetType(), type)) {
			result.push_back(object);
		}
	}

	return result;
}

Window* TinyMap::GetWindow()
{
	return window;
}

TileMap* TinyMap::GetTileMap()
{
	return tileMap;
}
