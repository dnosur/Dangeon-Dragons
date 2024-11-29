#pragma once
#include "ICollision.h"

class BoxCollision :
    public ICollision
{
	int root_id;
	char* root_title;
	char* type;

	Coord point;
	Size size;

	std::vector<IGameObject*> gameObjects;
public:
	BoxCollision(Coord point,Size size, int root_id, char* root_title = nullptr, char* type = nullptr);
	~BoxCollision();

	int GetRootId();

	char* GetRootTitle();
	char* GetType();

	BoxCollision* Clone() const override;

	std::vector<Coord> GetPoints();
	void SetPoints(std::vector<Coord> points);

	Size GetSize();
	void SetSize(Size size);

	bool IsCollisionEnter(IGameObject* gameObject);
	bool IsCollisionStay(IGameObject* gameObject);
	bool IsCollisionExit(IGameObject* gameObject);

	bool IsExist(IGameObject* gameObject);

	bool operator==(const BoxCollision& other) const;
	bool operator!=(const BoxCollision& other) const;
	BoxCollision& operator=(const BoxCollision& other);
};

