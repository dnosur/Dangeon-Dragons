#include "BoxCollision.h"
#include "../functions.h"

BoxCollision::BoxCollision()
{
}

BoxCollision::BoxCollision(Coord point, Size size, int root_id, std::string root_title, std::string type)
{
	this->point = point;
	this->size = size;

	this->root_id = root_id;

    this->kinematic = false;

    SetLayer(Layer::Collision);

    this->root_title = root_title;
    this->type = type;
}

BoxCollision::~BoxCollision()
{
}

int BoxCollision::GetRootId()
{
	return root_id;
}

std::string_view BoxCollision::GetRootTitle()
{
	return root_title;
}

std::string_view BoxCollision::GetType()
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

Layer BoxCollision::GetLayer()
{
    return layer;
}

void BoxCollision::SetLayer(Layer layer)
{
	this->layer = layer;
}

bool BoxCollision::IsKinematic()
{
    return kinematic;
}

void BoxCollision::SetKinematic(bool kinematic)
{
    this->kinematic = kinematic;
}

bool BoxCollision::IsCollisionEnter(IGameObject* gameObject)
{
    std::shared_ptr<ICollision> collision = gameObject->GetCollision().lock();

    if (!gameObject || !collision) {
        return false;
    }

    // Координаты текущей коллизии
    float xMin1 = point.X;
    float yMin1 = point.Y;
    float xMax1 = point.X + size.width;
    float yMax1 = point.Y + size.height;

    // Проверяем, является ли другая коллизия "BoxCollision"
    std::shared_ptr<BoxCollision> otherBoxCollision = std::dynamic_pointer_cast<BoxCollision>(collision);
    if (otherBoxCollision) {
        // Координаты другой коллизии
        float xMin2 = otherBoxCollision->point.X;
        float yMin2 = otherBoxCollision->point.Y;
        float xMax2 = otherBoxCollision->point.X + otherBoxCollision->size.width;
        float yMax2 = otherBoxCollision->point.Y + otherBoxCollision->size.height;

        // Проверяем пересечение
        bool isIntersecting = !(xMax1 < xMin2 || xMax2 < xMin1 || yMax1 < yMin2 || yMax2 < yMin1);

        // Проверяем вложение одного прямоугольника в другой
        bool isInside = (xMin2 >= xMin1 && xMax2 <= xMax1 && yMin2 >= yMin1 && yMax2 <= yMax1) ||
            (xMin1 >= xMin2 && xMax1 <= xMax2 && yMin1 >= yMin2 && yMax1 <= yMax2);

        if (isIntersecting || isInside) {
            // Проверяем, если объект уже зарегистрирован
            if (IsExist(gameObject)) {
                return true;
            }

            // Добавляем объект в список коллизий
            gameObjects.push_back(gameObject);
            return true;
        }
    }


    std::vector<Coord> otherPoints = collision->GetPoints();
    if (otherPoints.empty()) {
        return false;
    }

    for (Coord& p : otherPoints) {
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

bool BoxCollision::IsCollisionEnter(Coord point, Size size)
{
    // Координаты текущей коллизии
    float xMin1 = this->point.X;
    float yMin1 = this->point.Y;
    float xMax1 = this->point.X + this->size.width;
    float yMax1 = this->point.Y + this->size.height;

    // Координаты другой коллизии
    float xMin2 = point.X;
    float yMin2 = point.Y;
    float xMax2 = point.X + size.width;
    float yMax2 = point.Y + size.height;

    // Проверяем пересечение
    bool isIntersecting = !(xMax1 < xMin2 || xMax2 < xMin1 || yMax1 < yMin2 || yMax2 < yMin1);

    // Проверяем вложение одного прямоугольника в другой
    bool isInside = (xMin2 >= xMin1 && xMax2 <= xMax1 && yMin2 >= yMin1 && yMax2 <= yMax1) ||
        (xMin1 >= xMin2 && xMax1 <= xMax2 && yMin1 >= yMin2 && yMax1 <= yMax2);

    return isIntersecting || isInside;
}

bool BoxCollision::IsExist(IGameObject* gameObject)
{
	return ExistInVector<IGameObject*>(gameObjects, gameObject);
}

bool BoxCollision::operator==(const BoxCollision& other) const
{
	return root_title == other.root_title &&
		type == other.type &&
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

        root_title = other.root_title;
        type = other.type;
	}
	return *this;
}
