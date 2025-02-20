#pragma once
#include "../materials/figures/BaseFigureMaterial.h"
#include "../images/ImagesController.h"
#include "../Directions.h"
#include "../render/RectRenderInstance.h"

class Rect :
    public IGameObject
{
    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    OnCollisionEnter OnCollisionEnterHandler;

    std::unique_ptr<RectRenderInstance> renderInstance;

    std::shared_ptr<ICollision> collision;

    Coord position;

    Size size;

    Color color;
    Color baseColor;

    Directions moveDirection;

    Camera* camera;

    std::string title;

    Layer layer;

    bool kinematic;

    bool MouseInRect(Mouse& mouse);

    void MathPos(Coord& vertex1, Coord& vertex2);
    void MathPos(Coord& position);

    void MathSize(Size& size);

    void MathSide(double& sideSize, bool isWidth);

    void Draw();

    void InitializeRender();
public:
    Rect();
    Rect(std::string title, Coord position, Size size, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(std::string title, Coord vertex1, Coord vertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(std::string title, Coord vertex1, Coord vertex2, Coord textureVertex1, Coord textureVertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);

    static std::vector<float> GetVerticesByDirection(
        Rect& rect, 
        Directions moveDirection, 
        bool returnTexCoords = false
    );

    void RotateToDirection(Directions direction);

    void Update();

    void UpdateVertices();

    void UpdateVertices(std::vector<float>& vertices);

    const Coord& GetPos();
    const Coord& GetOpenGlPos();

    void SetSize(Size size, bool render = true);
    Size GetSize();

    void SetSideSize(Sides sides, bool render = true);

    bool MouseHover(Mouse& mouse);
    bool MouseClick(Mouse& mouse);

    bool CollisionEnter(IGameObject& gameObject);

    void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    void SetPos(std::vector<Coord> vertices, bool render = true);
    void SetPos(Coord position, bool render = true);

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

