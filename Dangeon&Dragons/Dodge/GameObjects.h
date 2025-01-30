#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include "IGameObject.h"

__interface IGameObject;
class Pawn;
enum Layer;

static class GameObjects
{
	static std::unordered_map<std::string, std::shared_ptr<IGameObject>> gameObjects;
	static std::unordered_map<std::string, std::shared_ptr<class Pawn>> pawns;
public:
	static void Add(IGameObject* gameObject);
	static void Add(class Pawn* pawn);

	static void Add(std::shared_ptr<IGameObject> gameObject);
	static void Add(std::shared_ptr<class Pawn> pawn);

	static void Add(std::vector<IGameObject*>* gameObjects);
	static void Add(std::vector<std::weak_ptr<IGameObject>>* gameObjects);

	static std::weak_ptr<IGameObject> GetByTitle(std::string_view title);
	template <typename T>
	static std::weak_ptr<T> GetDynamicByTitle(std::string_view title);

	static std::weak_ptr<IGameObject> GetByTitle(std::string_view title, Layer layer);
	template <typename T>
	static std::weak_ptr<T>  GetDynamicByTitle(std::string_view title, Layer layer);

	static std::unordered_map<std::string, std::shared_ptr<IGameObject>>& GetAll();
	static std::unordered_map<std::string, std::shared_ptr<IGameObject>>& GetAll(Layer layer);

	static std::unordered_map<std::string, std::shared_ptr<class Pawn>>& GetAllPawns();
	static std::unordered_map<std::string, std::shared_ptr<class Pawn>>& GetAllPawns(Layer layer);

	template <typename T>
	static std::unordered_map<std::string, std::shared_ptr<T>>& GetAllDynamic();
	template <typename T>
	static std::unordered_map<std::string, std::shared_ptr<T>>& GetAllDynamic(Layer layer);

	static void Clear();

	template <typename T>
	bool Exists(T* gameObject);
};

template<typename T>
inline std::weak_ptr<T> GameObjects::GetDynamicByTitle(std::string_view title)
{
	auto it = gameObjects.find(std::string(title));
	if (it != gameObjects.end()) {
		return std::shared_ptr<T>(nullptr);
	}

	return std::dynamic_pointer_cast<T>(it->second);
}

template<typename T>
inline std::weak_ptr<T> GameObjects::GetDynamicByTitle(std::string_view title, Layer layer)
{
	for (auto& pair : gameObjects)
	{
		if (pair.second->GetTitle() == title &&
			pair.second->GetLayer() == layer
			)
		{
			if (auto casted = std::dynamic_pointer_cast<T>(pair.second)) {
				return std::dynamic_pointer_cast<T>(pair.second);
			}
		}
	}
	return std::shared_ptr<T>(nullptr);
}

template<typename T>
inline std::unordered_map<std::string, std::shared_ptr<T>>& GameObjects::GetAllDynamic()
{
	std::unordered_map<std::string, std::shared_ptr<T>> temp;
	for (auto& pair : gameObjects)
	{
		if (auto casted = std::dynamic_pointer_cast<T>(pair))
		{
			temp->push_back(casted);
		}
	}
	return temp;
}

template<typename T>
inline std::unordered_map<std::string, std::shared_ptr<T>>& GameObjects::GetAllDynamic(Layer layer)
{
	std::unordered_map<std::string, std::shared_ptr<T>> temp;
	for (IGameObject* gameObject : GetAll(layer))
	{
		if(auto casted = std::dynamic_pointer_cast<T>(gameObject))
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