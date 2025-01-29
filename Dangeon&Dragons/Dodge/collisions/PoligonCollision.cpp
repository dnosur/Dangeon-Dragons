#include "PoligonCollision.h"
#include "../functions.h"

PoligonCollision::PoligonCollision()
{
	root_id = -1;
	root_title = nullptr;
	type = nullptr;

	kinematic = false;

	SetLayer(Layer::Undefined);
}

PoligonCollision::PoligonCollision(std::vector<Coord> points, int root_id, char* root_title, char* type)
{
	this->root_id = root_id;
	this->points = points;

	this->kinematic = false;

	SetLayer(Layer::Collision);

	CopyStr(root_title, this->root_title);
	CopyStr(type, this->type);
}

bool PoligonCollision::IsPointInPolygon(const Coord& point, const std::vector<Coord>& polygon)
{
	int intersections = 0;
	size_t numPoints = polygon.size();

	for (size_t i = 0; i < numPoints; i++) {
		Coord p1 = polygon[i];
		Coord p2 = polygon[(i + 1) % numPoints];

		if (((p1.Y > point.Y) != (p2.Y > point.Y)) &&
			(point.X < (p2.X - p1.X) * (point.Y - p1.Y) / (p2.Y - p1.Y) + p1.X)) {
			intersections++;
		}
	}

	return (intersections % 2) == 1;
}

int PoligonCollision::GetRootId()
{
	return root_id;
}

char* PoligonCollision::GetRootTitle()
{
	return root_title;
}

char* PoligonCollision::GetType()
{
	return type;
}

std::vector<Coord> PoligonCollision::GetPoints()
{
	return points;
}

void PoligonCollision::SetPoints(std::vector<Coord> points)
{
	if (this->points.size()) {
		this->points.clear();
	}

	this->points = points;
}

PoligonCollision* PoligonCollision::Clone() const
{
	return new PoligonCollision(*this);
}

Layer PoligonCollision::GetLayer()
{
	return layer;
}

void PoligonCollision::SetLayer(Layer layer)
{
	this->layer = layer;
}

bool PoligonCollision::IsKinematic()
{
	return kinematic;
}

void PoligonCollision::SetKinematic(bool kinematic)
{
	this->kinematic = kinematic;
}

bool PoligonCollision::IsCollisionEnter(IGameObject* gameObject)
{
	if (!gameObject || gameObject == nullptr) {
		return false;
	}

	std::shared_ptr<ICollision> gameObjectPtr = gameObject->GetCollision().lock();

	if (gameObjectPtr == nullptr) {
		return false;
	}

	if (gameObjectPtr.get() == this) {
		return true;
	}

	const std::vector<Coord>& polygonPoints = this->points;
	if (polygonPoints.size() < 3) {
		return false;
	}

	std::vector<Coord> otherPoints = gameObjectPtr->GetPoints();
	if (otherPoints.empty()) {
		return false;
	}

	bool res = false;

	for (Coord& p : otherPoints) {
		if (IsPointInPolygon(p, polygonPoints)) {
			res = true;
			break;
		}
	}

	if (!res) {
		return false;
	}

	if (IsExist(gameObject)) {
		return true;
	}

	gameObjects.push_back(gameObject);

	return true;
}

bool PoligonCollision::IsCollisionStay(IGameObject* gameObject)
{
	return IsExist(gameObject);
}

bool PoligonCollision::IsCollisionExit(IGameObject* gameObject)
{
	bool isExit = IsExist(gameObject) && !IsCollisionEnter(gameObject);

	if (isExit && !gameObjects.empty()) {
		gameObjects.erase(
			std::remove(
				gameObjects.begin(),
				gameObjects.end(),
				gameObject
			),
			gameObjects.end()
		);
	}

	return isExit;
}

bool PoligonCollision::IsCollisionEnter(Coord point, Size size)
{
	return false;
}

bool PoligonCollision::IsExist(IGameObject* gameObject)
{
	return ExistInVector<IGameObject*>(gameObjects, gameObject);
}

bool PoligonCollision::operator==(const PoligonCollision& other) const
{
	return !strcmp(root_title, other.root_title) &&
		!strcmp(type, other.type) &&
		points == other.points && 
		root_id == other.root_id;
}

bool PoligonCollision::operator!=(const PoligonCollision& other) const
{
	return !(*this == other);
}

PoligonCollision& PoligonCollision::operator=(const PoligonCollision& other)
{
	if (this != &other)
	{
		CopyStr(other.root_title, root_title);
		CopyStr(other.type, type);

		points = other.points;
		root_id = other.root_id;
	}
	return *this;
}
