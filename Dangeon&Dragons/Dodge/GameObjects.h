#pragma once
#include <vector>

__interface IGameObject;
class Pawn;
enum Layer;

static class GameObjects
{
	static std::vector<IGameObject*> gameObjects;
	static std::vector<class Pawn*> pawns;
public:
	static void Add(IGameObject* gameObject);
	static void Add(class Pawn* pawn);

	static void Add(std::vector<IGameObject*>* gameObjects);

	static IGameObject* GetByTitle(const char* title);
	template <typename T>
	static T* GetDynamicByTitle(const char* title);

	static IGameObject* GetByTitle(const char* title, Layer layer);
	template <typename T>
	static T* GetDynamicByTitle(const char* title, Layer layer);

	static std::vector<IGameObject*>* GetAll();
	static std::vector<IGameObject*>* GetAll(Layer layer);

	static std::vector<class Pawn*>* GetAllPawns();
	static std::vector<class Pawn*>* GetAllPawns(Layer layer);

	template <typename T>
	static std::vector<T*>* GetAllDynamic();
	template <typename T>
	static std::vector<T*>* GetAllDynamic(Layer layer);

	template <typename T>
	bool Exists(T* gameObject);
};

template<typename T>
inline T* GameObjects::GetDynamicByTitle(const char* title)
{
	return dynamic_cast<T*>(GetByTitle(title));
}

template<typename T>
inline T* GameObjects::GetDynamicByTitle(const char* title, Layer layer)
{
	return dynamic_cast<T*>(GetByTitle(title, layer));
}

template<typename T>
inline std::vector<T*>* GameObjects::GetAllDynamic()
{
	std::vector<T*>* temp = new std::vector<T*>;
	for (IGameObject* gameObject : gameObjects)
	{
		T* casted = dynamic_cast<T*>(gameObject);
		if (casted)
		{
			temp->push_back(casted);
		}
	}
	return temp;
}

template<typename T>
inline std::vector<T*>* GameObjects::GetAllDynamic(Layer layer)
{
	std::vector<T*>* temp = new std::vector<T*>;
	for (IGameObject* gameObject : GetAll(layer))
	{
		T* casted = dynamic_cast<T*>(gameObject);
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
