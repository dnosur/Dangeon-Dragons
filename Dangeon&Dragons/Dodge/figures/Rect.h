#pragma once
#include "../materials/figures/BaseFigureMaterial.h"
#include "../images/ImagesController.h"
#include "../Directions.h"

extern std::vector<unsigned int> defaultIndicies;

class Rect :
    public IGameObject
{
    MouseHoverHandler OnMouseHover;
    MouseHoverHandler OnMouseOver;

    MouseClickHandler OnMouseClick;

    OnCollisionEnter OnCollisionEnterHandler;

    unsigned int VAO, VBO, EBO;

    Coord vertex1;
    Coord vertex2;

    std::shared_ptr<ICollision> collision;

    Coord position;

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
    void MathPos(Coord& position);

    void MathSize(Size& size);

    void MathSide(double& sideSize, bool isWidth);

    void Draw();

    void InitializeRender();
    std::vector<float> GetRenderVertices();
public:
    Rect();
    Rect(std::string title, Coord position, Size size, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(std::string title, Coord vertex1, Coord vertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);
    Rect(std::string title, Coord vertex1, Coord vertex2, Coord textureVertex1, Coord textureVertex2, Color color = Color(0, 0, 0), Directions moveDirection = Directions::DOWN);

    static void InitQuads(
        unsigned int& VAO, unsigned int& VBO, unsigned int& EBO,
        std::vector<float> vertices, std::vector<unsigned int>& indices = defaultIndicies
    );

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

    Window* GetWindow();

    void SetColor(Color color);
    Color GetColor();

    Color GetBaseColor();

    std::vector<Coord> GetVertices();

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

