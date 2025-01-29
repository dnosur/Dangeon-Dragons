#pragma once
#include "../../../../Dodge/pawn/Pawn.h"

#include <mutex>

class Player :
    public Pawn, public std::enable_shared_from_this<Player>
{
    Keyboard* keyboard;

    //Позиция на экране для отрисовки
    Coord startPos;
    Coord startPosVertexes[2];

    std::mutex* raycastMutex;

    void LoadAnimations() override;
    const char* GetAnimationName() override;

    void LoadAudio() override;
	void Draw() override;

    void Move();
    void Drag(Coord newPos);

    void Raycasting();

    bool CheckForCollision();
    bool CheckForCollision(Coord pos, Size size);

    void MathSide(double& sideSize, bool isWidth) override;

    void AIMovement() override;
public:
    Player(
        const char* title, Window& window,
        std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
        Coord pos, Size size, float speed, float maxSpeed, float minSpeed,
        float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
        std::vector<std::shared_ptr<IAnimation>> animations = {}
    );

    void Initialize() override;

    void SetSideSize(Sides sides) override;

    Coord GetStartPos();

    Coord GetDistanceTo(IGameObject& gameObject) override;
    float GetFloatDistanceTo(IGameObject& gameObject) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord pos) override;

    void Update() override;
};

