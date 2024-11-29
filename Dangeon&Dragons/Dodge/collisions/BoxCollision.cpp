#include "BoxCollision.h"

BoxCollision::BoxCollision(Coord point, Size size, int root_id, char* root_title, char* type)
{
	this->point = point;
	this->size = size;

	this->root_id = root_id;

    copyStr(root_title, this->root_title);
    copyStr(type, this->type);
}

BoxCollision::~BoxCollision()
{
}

int BoxCollision::GetRootId()
{
	return root_id;
}

char* BoxCollision::GetRootTitle()
{
	return root_title;
}

char* BoxCollision::GetType()
{
	return type;
}

BoxCollision* BoxCollision::Clone() const
{
    return new BoxCollision(*this);
}

std::vector<Coord> BoxCollision::GetPoints()
{
	return { point };
}

void BoxCollision::SetPoints(std::vector<Coord> points)
{
	point = points[0];
}

Size BoxCollision::GetSize()
{
	return size;
}

void BoxCollision::SetSize(Size size)
{
    this->size = size;
}

bool BoxCollision::IsCollisionEnter(IGameObject* gameObject)
{
    if (!gameObject || gameObject == nullptr) {
        return false;
    }

    ICollision* otherCollision = gameObject->GetCollision();
    if (otherCollision == nullptr || otherCollision == this) {
        return false;
    }

    float xMin1 = point.X;
    float yMin1 = point.Y;
    float xMax1 = point.X + size.width;
    float yMax1 = point.Y + size.height;

    auto* otherBoxCollision = dynamic_cast<BoxCollision*>(otherCollision);
    if (otherBoxCollision) {
        float xMin2 = otherBoxCollision->point.X;
        float yMin2 = otherBoxCollision->point.Y;
        float xMax2 = otherBoxCollision->point.X + otherBoxCollision->size.width;
        float yMax2 = otherBoxCollision->point.Y + otherBoxCollision->size.height;

        bool intersect = !(xMax1 < xMin2 || xMax2 < xMin1 || yMax1 < yMin2 || yMax2 < yMin1);

        if (!intersect) {
            return false;
        }

        if (IsExist(gameObject)) {
            return true;
        }

        gameObjects.push_back(gameObject);
        return true;
    }


    std::vector<Coord> otherPoints = otherCollision->GetPoints();
    if (otherPoints.empty()) {
        return false;
    }

    for (const Coord& p : otherPoints) {
        if (p.X >= xMin1 && p.X <= xMax1 && p.Y >= yMin1 && p.Y <= yMax1) {
            if (IsExist(gameObject)) {
                return true;
            }
            gameObjects.push_back(gameObject);
            return true;
        }
    }

    return false;
}

bool BoxCollision::IsCollisionStay(IGameObject* gameObject)
{
	return IsExist(gameObject);
}

bool BoxCollision::IsCollisionExit(IGameObject* gameObject)
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

bool BoxCollision::IsExist(IGameObject* gameObject)
{
	return ExistInVector<IGameObject*>(gameObjects, gameObject);
}

bool BoxCollision::operator==(const BoxCollision& other) const
{
	return !strcmp(root_title, other.root_title) &&
		!strcmp(type, other.type) &&
		point == other.point &&
		root_id == other.root_id;
}

bool BoxCollision::operator!=(const BoxCollision& other) const
{
	return !(*this == other);
}

BoxCollision& BoxCollision::operator=(const BoxCollision& other)
{
	if (this != &other)
	{
		point = other.point;
		size = other.size;

		root_id = other.root_id;

        free(root_title);
        free(type);

        root_title = strdup(other.root_title);
        type = strdup(other.type);
	}
	return *this;
}
