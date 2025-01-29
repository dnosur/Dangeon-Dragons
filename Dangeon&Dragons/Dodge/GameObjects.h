#pragma once
#include <memory>
#include <vector>
#include "IGameObject.h"

__interface IGameObject;
class Pawn;
enum Layer;

static class GameObjects
{
	static std::vector<std::shared_ptr<IGameObject>> gameObjects;
	static std::vector<std::shared_ptr<class Pawn>> pawns;
public:
	static void Add(IGameObject* gameObject);
	static void Add(class Pawn* pawn);

	static void Add(std::shared_ptr<IGameObject> gameObject);
	static void Add(std::shared_ptr<class Pawn> pawn);

	static void Add(std::vector<IGameObject*>* gameObjects);
	static void Add(std::vector<std::weak_ptr<IGameObject>>* gameObjects);

	static std::weak_ptr<IGameObject> GetByTitle(std::string title);
	template <typename T>
	static std::weak_ptr<T> GetDynamicByTitle(std::string title);

	static std::weak_ptr<IGameObject> GetByTitle(std::string title, Layer layer);
	template <typename T>
	static std::weak_ptr<T>  GetDynamicByTitle(std::string title, Layer layer);

	static std::vector<std::shared_ptr<IGameObject>>* GetAll();
	static std::vector<std::shared_ptr<IGameObject>>* GetAll(Layer layer);

	static std::vector<std::shared_ptr<class Pawn>>* GetAllPawns();
	static std::vector<std::shared_ptr<class Pawn>>* GetAllPawns(Layer layer);

	template <typename T>
	static std::vector<std::shared_ptr <T>>* GetAllDynamic();
	template <typename T>
	static std::vector<std::shared_ptr <T>>* GetAllDynamic(Layer layer);

	static void Clear();

	template <typename T>
	bool Exists(T* gameObject);
};

template<typename T>
inline std::weak_ptr<T> GameObjects::GetDynamicByTitle(std::string title)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetTitle() == title)
		{
			if (auto casted = std::dynamic_pointer_cast<T>(gameObjects[i])) {
				return casted;
			}
		}
	}
	return std::shared_ptr<T>(nullptr);
}

template<typename T>
inline std::weak_ptr<T> GameObjects::GetDynamicByTitle(std::string title, Layer layer)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetTitle() == title &&
			gameObjects[i]->GetLayer() == layer
			)
		{
			if (auto casted = std::dynamic_pointer_cast<T>(gameObjects[i])) {
				return casted;
			}
		}
	}
	return std::shared_ptr<T>(nullptr);
}

template<typename T>
inline std::vector<std::shared_ptr <T>>* GameObjects::GetAllDynamic()
{
	std::vector<std::shared_ptr <T>>* temp = new std::vector<std::shared_ptr <T>>();
	for (IGameObject*& gameObject : gameObjects)
	{
		auto casted = std::dynamic_pointer_cast<T>(gameObject);
		if (casted)
		{
			temp->push_back(casted);
		}
	}
	return temp;
}

template<typename T>
inline std::vector<std::shared_ptr <T>>* GameObjects::GetAllDynamic(Layer layer)
{
	std::vector<std::shared_ptr <T>>* temp = new std::vector<std::shared_ptr <T>>();
	for (IGameObject* gameObject : GetAll(layer))
	{
		auto casted = std::dynamic_pointer_cast<T>(gameObject);
		if (casted)
		{
			temp->push_back(casted);
		}
	}
	return temp;
}

template<typename T>
inline bool GameObjects::Exists(T* gameObject)
{
	return false;
}