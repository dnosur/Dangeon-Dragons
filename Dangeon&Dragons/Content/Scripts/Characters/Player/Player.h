#pragma once
#include "../../../../Dodge/pawn/Pawn.h"

class Player :
    public Pawn
{
    Keyboard* keyboard;

    //������� �� ������ ��� ���������
    Coord startPos;
    Coord startPosVertexes[2];

    void LoadAnimations() override;
    const char* GetAnimationName() override;

    void LoadAudio() override;

    void Initialize() override;
	void Draw() override;

    void Move();
    void Drag(Coord newPos);

    bool CheckForCollision();
    bool CheckForCollision(Coord pos, Size size);

    void AIMovement() override;
public:
    Player(
        const char* title, Window& window,
        ICollision* collision, Material* material, Directions moveDirection,
        Coord pos, Size size, float speed, float maxSpeed, float minSpeed,
        float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
        std::vector<IAnimation*> animations = {}
    );

    Coord GetStartPos();

    Coord GetDistanceTo(IGameObject& gameObject) override;
    float GetDistanceTo(IGameObject& gameObject, Size objSize) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord pos) override;

    void Update() override;
};
