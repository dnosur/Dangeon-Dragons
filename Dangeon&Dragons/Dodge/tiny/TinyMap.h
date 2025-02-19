#pragma once
#include "../Window.h"
#include "TileMap.h"

#include "../animator/AnimationController.h"

class TinyMap
{
protected:
	Window* window;
	std::unique_ptr<TileMap> tileMap;

	Coord position;

	AnimationController animationController;

	std::vector<std::shared_ptr<IGameObject>> gameObjects;
	std::vector<std::shared_ptr<IGameObject>> gameClasses;

	void MoveCollison(std::shared_ptr<ICollision> collision, Coord* position = nullptr);

	virtual void OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject) = 0;

	void Initialize();
public:
	TinyMap(Window* window, std::unique_ptr<TileMap>, Coord position = Coord());
	virtual ~TinyMap() = default;

	virtual void Update() = 0;

	std::vector<std::weak_ptr<IGameObject>> GetClassesByType(std::string type);
	std::vector<std::weak_ptr<IGameObject>> GetClassesByName(std::string name);
	std::weak_ptr<IGameObject> GetClassByName(std::string name);

	const std::vector<std::shared_ptr<IGameObject>>& GetGameObjects();
	const std::vector<std::shared_ptr<IGameObject>>& GetGameClasses();

	void InitializeRender();

	Window* GetWindow();
	TileMap* GetTileMap();
};