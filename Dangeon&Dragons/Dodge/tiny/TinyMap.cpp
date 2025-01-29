#include "TinyMap.h"
#include "../GameStatuses.h"
#include "../animator/VertexAnimation.h"

void TinyMap::MoveCollison(std::shared_ptr<ICollision> collision, Coord* pos)
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
			std::weak_ptr<TinyChunk> weakChunk = spriteLayer[chunk_id];
			std::shared_ptr<TinyChunk> chunk = weakChunk.lock();

			if (chunk == nullptr) {
				continue;
			}

			for (int i = 0; i < chunk->size.height; i++) {
				for (int j = 0; j < chunk->size.width; j++) {
					int tileId = chunk->tileIds[i][j];

					if (!tileId) {
						continue;
					}

					std::shared_ptr<Tileset> tileset = tileMap->tilesetsController.GetTilesetByTileId(tileId).lock();
					if (tileset == nullptr) {
						continue;
					}

					Tile* tile = tileset->GetTileById(tileId);

					std::shared_ptr<ICollision> collision = tile ? tile->GetCollision().lock() : nullptr;
					std::shared_ptr<Animation> tileAnimation = tile ? tile->GetAnimation().lock() : nullptr;

					std::shared_ptr<Rect> rect = nullptr;
					std::unique_ptr<VertexAnimation> animation = nullptr;

					{
						int ciclesCount = tile == nullptr
							? 0
							: tileAnimation != nullptr
							? tileAnimation->FrameCount()
							: 0;

						Coord vertex1, vertex2;
						Coord textureVertex1, textureVertex2;

						std::string random_str = GenerateRandomString(5);
						std::string obj_title = random_str.c_str();

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
								animation = std::make_unique<VertexAnimation>(
									obj_title,
									4,
									true,
									false,
									rect.get()
								);

								tileId = tileAnimation->operator[](k)->tileId;
								animation->AddFrame(tileAnimation->operator[](k)->duration, {
									textureVertex1,
									textureVertex2
									});

								tileId = k + 1 < ciclesCount
									? tileAnimation->operator[](k + 1)->tileId
									: tileId;
							}

							if (rect != nullptr) {
								animation->AddFrame(tileAnimation->operator[](k)->duration, {
									textureVertex1,
									textureVertex2
									});

								tileId = k + 1 < ciclesCount
									? tileAnimation->operator[](k + 1)->tileId
									: tileId;
								continue;
							}

							rect = std::make_shared<Rect>(
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
						animation->SetGameObject(rect.get());
						animationController.AddAnimation(std::move(animation));
					}

					Coord rectPos = rect->GetPos();
					MoveCollison(collision, &rectPos);

					if (std::shared_ptr<BoxCollision> boxCollision = std::dynamic_pointer_cast<BoxCollision>(collision)) {
						boxCollision->SetSize(boxCollision->GetSize() * Size(.7f, .7f));
						rect->SetCollision(std::make_unique<BoxCollision>(*boxCollision));
					}

					rect->GetMaterial().lock()->SetDiffuseMap(std::make_shared<Image>(tileset->GetImage()));

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

		for (std::weak_ptr<ICollision> item : classes) {
			std::shared_ptr<ICollision> collision = item.lock();
			if (collision == nullptr) {
				continue;
			}

			std::cout << "Collision: " << collision->GetRootTitle() << std::endl;

			MoveCollison(collision);
			std::ostringstream oss;
			oss << collision->GetRootId() << "_" << collision->GetType();

			std::shared_ptr<Rect> circle = std::make_shared<Rect>(
				oss.str(),
				*window,
				collision->GetPoints()[0],
				Size(35, 35),
				Color(1, 1, 1)
			);

			if (std::shared_ptr<BoxCollision> boxCollision = std::dynamic_pointer_cast<BoxCollision>(collision)) {
				circle->SetCollision(boxCollision);
			}

			//circle->SetCollision(collision);
			circle->HookOnCollisionEnter([](IGameObject* object, IGameObject* sender, GLFWwindow* window) {
				std::cout << object->GetTitle() << " collided with " << sender->GetTitle() << std::endl;
			});

			gameClasses.push_back(circle);
		}
	}
}

TinyMap::TinyMap(Window* window, std::unique_ptr<TileMap> tileMap, Coord pos)
{
	this->window = window;
	this->tileMap = std::move(tileMap);
	this->pos = pos;

	Initialize();
}

std::vector<std::weak_ptr<IGameObject>> TinyMap::GetClassesByType(std::string type)
{
	std::vector<std::weak_ptr<IGameObject>> result = std::vector<std::weak_ptr<IGameObject>>();

	for (std::shared_ptr<IGameObject>& object : gameClasses) {
		if (object->GetCollision().lock()->GetType() == type) {
			result.push_back(object);
		}
	}

	return result;
}

std::vector<std::weak_ptr<IGameObject>> TinyMap::GetClassesByName(std::string name)
{
	std::vector<std::weak_ptr<IGameObject>> classes;

	for (std::shared_ptr<IGameObject>& object : gameClasses) {
		if (object->GetCollision().lock()->GetRootTitle() == name) {
			classes.push_back(object);
		}
	}

	return classes;
}

std::weak_ptr<IGameObject> TinyMap::GetClassByName(std::string name)
{
	for (std::shared_ptr<IGameObject>& object : gameClasses) {
		if (object->GetCollision().lock()->GetRootTitle() == name) {
			return object;
		}
	}

	return std::weak_ptr<Rect>();
}

Window* TinyMap::GetWindow()
{
	return window;
}

TileMap* TinyMap::GetTileMap()
{
	return tileMap.get();
}
