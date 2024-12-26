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

	Layer layer;

	bool kinematic;

	boost::container::small_vector<IGameObject*, 32> gameObjects;

	bool ExistGameObject(IGameObject* gameObject);
public:
	BoxCollision(Coord point,Size size, int root_id, char* root_title = nullptr, char* type = nullptr);
	~BoxCollision();

	int GetRootId();

	char* GetRootTitle();
	char* GetType();

	BoxCollision* Clone() const override;

	boost::container::vector<Coord> GetPoints();
	void SetPoints(boost::container::vector<Coord> points);

	Size GetSize();
	void SetSize(Size size);

	Layer GetLayer();
	void SetLayer(Layer layer);

	bool IsKinematic();
	void SetKinematic(bool kinematic);

	bool IsCollisionEnter(IGameObject* gameObject);
	bool IsCollisionStay(IGameObject* gameObject);
	bool IsCollisionExit(IGameObject* gameObject);

	bool IsCollisionEnter(Coord point, Size size);

	bool IsExist(IGameObject* gameObject);

	bool operator==(const BoxCollision& other) const;
	bool operator!=(const BoxCollision& other) const;
	BoxCollision& operator=(const BoxCollision& other);
};

