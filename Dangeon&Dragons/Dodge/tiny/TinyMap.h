#pragma once
#include "../Window.h"
#include "TileMap.h"

#include "../animator/AnimationController.h"

class TinyMap
{
protected:
	Window* window;
	TileMap* tileMap;

	Coord pos;

	AnimationController animationController;

	std::vector<IGameObject*> gameObjects;
	std::vector<IGameObject*> gameClasses;

	void MoveCollison(ICollision* collision, Coord* pos = nullptr);

	virtual void OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject) = 0;

	void Initialize();
public:
	TinyMap(Window* window, TileMap* tileMap, Coord pos = Coord());
	virtual ~TinyMap() = default;

	virtual void Update() = 0;

<<<<<<< Updated upstream
	std::vector<IGameObject*> GetClassesByType(const char* type);
	std::vector<IGameObject*> GetClassesByName(const char* name);
	IGameObject* GetClassByName(const char* name);
=======
	std::vector<std::weak_ptr<IGameObject>> GetClassesByType(std::string type);
	std::vector<std::weak_ptr<IGameObject>> GetClassesByName(std::string name);
	std::weak_ptr<IGameObject> GetClassByName(std::string name);
>>>>>>> Stashed changes

	Window* GetWindow();
	TileMap* GetTileMap();
};