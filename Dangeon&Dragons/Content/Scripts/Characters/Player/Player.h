#pragma once
#include "../../../../Dodge/pawn/Pawn.h"

#include <mutex>

class Player :
    public Pawn
{
    Keyboard* keyboard;

    //Позиция на экране для отрисовки
    Coord startPos;
    Coord startPosVertexes[2];

    std::mutex* raycastMutex;

    void LoadAnimations() override;
    std::string_view GetAnimationName() override;

    void LoadAudio() override;

    void Initialize() override;
	void Draw() override;

    void Move();
    void Drag(Coord newPos);

    void Raycasting();

    bool CheckForCollision();
    bool CheckForCollision(Coord pos, Size size);

    void AIMovement() override;

    void MathSide(double& sideSize, bool isWidth);
public:
    Player(
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

    void SetSideSize(Sides sides);

    const Coord& GetDistanceTo(IGameObject& gameObject) override;
    float GetFloatDistanceTo(IGameObject& gameObject) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord pos) override;

    void Update() override;
};

