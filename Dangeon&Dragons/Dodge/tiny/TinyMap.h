#pragma once
#include "../Window.h"
#include "TileMap.h"

#include "../animator/AnimationController.h"

class TinyMap
{
protected:
	Window* window;
	std::unique_ptr<TileMap> tileMap;

	Coord pos;

	AnimationController animationController;

	std::vector<std::shared_ptr<IGameObject>> gameObjects;
	std::vector<std::shared_ptr<IGameObject>> gameClasses;

	void MoveCollison(std::shared_ptr<ICollision> collision, Coord* pos = nullptr);

	virtual void OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject) = 0;

	void Initialize();
public:
	TinyMap(Window* window, std::unique_ptr<TileMap>, Coord pos = Coord());
	virtual ~TinyMap() = default;

	virtual void Update() = 0;

	std::vector<std::weak_ptr<IGameObject>> GetClassesByType(const char* type);
	std::vector<std::weak_ptr<IGameObject>> GetClassesByName(const char* name);
	std::weak_ptr<IGameObject> GetClassByName(const char* name);

	Window* GetWindow();
	TileMap* GetTileMap();
};