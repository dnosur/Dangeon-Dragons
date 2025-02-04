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

    std::shared_ptr<ICollision> collision;

    Coord pos;

    Size size;

    Color color;
    Color baseColor;

    std::shared_ptr<Material> material;

    Directions moveDirection;

    Camera* camera;

    std::string title;

    Layer layer;

    bool kinematic;

    bool MouseInRect(Mouse& mouse);

    void MathPos(Coord& vertex1, Coord& vertex2);
    void MathPos(Coord& pos);

    void MathSize(Size& size);

    void MathSide(double& sideSize, bool isWidth);

    void Draw();
public:
    Rect();
    Rect(std::string title, Window& window, Coord pos, Size size, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(std::string title, Window& window, Coord vertex1, Coord vertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(std::string title, Window& window, Coord vertex1, Coord vertex2, Coord textureVertex1, Coord textureVertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);

    static std::vector<float> GetVerticesByDirection(
        Rect& rect, 
        Directions moveDirection, 
        bool returnTexCoords = false
    );

    void RotateToDirection(Directions direction);

    void Update();

    const Coord& GetPos();
    const Coord& GetOpenGlPos();

    void SetSize(Size size);
    Size GetSize();

    void SetSideSize(Sides sides);

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

    void SetMaterial(std::shared_ptr<Material> material);

    std::weak_ptr<Material> GetMaterial();

    void SetCollision(std::shared_ptr<ICollision> collision);
    std::weak_ptr<ICollision> GetCollision();

    const std::string& GetTitleString();
    std::string_view GetTitle();
    void SetTitle(std::string title);

    void SetMoveDirection(Directions moveDirection);
    Directions GetMoveDirection();

    const bool IsMouseOverlap();

    void SetLayer(Layer layer);
    Layer GetLayer();

    bool IsKinematic();
    void SetKinematic(bool kinematic);

    const Coord& GetDistanceTo(IGameObject& gameObject);

    void HookMouseHover(MouseHoverHandler handler);
    void HookMouseOver(MouseHoverHandler handler);

    void HookMouseClick(MouseClickHandler handler);

    void HookOnCollisionEnter(OnCollisionEnter handler);

    bool operator==(const Rect& other) const;
    bool operator!=(const Rect& other) const;
    Rect& operator=(const Rect&& other);
};

