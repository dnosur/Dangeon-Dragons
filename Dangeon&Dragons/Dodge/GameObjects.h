#pragma once
#include "IGameObject.h"

class Pawn;
enum Layer;

static class GameObjects
{
	static boost::container::vector<IGameObject*> gameObjects;
	static boost::container::vector<class Pawn*> pawns;
public:
	static void Add(IGameObject* gameObject);
	static void Add(class Pawn* pawn);

	static void Add(boost::container::vector<IGameObject*>* gameObjects);

	static IGameObject* GetByTitle(const char* title);
	template <typename T>
	static T* GetDynamicByTitle(const char* title);

	static IGameObject* GetByTitle(const char* title, Layer layer);
	template <typename T>
	static T* GetDynamicByTitle(const char* title, Layer layer);

	static boost::container::vector<IGameObject*>* GetAll();
	static boost::container::vector<IGameObject*>* GetAll(Layer layer);

	static boost::container::vector<class Pawn*>* GetAllPawns();
	static boost::container::vector<class Pawn*>* GetAllPawns(Layer layer);

	template <typename T>
	static boost::container::vector<T*>* GetAllDynamic();
	template <typename T>
	static boost::container::vector<T*>* GetAllDynamic(Layer layer);

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
inline boost::container::vector<T*>* GameObjects::GetAllDynamic()
{
	boost::container::vector<T*>* temp = new boost::container::vector<T*>;
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
inline boost::container::vector<T*>* GameObjects::GetAllDynamic(Layer layer)
{
	boost::container::vector<T*>* temp = new boost::container::vector<T*>;
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
