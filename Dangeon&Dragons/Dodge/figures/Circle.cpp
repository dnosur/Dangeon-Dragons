#include "Circle.h"

bool Circle::MouseInCircle(Mouse& mouse)
{
    float normMouseX = (mouse.GetMouseCoord().X / window->GetSize().GetWidth()) * 2.0f - 1.0f;
    float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / window->GetSize().GetHeight()) * 2.0f;

    float centerX = window->PixelToGLX(pos.X);
    float centerY = window->PixelToGLY(pos.Y);

    float distX = normMouseX - centerX;
    float distY = normMouseY - centerY;
    float distanceSquared = distX * distX + distY * distY;

    return distanceSquared <= (r * r);
}

void Circle::MathHeights()
{
    if (!vertexes.empty()) {
        vertexes.clear();
    }

    float centerX = window->PixelToGLX(pos.X);
    float centerY = window->PixelToGLY(pos.Y);

    vertexes.push_back(centerX);
    vertexes.push_back(centerY);
    vertexes.push_back(0.0f);
    vertexes.push_back(color.r);
    vertexes.push_back(color.g);
    vertexes.push_back(color.b);
    vertexes.push_back(color.a);

    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);

        vertexes.push_back(x + centerX);
        vertexes.push_back(y + centerY);
        vertexes.push_back(0.0f);
        vertexes.push_back(color.r);
        vertexes.push_back(color.g);
        vertexes.push_back(color.b);
        vertexes.push_back(color.a);
    }
}

Circle::Circle()
{
    title = (char*)"Undefined";
    window = NULL;

    r = numSegments = -1;

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    material = nullptr;
    collision = nullptr;
}

Circle::Circle(const char* title, Window& window, Coord pos, int numSegments, float r, Color color)
{
	copyStr(title, this->title);

	this->window = &window;
	this->pos = pos;
	this->numSegments = numSegments;
	this->color = baseColor = color;

    float scaleX = 2.0f / window.GetSize().width;
    float scaleY = 2.0f / window.GetSize().height;

    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    this->r = r * scale;

    MathHeights();

	OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
	OnMouseClick = nullptr;

    material = new BaseFigureMaterial();
    material->SetShader(
        new Shader(
            title,
            "Dodge/shaders/Figures/vertex.vs",
            "Dodge/shaders/Figures/fragment.frag"
        )
    );

	collision = nullptr;
}

void Circle::Draw()
{
    material->Use(this);
    material->GetShader()->SetVec4("targetColor", 0, 0, 0, 0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(float), vertexes.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); // Позиции
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float))); // Цвета
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glPopAttrib();
    glUseProgram(0);
}

void Circle::Update()
{
    Draw();
}

bool Circle::MouseHover(Mouse& mouse)
{
    if (mouse.IsEqual()) {
        return false;
    }

    const bool isHover = MouseInCircle(mouse);

    //std::cout << "X: " << mouse.GetMouseCoord().X << " Y: " << mouse.GetMouseCoord().Y << " " << "isHover: " << isHover << std::endl;

    if (isHover && OnMouseHover) {
        OnMouseHover(this, window->GetWindow());
    }

    if (!isHover && OnMouseOver) {
        OnMouseOver(this, window->GetWindow());
    }

    return isHover;
}

bool Circle::MouseClick(Mouse& mouse)
{
    if (!mouse.isClick() || !MouseInCircle(mouse)) {
        return false;
    }

    OnMouseClick(this, window->GetWindow());
    return true;
}

bool Circle::CollisionEnter(IGameObject& gameObject)
{
    if (!collision || collision == nullptr) {
        return false;
    }

    bool isEnter = collision->IsCollisionEnter(&gameObject);

    if (isEnter && OnCollisionEnterHandler) {
        OnCollisionEnterHandler(this, &gameObject, window->GetWindow());
    }
}

std::vector<Coord> Circle::GetVertices()
{
    return std::vector<Coord>();
}

void Circle::SetTitle(const char* title)
{
	copyStr(title, this->title);
}

void Circle::SetColor(Color color)
{
	this->color = color;
}

Color Circle::GetColor()
{
    return color;
}

Color Circle::GetBaseColor()
{
    return baseColor;
}

Size Circle::GetSize()
{
    return size;
}

Coord Circle::GetPos()
{
    return pos;
}

void Circle::SetPos(std::vector<Coord> vertices)
{
}

void Circle::SetPos(Coord pos)
{
}

Directions Circle::GetMoveDirection()
{
    return moveDirection;
}

void Circle::SetMoveDirection(Directions direction)
{
    this->moveDirection = direction;
}

void Circle::RotateToDirection(Directions direction)
{
}

const char* Circle::GetTitle()
{
    return title;
}

void Circle::SetMaterial(Material* material)
{
    this->material = material;
}

Material* Circle::GetMaterial()
{
    return material;
}

void Circle::SetCollision(ICollision* collision)
{
    this->collision = collision;
}

ICollision* Circle::GetCollision()
{
    return collision;
}

Window* Circle::GetWindow()
{
    return window;
}

const bool Circle::IsMouseOverlap()
{
    return MouseInCircle(window->GetMouse());
}

void Circle::HookMouseHover(MouseHoverHandler OnMouseHover)
{
	this->OnMouseHover = OnMouseHover;
}

void Circle::HookMouseOver(MouseHoverHandler OnMouseOver)
{
	this->OnMouseOver = OnMouseOver;
}

void Circle::HookMouseClick(MouseClickHandler OnMouseClick)
{
	this->OnMouseClick = OnMouseClick;
}

void Circle::HookOnCollisionEnter(OnCollisionEnter handler)
{
    this->OnCollisionEnterHandler = handler;
}

Circle& Circle::operator=(const Circle& other)
{
    if (this == &other) {
        return *this;
    }

    baseColor = other.baseColor;
    color = other.color;
    numSegments = other.numSegments;

    OnMouseClick = other.OnMouseClick;
    OnMouseHover = other.OnMouseHover;
    OnMouseOver = other.OnMouseOver;

    vertexes = other.vertexes;

    r = other.r;

    pos = other.pos;
    size = other.size;

    copyStr(other.title, title);

    material = other.material;

    return *this;
}
