#include "GameObjects.h"

#include "IGameObject.h"
#include "Layers.h"
#include "pawn/Pawn.h"

std::vector<IGameObject*> GameObjects::gameObjects;
std::vector<class Pawn*> GameObjects::pawns;

void GameObjects::Add(IGameObject* gameObject)
{
	gameObjects.push_back(gameObject);

	if (class Pawn* pawn = dynamic_cast<class Pawn*>(gameObject))
	{
		pawns.push_back(pawn);
	}
}

void GameObjects::Add(class Pawn* pawn)
{
	pawns.push_back(pawn);
	gameObjects.push_back(pawn);
}

void GameObjects::Add(std::vector<IGameObject*>* gameObjects)
{
	for (IGameObject* gameObject : *gameObjects)
	{
		Add(gameObject);
	}
}

IGameObject* GameObjects::GetByTitle(const char* title)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!strcmp(gameObjects[i]->GetTitle(), title))
		{
			return gameObjects[i];
		}
	}
	return nullptr;
}

IGameObject* GameObjects::GetByTitle(const char* title, Layer layer)
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
	return nullptr;
}

std::vector<IGameObject*>* GameObjects::GetAll()
{
	return &gameObjects;
}

std::vector<IGameObject*>* GameObjects::GetAll(Layer layer)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetLayer() == layer)
		{
			return &gameObjects;
		}
	}
	return nullptr;
}

std::vector<class Pawn*>* GameObjects::GetAllPawns()
{
	return &pawns;
}

std::vector<class Pawn*>* GameObjects::GetAllPawns(Layer layer)
{
	for (int i = 0; i < pawns.size(); i++)
	{
		if (pawns[i]->GetLayer() == layer)
		{
			return &pawns;
		}
	}
	return nullptr;
}
