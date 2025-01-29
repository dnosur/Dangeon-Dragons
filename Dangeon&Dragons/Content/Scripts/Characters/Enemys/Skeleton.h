#pragma once
#include <thread>
#include <mutex>

#include "../../../../Dodge/pawn/Pawn.h"
#include "../../../../Dodge/images/SlicedImage.h"

#include "../../AI/Movement.h"

class Skeleton
	: public Pawn
{
    Pawn* target;
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
    std::string_view GetAnimationName() override;
    std::string_view GetAnimationMovementName(Coord direction);

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
<<<<<<< Updated upstream
        const char* title, Window& window,
        ICollision* collision, Material* material, Directions moveDirection,
=======
        std::string title, Window& window,
        std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
>>>>>>> Stashed changes
        Coord pos, Size size, float speed, float maxSpeed, float minSpeed,
        float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
        std::vector<IAnimation*> animations = {}
    );

    Coord GetStartPos();

    const Coord& GetDistanceTo(IGameObject& gameObject) override;
    float GetFloatDistanceTo(IGameObject& gameObject) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord pos) override;

    void SetTarget(Pawn* target);
    Pawn* GetTarget();

    void ViewPawn(Pawn* pawn);

    void SetPathOffset(Coord offset);

    void Update() override;
};

