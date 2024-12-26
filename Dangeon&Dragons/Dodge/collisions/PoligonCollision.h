#pragma once
#include "ICollision.h"

class PoligonCollision 
	: public ICollision
{
	int root_id;
	char* root_title;
	char* type;

	Layer layer;

	bool kinematic;

	boost::container::vector<Coord> points;
	boost::container::small_vector<IGameObject*, 32> gameObjects;

	bool ExistGameObject(IGameObject* gameObject);
public:
	PoligonCollision();
	PoligonCollision(boost::container::vector<Coord>, int root_id, char* root_title = nullptr, char* type = nullptr);

	static bool IsPointInPolygon(const Coord& point, const 	boost::container::vector<Coord>& polygon);

	int GetRootId();

	char* GetRootTitle();
	char* GetType();

	boost::container::vector<Coord> GetPoints();
	void SetPoints(boost::container::vector<Coord> points);

	PoligonCollision* Clone() const override;

	Layer GetLayer();
	void SetLayer(Layer layer);

	bool IsKinematic();
	void SetKinematic(bool kinematic);

	bool IsCollisionEnter(IGameObject* gameObject);
	bool IsCollisionStay(IGameObject* gameObject);
	bool IsCollisionExit(IGameObject* gameObject);

	bool IsCollisionEnter(Coord point, Size size);

	bool IsExist(IGameObject* gameObject);

	bool operator==(const PoligonCollision& other) const;
	bool operator!=(const PoligonCollision& other) const;
	PoligonCollision& operator=(const PoligonCollision& other);
};

