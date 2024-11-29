#pragma once
#include "../IGameObject.h"

__interface IGameObject;

__interface ICollision
{
	int GetRootId();

	char* GetRootTitle();
	char* GetType();

	std::vector<Coord> GetPoints();
	void SetPoints(std::vector<Coord> points);

	virtual ICollision* Clone() const = 0;

	bool IsExist(IGameObject* gameObject);

	bool IsCollisionEnter(IGameObject* gameObject);
	bool IsCollisionStay(IGameObject* gameObject);
	bool IsCollisionExit(IGameObject* gameObject);
};