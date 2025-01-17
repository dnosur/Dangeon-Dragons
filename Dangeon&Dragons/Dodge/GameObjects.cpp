#include "GameObjects.h"

#include "Layers.h"
#include "pawn/Pawn.h"

std::vector<std::shared_ptr <IGameObject>> GameObjects::gameObjects;
std::vector<std::shared_ptr <class Pawn>> GameObjects::pawns;

void GameObjects::Add(IGameObject* gameObject)
{
	std::shared_ptr <IGameObject> obj = std::shared_ptr <IGameObject>(gameObject);
	gameObjects.push_back(obj);

	if (std::shared_ptr <class Pawn> pawn = std::dynamic_pointer_cast<class Pawn>(obj)) {
		pawns.push_back(pawn);
	}
}

void GameObjects::Add(class Pawn* pawn)
{
	std::shared_ptr <class Pawn> p = std::shared_ptr <class Pawn>(pawn);
	pawns.push_back(p);
	gameObjects.push_back(p);
}

void GameObjects::Add(std::shared_ptr<IGameObject> gameObject)
{
	gameObjects.push_back(gameObject);

	if (std::shared_ptr<class Pawn> pawn = std::dynamic_pointer_cast<class Pawn>(gameObject)) {
		pawns.push_back(pawn);
	}
}

void GameObjects::Add(std::shared_ptr<class Pawn> gameObject)
{
	pawns.push_back(gameObject);
	gameObjects.push_back(gameObject);
}

void GameObjects::Add(std::vector<IGameObject*>* gameObjects)
{
	for (IGameObject*& gameObject : *gameObjects)
	{
		Add(gameObject);
	}
}

void GameObjects::Add(std::vector<std::weak_ptr<IGameObject>>* gameObjects)
{
	for (const std::weak_ptr<IGameObject>& gameObject : *gameObjects)
	{
		const std::shared_ptr<IGameObject> gameObjectPtr = gameObject.lock();
		if (gameObject.expired() || gameObjectPtr == nullptr) {
			continue;
		}
		Add(gameObjectPtr);
	}
}

std::weak_ptr<IGameObject> GameObjects::GetByTitle(const char* title)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!strcmp(gameObjects[i]->GetTitle(), title))
		{
			return gameObjects[i];
		}
	}

	return std::shared_ptr<IGameObject>(nullptr);
}

std::weak_ptr<IGameObject> GameObjects::GetByTitle(const char* title, Layer layer)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!strcmp(gameObjects[i]->GetTitle(), title) &&
			gameObjects[i]->GetLayer() == layer
			)
		{
			return gameObjects[i];
		}
	}
	return std::shared_ptr<IGameObject>(nullptr);
}

std::vector<std::shared_ptr <IGameObject>>* GameObjects::GetAll()
{
	return &gameObjects;
}

std::vector<std::shared_ptr <IGameObject>>* GameObjects::GetAll(Layer layer)
{
	std::vector<std::shared_ptr <IGameObject>>* result = new std::vector<std::shared_ptr <IGameObject>>{};

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetLayer() == layer)
		{
			result->push_back(gameObjects[i]);
		}
	}
	return result;
}

std::vector<std::shared_ptr<class Pawn>>* GameObjects::GetAllPawns()
{
	return &pawns;
}

std::vector<std::shared_ptr<class Pawn>>* GameObjects::GetAllPawns(Layer layer)
{
	std::vector<std::shared_ptr <class Pawn>>* result = new std::vector<std::shared_ptr <class Pawn>>{};

	for (int i = 0; i < pawns.size(); i++)
	{
		if (pawns[i]->GetLayer() == layer)
		{
			result->push_back(pawns[i]);
		}
	}
	return result;
}

void GameObjects::Clear()
{
	pawns[0].reset();
	gameObjects.clear();
	pawns.clear();
}
