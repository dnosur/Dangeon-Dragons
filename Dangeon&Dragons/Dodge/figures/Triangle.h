#pragma once
#include "../materials/figures/BaseFigureMaterial.h"

class Triangle
    : public IGameObject
{
    Window* window;

    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    OnCollisionEnter OnCollisionEnterHandler;

    Coord vertex1;
    Coord vertex2;
    Coord vertex3;

	ICollision* collision;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    Material* material;

	Directions moveDirection;

    char* title;

    bool MouseInTriangle(Mouse& mouse);

    void Draw();
public:
    Triangle();
    Triangle(const char* title, Window& window, Coord pos, Size size, Color color = Color(0, 0, 0));
    Triangle(const char* title, Window& window, Coord vertex1, Coord vertex2, Coord vertex3, Color color = Color(0, 0, 0));

    void Update();
    Coord GetPos();

    void SetPos(std::vector<Coord> vertices);
    void SetPos(Coord pos);

    Directions GetMoveDirection();
	void SetMoveDirection(Directions moveDirection);

    void RotateToDirection(Directions direction);

    Size GetSize();

    bool MouseHover(Mouse& mouse);
    bool MouseClick(Mouse& mouse);

    bool CollisionEnter(IGameObject& gameObject);

    Window* GetWindow();

    void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    std::vector<Coord> GetVertices();

    const char* GetTitle();
    void SetTitle(const char* title);

    void SetMaterial(Material* material);

    Material* GetMaterial();

    void SetCollision(ICollision* collision);
    ICollision* GetCollision();

    const bool IsMouseOverlap();

    void HookMouseHover(MouseHoverHandler handler);
    void HookMouseOver(MouseHoverHandler handler);

    void HookMouseClick(MouseClickHandler handler);

    void HookOnCollisionEnter(OnCollisionEnter handler);

    Triangle& operator=(const Triangle& other);
};

