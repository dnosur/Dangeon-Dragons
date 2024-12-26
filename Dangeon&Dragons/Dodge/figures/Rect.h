#pragma once
#include "../materials/figures/BaseFigureMaterial.h"
#include "../images/ImagesController.h"
#include "../Directions.h"

class Rect :
    public IGameObject
{
    Window* window;

    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    OnCollisionEnter OnCollisionEnterHandler;

    Coord vertex1;
    Coord vertex2;

    ICollision* collision;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    Material* material;

    Directions moveDirection;

    Camera* camera;

    char* title;

    Layer layer;

    bool kinematic;

    bool MouseInRect(Mouse& mouse);

    void MathPos(Coord& vertex1, Coord& vertex2);
    void MathPos(Coord& pos);

    void Draw();
public:
    Rect();
    Rect(const char* title, Window& window, Coord pos, Size size, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(const char* title, Window& window, Coord vertex1, Coord vertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(const char* title, Window& window, Coord vertex1, Coord vertex2, Coord textureVertex1, Coord textureVertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    ~Rect() = default;

    static std::vector<float> GetVerticesByDirection(
        Rect& rect, 
        Directions moveDirection, 
        bool returnTexCoords = false
    );

    void RotateToDirection(Directions direction);

    void Update();

    Coord GetPos();
    Coord GetOpenGlPos();

    Size GetSize();

    bool MouseHover(Mouse& mouse);
    bool MouseClick(Mouse& mouse);

    bool CollisionEnter(IGameObject& gameObject);

    Window* GetWindow();

    void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    std::vector<Coord> GetVertices();

    void SetPos(std::vector<Coord> vertices);
    void SetPos(Coord pos);

    void SetMaterial(Material* material);

    Material* GetMaterial();

    void SetCollision(ICollision* collision);
    ICollision* GetCollision();

    const char* GetTitle();
    void SetTitle(const char* title);

    void SetMoveDirection(Directions moveDirection);
    Directions GetMoveDirection();

    const bool IsMouseOverlap();

    void SetLayer(Layer layer);
    Layer GetLayer();

    bool IsKinematic();
    void SetKinematic(bool kinematic);

    Coord GetDistanceTo(IGameObject& gameObject);

    void HookMouseHover(MouseHoverHandler handler);
    void HookMouseOver(MouseHoverHandler handler);

    void HookMouseClick(MouseClickHandler handler);

    void HookOnCollisionEnter(OnCollisionEnter handler);

    bool operator==(const Rect& other) const;
    bool operator!=(const Rect& other) const;
    Rect& operator=(const Rect& other);
};

