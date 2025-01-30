#include "GameObjects.h"

#include "Layers.h"
#include "pawn/Pawn.h"

std::unordered_map<std::string, std::shared_ptr<IGameObject>> GameObjects::gameObjects;
std::unordered_map<std::string, std::shared_ptr<class Pawn>> GameObjects::pawns;

void GameObjects::Add(IGameObject* gameObject)
{
	std::shared_ptr <IGameObject> obj = std::shared_ptr <IGameObject>(gameObject);
	gameObjects[obj->GetTitleString()] = obj;

	if (std::shared_ptr <class Pawn> pawn = std::dynamic_pointer_cast<class Pawn>(obj)) {
		pawns[pawn->GetTitleString()] = pawn;
	}
}

void GameObjects::Add(class Pawn* pawn)
{
	std::shared_ptr <class Pawn> p = std::shared_ptr <class Pawn>(pawn);
	const std::string& title = p->GetTitleString();

	pawns[title] = p;
	gameObjects[title] = p;
}

void GameObjects::Add(std::shared_ptr<IGameObject> gameObject)
{
	gameObjects[gameObject->GetTitleString()] = gameObject;

	if (std::shared_ptr<class Pawn> pawn = std::dynamic_pointer_cast<class Pawn>(gameObject)) {
		pawns[pawn->GetTitleString()] = pawn;
	}
}

void GameObjects::Add(std::shared_ptr<class Pawn> gameObject)
{
	const std::string& title = gameObject->GetTitleString();

	pawns[title] = gameObject;
	gameObjects[title] = gameObject;
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
	for (std::weak_ptr<IGameObject>& gameObject : *gameObjects)
	{
		std::shared_ptr<IGameObject> gameObjectPtr = gameObject.lock();
		if (gameObject.expired() || gameObjectPtr == nullptr) {
			continue;
		}
		Add(gameObjectPtr);
	}
}

std::weak_ptr<IGameObject> GameObjects::GetByTitle(std::string_view title)
{
	auto it = gameObjects.find(std::string(title));
	if (it == gameObjects.end()) {
		return std::shared_ptr<IGameObject>(nullptr);
	}

	return it->second;
}

std::weak_ptr<IGameObject> GameObjects::GetByTitle(std::string_view title, Layer layer)
{
	for (const auto& pair : gameObjects)
	{
		const auto& obj = pair.second;
		if (obj && obj->GetTitle() == title && obj->GetLayer() == layer)
		{
			return obj;
		}
	}
	return {};
}

std::unordered_map<std::string, std::shared_ptr<IGameObject>>& GameObjects::GetAll()
{
	return gameObjects;
}

std::unordered_map<std::string, std::shared_ptr<IGameObject>>& GameObjects::GetAll(Layer layer)
{
	std::unordered_map<std::string, std::shared_ptr<IGameObject>> result;

	for (auto& pair : gameObjects)
	{
		if (pair.second->GetLayer() == layer)
		{
			result[pair.second->GetTitleString()] = pair.second;
		}
	}
	return result;
}

std::unordered_map<std::string, std::shared_ptr<class Pawn>>& GameObjects::GetAllPawns()
{
	return pawns;
}

std::unordered_map<std::string, std::shared_ptr<class Pawn>>& GameObjects::GetAllPawns(Layer layer)
{
	std::unordered_map<std::string, std::shared_ptr<class Pawn>> result;

	for (auto& pair : pawns)
	{
		if (pair.second->GetLayer() == layer)
		{
			result[pair.second->GetTitleString()] = pair.second;
		}
	}
	return result;
}

void GameObjects::Clear()
{
	gameObjects.clear();
	pawns.clear();
}
