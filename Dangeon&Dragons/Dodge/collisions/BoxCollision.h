#pragma once
#include "ICollision.h"

class BoxCollision :
    public ICollision
{
	int root_id;
	std::string root_title;
	std::string type;

	Coord point;
	Size size;

	Layer layer;

	bool kinematic;

	std::vector<IGameObject*> gameObjects;
public:
<<<<<<< Updated upstream
	BoxCollision(Coord point,Size size, int root_id, char* root_title = nullptr, char* type = nullptr);
=======
	BoxCollision();
	BoxCollision(Coord point,Size size, int root_id, std::string root_title = "empty", std::string type = "empty");
>>>>>>> Stashed changes
	~BoxCollision();

	int GetRootId();

	std::string_view GetRootTitle();
	std::string_view GetType();

	BoxCollision* Clone() const override;

	std::vector<Coord> GetPoints();
	void SetPoints(std::vector<Coord> points);

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

