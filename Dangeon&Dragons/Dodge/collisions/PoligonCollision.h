#pragma once
#include "ICollision.h"

class PoligonCollision 
	: public ICollision
{
	int root_id;
	std::string root_title;
	std::string type;

	Layer layer;

	bool kinematic;

	std::vector<Coord> points;
	std::vector<IGameObject*> gameObjects;
public:
	PoligonCollision();
	PoligonCollision(std::vector<Coord> points, int root_id, std::string root_title = "empty", std::string type = "empty");

	static bool IsPointInPolygon(const Coord& point, const std::vector<Coord>& polygon);

	int GetRootId();

	std::string_view GetRootTitle();
	std::string_view GetType();

	std::vector<Coord> GetPoints();
	void SetPoints(std::vector<Coord> points);

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

