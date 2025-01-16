#include "TinyMap.h"
#include "../figures/Circle.h"
#include "../GameStatuses.h"
#include "../animator/VertexAnimation.h"

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

		for (int chunk_id = 0; chunk_id < spriteLayer.GetChunksCount(); chunk_id++) {
			TinyChunk* chunk = spriteLayer[chunk_id];

			for (int i = 0; i < chunk->size.height; i++) {
				for (int j = 0; j < chunk->size.width; j++) {
					int tileId = chunk->tileIds[i][j];

					if (!tileId) {
						continue;
					}

					Tileset* tileset = tileMap->tilesetsController.GetTilesetByTileId(tileId);

					Tile* tile = tileset->GetTileById(tileId);

					ICollision* collision = (
						tile == nullptr
						? nullptr
						: tile->GetCollision() != nullptr
						? tile->GetCollision()->Clone()
						: nullptr
						);

					Rect* rect = nullptr;
					VertexAnimation* animation = nullptr;

					{
						int ciclesCount = tile == nullptr
							? 0
							: tile->GetAnimation() != nullptr
							? tile->GetAnimation()->FrameCount()
							: 0;

						Coord vertex1, vertex2;
						Coord textureVertex1, textureVertex2;

						std::string random_str = generateRandomString(5);
						const char* obj_title = random_str.c_str();

						for (int k = 0; k < (ciclesCount ? ciclesCount : 1); k++) {

							const int tileWidth = tileset->GetTileWidth();
							const int tileHeight = tileset->GetTileHeight();

							const int width = tileset->GetWidth();
							const int height = tileset->GetHeight();

							const int columns = tileset->GetColumns();

							int tileValue = tileId > tileset->GetFirstgId()
								? tileId - tileset->GetFirstgId()
								: tileId;

							int atlasX = tileValue % columns;
							int atlasY = tileValue / columns;

							float tileU = (float)tileWidth / (float)width;
							float tileV = (float)tileHeight / (float)height;

							if (rect == nullptr) {
								const int chunk_j = j + chunk->coord.X;
								const int chunk_i = i + chunk->coord.Y;

								vertex1 = Coord(window->PixelToGLX(((chunk_j + 1) * tileWidth) + pos.X), window->PixelToGLY(((chunk_i + 1) * tileHeight) + pos.Y));
								vertex2 = Coord(window->PixelToGLX(((chunk_j * tileWidth)) + pos.X), window->PixelToGLY((chunk_i * tileHeight) + pos.Y));
							}

							textureVertex1 = Coord(((float)atlasX + 1.0f) * tileU, 1.0f - ((float)(atlasY + 1) * (float)tileV));
							textureVertex2 = Coord((float)atlasX * (float)tileU, 1.0f - ((float)atlasY * tileV));

							if (animation == nullptr && ciclesCount > 0) {
								animation = new VertexAnimation(
									obj_title,
									4,
									true,
									false,
									rect
								);

								tileId = tile->GetAnimation()->operator[](k)->tileId;
								animation->AddFrame(tile->GetAnimation()->operator[](k)->duration, {
									textureVertex1,
									textureVertex2
									});

								tileId = k + 1 < ciclesCount
									? tile->GetAnimation()->operator[](k + 1)->tileId
									: tileId;
							}

							if (rect != nullptr) {
								animation->AddFrame(tile->GetAnimation()->operator[](k)->duration, {
									textureVertex1,
									textureVertex2
									});

								tileId = k + 1 < ciclesCount
									? tile->GetAnimation()->operator[](k + 1)->tileId
									: tileId;
								continue;
							}

							rect = new Rect(
								obj_title,
								*window,
								vertex1,
								vertex2,
								textureVertex1,
								textureVertex2
							);
						}
					}

					if (animation != nullptr) {
						animation->SetGameObject(rect);
						animationController.AddAnimation(animation);
					}

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
		}

		std::cout << std::endl;
	}

	//Classes
	for (TinyClass& classes : tileMap->classesController) {
		std::cout << "Class: " << classes.GetName() << std::endl;
		std::cout << "Size: " << classes.GetSize() << std::endl;

		for (ICollision* collision : classes) {
			std::cout << "Collision: " << collision->GetRootTitle() << std::endl;

			MoveCollison(collision);
			std::string name = "";
			name += std::to_string(collision->GetRootId()) + "_" + collision->GetType();

			Rect* circle = new Rect(
				name.c_str(),
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

	for (IGameObject*& object : gameClasses) {
		if (!strcmp(object->GetCollision()->GetType(), type)) {
			result.push_back(object);
		}
	}

	return result;
}

std::vector<IGameObject*> TinyMap::GetClassesByName(const char* name)
{
	std::vector<IGameObject*> classes;

	for (IGameObject* object : gameClasses) {
		if (!strcmp(object->GetCollision()->GetRootTitle(), name)) {
			classes.push_back(object);
		}
	}

	return classes;
}

IGameObject* TinyMap::GetClassByName(const char* name)
{
	for (IGameObject* object : gameClasses) {
		if (!strcmp(object->GetCollision()->GetRootTitle(), name)) {
			return object;
		}
	}

	return nullptr;
}

Window* TinyMap::GetWindow()
{
	return window;
}

TileMap* TinyMap::GetTileMap()
{
	return tileMap;
}
