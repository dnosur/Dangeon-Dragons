#pragma once
#include "../IGameObject.h"

__interface IGameObject;

__interface ICollision
{
	int GetRootId();

	std::string_view GetRootTitle();
	std::string_view GetType();

	std::vector<Coord> GetPoints();
	void SetPoints(std::vector<Coord> points);

	virtual ICollision* Clone() const = 0;

	bool IsExist(IGameObject* gameObject);

	Layer GetLayer();
	void SetLayer(Layer layer);

	bool IsKinematic();
	void SetKinematic(bool kinematic);

	bool IsCollisionEnter(IGameObject* gameObject);
	bool IsCollisionStay(IGameObject* gameObject);
	bool IsCollisionExit(IGameObject* gameObject);

	bool IsCollisionEnter(Coord point, Size size);
};