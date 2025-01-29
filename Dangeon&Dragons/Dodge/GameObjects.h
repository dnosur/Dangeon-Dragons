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

<<<<<<< Updated upstream
	static IGameObject* GetByTitle(const char* title);
	template <typename T>
	static T* GetDynamicByTitle(const char* title);

	static IGameObject* GetByTitle(const char* title, Layer layer);
	template <typename T>
	static T* GetDynamicByTitle(const char* title, Layer layer);
=======
	static std::weak_ptr<IGameObject> GetByTitle(std::string title);
	template <typename T>
	static std::weak_ptr<T> GetDynamicByTitle(std::string title);

	static std::weak_ptr<IGameObject> GetByTitle(std::string title, Layer layer);
	template <typename T>
	static std::weak_ptr<T>  GetDynamicByTitle(std::string title, Layer layer);
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
inline T* GameObjects::GetDynamicByTitle(const char* title)
{
	return dynamic_cast<T*>(GetByTitle(title));
}

template<typename T>
inline T* GameObjects::GetDynamicByTitle(const char* title, Layer layer)
{
	return dynamic_cast<T*>(GetByTitle(title, layer));
=======
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
>>>>>>> Stashed changes
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
