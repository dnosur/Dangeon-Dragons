#pragma once
#include <thread>
#include <mutex>

#include "../../../../Dodge/pawn/Pawn.h"
#include "../../../../Dodge/images/SlicedImage.h"

#include "../../AI/Movements/Movement.h"

class Skeleton
	: public Pawn, public std::enable_shared_from_this<Skeleton>
{
    std::unique_ptr<AIContext> aiContext;

    void LoadAnimations() override;

    void LoadAudio() override;
    void Draw() override;

    void Move();
    void Drag(Coord newPos);

    bool CheckForCollision(Coord position, Size size = Size(24, 24)) override;
    bool CheckForCollision() override;

    void MathSide(double& sideSize, bool isWidth);

    void AIMovement() override;

    void InitializeRender() override;
public:
    Skeleton(
        std::string title,
        std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
        Coord position, Size size, float speed, float maxSpeed, float minSpeed,
        float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
        std::vector<std::shared_ptr<IAnimation>> animations = {}
    );

    void Initialize() override;

    void SetSideSize(Sides sides, bool render = true) override;

    const Coord& GetDistanceTo(IGameObject& gameObject) override;
    float GetFloatDistanceTo(IGameObject& gameObject) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord position) override;

    void ViewPawn(class Pawn* pawn);
    std::string_view GetAnimationName() override;
    std::string_view GetAnimationMovementName(Coord& direction);

    void Update() override;

    void UpdateVertices() override;

    void UpdateVertices(std::vector<float>& vertices) override;

    const std::type_index& GetClassTypeId() override;
};