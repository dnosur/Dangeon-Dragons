#pragma once

#include <iostream>
#include <corecrt_math_defines.h>
#include "../materials/figures/BaseFigureMaterial.h"

class Circle 
    : public IGameObject
{
    Window* window;

    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    OnCollisionEnter OnCollisionEnterHandler;

    std::vector<float> vertexes;
    ICollision* collision;

    int numSegments;
    float r;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    Material* material;

    Directions moveDirection;

    char* title;

    bool MouseInCircle(Mouse& mouse);

    void MathHeights();

    void Draw();
public:

    Circle();
	Circle(const char* title, Window& window, Coord pos, int numSegments, float r, Color color);

	void Update();
	bool MouseHover(Mouse& mouse);
	bool MouseClick(Mouse& mouse);

    bool CollisionEnter(IGameObject& gameObject);

    std::vector<Coord> GetVertices();
	void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    Size GetSize();

    Coord GetPos();

    void SetPos(std::vector<Coord> vertices);
    void SetPos(Coord pos);

    Directions GetMoveDirection();
    void SetMoveDirection(Directions direction);

    void RotateToDirection(Directions direction);

    const char* GetTitle();
    void SetTitle(const char* title);

    void SetMaterial(Material* material);

    Material* GetMaterial();

    void SetCollision(ICollision* collision);
    ICollision* GetCollision();

    Window* GetWindow();

    const bool IsMouseOverlap();

    void HookMouseHover(MouseHoverHandler OnMouseHover);
    void HookMouseOver(MouseHoverHandler OnMouseOver);
    void HookMouseClick(MouseClickHandler OnMouseClick);

    void HookOnCollisionEnter(OnCollisionEnter handler);

    Circle& operator=(const Circle& other);
};