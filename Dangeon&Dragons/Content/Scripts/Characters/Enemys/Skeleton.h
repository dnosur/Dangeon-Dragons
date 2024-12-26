#pragma once
#include <thread>
#include <mutex>

#include "../../../../Dodge/pawn/Pawn.h"
#include "../../../../Dodge/images/SlicedImage.h"

#include "../../AI/Movement.h"

class Skeleton
	: public Pawn
{
    std::weak_ptr<Pawn> target;
    float viewDistance;

    float viewWidth;

    Coord startPos;
    Coord startPosVertexes[2];
    Coord offset;

    //В дальнейшем перенести в класс!
    std::vector<Movement*> movements;
	int movementIndex;

    std::mutex pathMutex;
    bool findingPath;

    void LoadAnimations() override;
    const char* GetAnimationName() override;
    const char* GetAnimationMovementName(Coord direction);

    void LoadAudio() override;

    Directions GetDirection(Coord direction);

    void Initialize() override;
    void Draw() override;

    void Move();
    void Drag(Coord newPos);

    bool CheckForCollision(Coord position);
    bool CheckForCollision();

    void AIMovement() override;

    Coord GenerateRandomPosition(Coord center, float radius);

    bool FindPath(Coord start, Coord goal);
    bool FindTarget();

    std::vector<Movement*> GetNeighbors(Coord position);
    bool IsWalkable(Coord position);
public:
    Skeleton(
        const char* title, Window& window,
        ICollision* collision, Material* material, Directions moveDirection,
        Coord pos, Size size, float speed, float maxSpeed, float minSpeed,
        float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
        std::vector<IAnimation*> animations = {}
    );
    ~Skeleton() = default;

    Coord GetStartPos();

    Coord GetDistanceTo(IGameObject& gameObject) override;
    float GetFloatDistanceTo(IGameObject& gameObject) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord pos) override;

    void SetTarget(std::shared_ptr<Pawn> target);
    void SetTarget(std::weak_ptr<Pawn>& target);
    std::weak_ptr<Pawn> GetTarget();

    void ViewPawn(Pawn* pawn);

    void SetPathOffset(Coord offset);

    void Update() override;
};

