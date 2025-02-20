#pragma once
#include "../../../../Dodge/pawn/Pawn.h"

#include <mutex>

class Player :
    public Pawn, public std::enable_shared_from_this<Player>
{
    //������� �� ������ ��� ���������
    Coord startPos;
    Coord startPosVertexes[2];

    std::mutex* raycastMutex;

    void LoadAnimations() override;
    std::string_view GetAnimationName() override;

    void LoadAudio() override;
	void Draw() override;

    void Move();
    void Drag(Coord newPos);

    void Raycasting();

    bool CheckForCollision();
    bool CheckForCollision(Coord position, Size size);

    void MathSide(double& sideSize, bool isWidth) override;

    void AIMovement() override;

    void InitializeRender() override;
public:
    Player(
        std::string title,
        std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
        Coord position, Size size, float speed, float maxSpeed, float minSpeed,
        float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
        std::vector<std::shared_ptr<IAnimation>> animations = {}
    );

    void Initialize() override;

    void SetSideSize(Sides sides, bool render = true) override;

    Coord GetStartPos();

    const Coord& GetDistanceTo(IGameObject& gameObject) override;
    float GetFloatDistanceTo(IGameObject& gameObject) override;

    bool IsNear(IGameObject& gameObject) override;
    bool IsNear(Coord position) override;

    void Update() override;

    void UpdateVertices() override;

    void UpdateVertices(std::vector<float>& vertices) override;
};

