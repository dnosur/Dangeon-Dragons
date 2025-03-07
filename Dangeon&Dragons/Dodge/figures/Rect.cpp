#include "Rect.h"
#include "../shaders/ShadersController.h"

std::vector<unsigned int> defaultIndicies = {
    0, 1, 2,
    2, 3, 0
};

bool Rect::MouseInRect(Mouse& mouse)
{
    float normMouseX = (mouse.GetMouseCoord().X / Window::GetRenderResolution().GetWidth()) * 2.0f - 1.0f;
    float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / Window::GetRenderResolution().GetHeight()) * 2.0f;

    const Coord& vertex1 = renderInstance->GetVertex1();
    const Coord& vertex2 = renderInstance->GetVertex2();

    return (normMouseX >= vertex1.X && normMouseX <= vertex2.X &&
        normMouseY >= vertex1.Y && normMouseY <= vertex2.Y);
}

void Rect::MathPos(Coord& vertex1, Coord& vertex2)
{
    renderInstance->SetVertexes(vertex1, vertex2);

    float width = (vertex2.X - vertex1.X) * (Window::GetRenderResolution().GetWidth() / 2.0f);
    float height = (vertex2.Y - vertex1.Y) * (Window::GetRenderResolution().GetHeight() / 2.0f);

    // ������ ������������ �� ������ ������� ���������
    size = Size(round(std::abs(width)), round(std::abs(height)));

    // ������� ����� � OpenGL-�����������
    float centerX_GL = (vertex1.X + vertex2.X) / 2.0f;
    float centerY_GL = (vertex1.Y + vertex2.Y) / 2.0f;

    // ����������� OpenGL-���������� � �������
    position = Coord(
        ((centerX_GL + 1.0f) / 2.0f) * (float)Window::GetRenderResolution().GetWidth(),
        ((1.0f - (centerY_GL + 1.0f) / 2.0f) * (float)Window::GetRenderResolution().GetHeight())
    );
}

void Rect::MathPos(Coord& position)
{
    this->position = position;
    float glCenterX = Window::PixelToGLX(position.X);
    float glCenterY = Window::PixelToGLY(position.Y);

    float glWidth = (float)size.GetWidth() / (float)Window::GetRenderResolution().GetWidth() * 2.0f;
    float glHeight = (float)size.GetHeight() / (float)Window::GetRenderResolution().GetHeight() * 2.0f;

    // Calculate the vertex1 and vertex2 coordinates
    //vertex2.X = glCenterX - glWidth / 2.0f;
    //vertex1.Y = glCenterY - glHeight / 2.0f;
    //vertex1.X = glCenterX + glWidth / 2.0f;
    //vertex2.Y = glCenterY + glHeight / 2.0f;

    renderInstance->SetVertexes(
        Coord(glCenterX + glWidth / 2.0f, glCenterY - glHeight / 2.0f),
        Coord(glCenterX - glWidth / 2.0f, glCenterY + glHeight / 2.0f)
    );
}

void Rect::MathSize(Size& size)
{
    this->size = size;
    MathPos(position);
}

void Rect::MathSide(double& sideSize, bool isWidth)
{


}

Rect::Rect()
{
    title = (char*)"Undefined";

    collision = nullptr;

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    kinematic = false;
    this->layer = Layer::Undefined;

    moveDirection = Directions::DOWN;

    renderInstance = std::make_unique<RectRenderInstance>();
}

Rect::Rect(
    std::string title, Coord
    position, Size size, Color color, 
    Directions moveDirection
)
{
    this->title = title;

    this->size = size;
    this->color = baseColor = color;

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    std::unique_ptr<Material> material = std::make_unique<BaseFigureMaterial>();
    material->SetShader(
        ShadersController::GetShaderID("BaseFigure")
    );

    material->SetDiffuse(color);
    material->SetDiffuseMap(ImagesController::GetDafaultImage().lock());

    this->moveDirection = moveDirection;

    kinematic = false;
    this->layer = Layer::GameObject;

    collision = nullptr;

    renderInstance = std::make_unique<RectRenderInstance>(std::move(material));

    MathPos(position);
}

Rect::Rect(
    std::string title, 
    Coord vertex1, Coord vertex2, 
    Color color, Directions moveDirection
)
{
    this->title = title;

    this->color = baseColor = color;

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    std::unique_ptr<Material> material = std::make_unique<BaseFigureMaterial>();
    material->SetShader(
        ShadersController::GetShaderID("BaseFigure")
    );

    this->moveDirection = moveDirection;

    kinematic = false;
    this->layer = Layer::GameObject;

    collision = nullptr;

    renderInstance = std::make_unique<RectRenderInstance>(std::move(material));

    MathPos(vertex1, vertex2);
}

Rect::Rect(
    std::string title, 
    Coord vertex1, Coord vertex2, 
    Coord textureVertex1, Coord textureVertex2, 
    Color color, Directions moveDirection
)
{
    this->title = title;

    this->color = baseColor = color;

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    std::unique_ptr<Material> material = std::make_unique<BaseFigureMaterial>();
    material->SetShader(
        ShadersController::GetShaderID("BaseFigure")
    );

    std::vector<Coord> verticies = std::vector<Coord>{
        textureVertex1, textureVertex2
    };
    material->SetDiffuseMapVerticies(verticies);

    this->moveDirection = moveDirection;

    kinematic = false;
    this->layer = Layer::GameObject;

    collision = nullptr;

    renderInstance = std::make_unique<RectRenderInstance>(std::move(material));

    MathPos(vertex1, vertex2);
}

void Rect::Update()
{
    Draw();
}

void Rect::Draw()
{
    renderInstance->Render();
}

void Rect::UpdateVertices()
{
    renderInstance->UpdateVertices();
}

void Rect::UpdateVertices(std::vector<float>& vertices)
{
    renderInstance->UpdateVertices(vertices);
}

void Rect::InitializeRender()
{
    renderInstance->Initialize();
}

std::vector<float> Rect::GetVerticesByDirection(Rect& rect, Directions moveDirection, bool returnTexCoords)
{
    Coord vertex1 = rect.renderInstance->GetVertex1();
    Coord vertex2 = rect.renderInstance->GetVertex2();

    std::weak_ptr<Material> weakMaterial = rect.renderInstance->GetMaterial();
    if (weakMaterial.expired() || !weakMaterial.lock()) {
        return rect.renderInstance->GetVertices();
    }

    std::shared_ptr<Material> material = weakMaterial.lock();

    const bool isHasDiffuseVertexs = 
        material->GetDiffuseMapVerticies().size() >= 2 && 
        material->GetDiffuseMap().lock() != nullptr;
    const Coord& textCoord1 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
    const Coord& textCoord2 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

    if (moveDirection == Directions::UP) {
        return returnTexCoords ? std::vector<float> {
            (float)vertex2.X, (float)vertex2.Y, 0.0f, (float)textCoord1.X, (float)textCoord1.Y,
                (float)vertex1.X, (float)vertex2.Y, 0.0f, (float)textCoord2.X, (float)textCoord1.Y,
                (float)vertex1.X, (float)vertex1.Y, 0.0f, (float)textCoord2.X, (float)textCoord2.Y,
                (float)vertex2.X, (float)vertex1.Y, 0.0f, (float)textCoord1.X, (float)textCoord2.Y
        }
        : std::vector<float>{
            (float)vertex2.X, (float)vertex2.Y, 0.0f, 
                (float)vertex1.X, (float)vertex2.Y, 0.0f, 
                (float)vertex1.X, (float)vertex1.Y, 0.0f, 
                (float)vertex2.X, (float)vertex1.Y, 0.0f
        };
    }

    if (moveDirection == Directions::DOWN) {
        return returnTexCoords ? std::vector<float> {
            (float)vertex1.X, (float)vertex1.Y, 0.0f, (float)textCoord1.X, (float)textCoord1.Y,
                (float)vertex2.X, (float)vertex1.Y, 0.0f, (float)textCoord2.X, (float)textCoord1.Y,
                (float)vertex2.X, (float)vertex2.Y, 0.0f, (float)textCoord2.X, (float)textCoord2.Y,
                (float)vertex1.X, (float)vertex2.Y, 0.0f, (float)textCoord1.X, (float)textCoord2.Y
        }
        : std::vector<float>{
			(float)vertex1.X, (float)vertex1.Y, 0.0f, 
				(float)vertex2.X, (float)vertex1.Y, 0.0f, 
				(float)vertex2.X, (float)vertex2.Y, 0.0f, 
				(float)vertex1.X, (float)vertex2.Y, 0.0f
		};
    }

    if (moveDirection == Directions::LEFT) {
        return returnTexCoords 
                ? std::vector<float> {
                (float)vertex1.X, (float)vertex1.Y, 0.0f, (float)textCoord1.X, (float)textCoord1.Y,
                (float)vertex1.X, (float)vertex2.Y, 0.0f, (float)textCoord2.X, (float)textCoord1.Y,
                (float)vertex2.X, (float)vertex2.Y, 0.0f, (float)textCoord2.X, (float)textCoord2.Y,
                (float)vertex2.X, (float)vertex1.Y, 0.0f, (float)textCoord1.X, (float)textCoord2.Y
            }
        :
            std::vector<float>{
                (float)vertex1.X, (float)vertex1.Y, 0.0f,
                (float)vertex1.X, (float)vertex2.Y, 0.0f,
                (float)vertex2.X, (float)vertex2.Y, 0.0f,
                (float)vertex2.X, (float)vertex1.Y, 0.0f,
        };
    }

    if (moveDirection == Directions::RIGHT) {
        return returnTexCoords ? std::vector<float> {
            (float)vertex2.X, (float)vertex2.Y, 0.0f, (float)textCoord1.X, (float)textCoord1.Y,
                (float)vertex2.X, (float)vertex1.Y, 0.0f, (float)textCoord2.X, (float)textCoord1.Y,
                (float)vertex1.X, (float)vertex1.Y, 0.0f, (float)textCoord2.X, (float)textCoord2.Y,
                (float)vertex1.X, (float)vertex2.Y, 0.0f, (float)textCoord1.X, (float)textCoord2.Y
        }
        : std::vector<float>{
            (float)vertex2.X, (float)vertex2.Y, 0.0f, 
                (float)vertex2.X, (float)vertex1.Y, 0.0f, 
                (float)vertex1.X, (float)vertex1.Y, 0.0f, 
                (float)vertex1.X, (float)vertex2.Y, 0.0f, 
        };
    }
}

void Rect::RotateToDirection(Directions direction)
{
    // ������� ��������� � ����������� �� �������� � �������� �����������
    if (moveDirection == direction) return; // ��� � ������ �����������

    Coord vertex1 = renderInstance->GetVertex1();
	Coord vertex2 = renderInstance->GetVertex2();

    // ���������� ���� ��������
    if ((moveDirection == Directions::RIGHT && direction == Directions::LEFT) ||
        (moveDirection == Directions::LEFT && direction == Directions::RIGHT) ||
        (moveDirection == Directions::UP && direction == Directions::DOWN) ||
        (moveDirection == Directions::DOWN && direction == Directions::UP)) {
        // �������� �� 180 ��������
        std::swap(vertex1.X, vertex2.X);
        std::swap(vertex1.Y, vertex2.Y);
    }
    else if ((moveDirection == Directions::RIGHT && direction == Directions::UP) ||
        (moveDirection == Directions::UP && direction == Directions::LEFT) ||
        (moveDirection == Directions::LEFT && direction == Directions::DOWN) ||
        (moveDirection == Directions::DOWN && direction == Directions::RIGHT)) {
        // ������� �� 90 �������� ������ ������� �������
        float centerX = (vertex1.X + vertex2.X) / 2;
        float centerY = (vertex1.Y + vertex2.Y) / 2;

        float tempX = vertex1.X - centerX;
        float tempY = vertex1.Y - centerY;

        vertex1.X = -tempY + centerX;
        vertex1.Y = tempX + centerY;

        tempX = vertex2.X - centerX;
        tempY = vertex2.Y - centerY;

        vertex2.X = -tempY + centerX;
        vertex2.Y = tempX + centerY;
    }
    else if ((moveDirection == Directions::RIGHT && direction == Directions::DOWN) ||
        (moveDirection == Directions::DOWN && direction == Directions::LEFT) ||
        (moveDirection == Directions::LEFT && direction == Directions::UP) ||
        (moveDirection == Directions::UP && direction == Directions::RIGHT)) {
        // ������� �� 90 �������� �� ������� �������
        float centerX = (vertex1.X + vertex2.X) / 2;
        float centerY = (vertex1.Y + vertex2.Y) / 2;

        float tempX = vertex1.X - centerX;
        float tempY = vertex1.Y - centerY;

        vertex1.X = tempY + centerX;
        vertex1.Y = -tempX + centerY;

        tempX = vertex2.X - centerX;
        tempY = vertex2.Y - centerY;

        vertex2.X = tempY + centerX;
        vertex2.Y = -tempX + centerY;
    }

    renderInstance->SetVertexes(vertex1, vertex2);
    // ��������� �����������
    moveDirection = direction;
}

const Coord& Rect::GetPos()
{
    return position;
}

const Coord& Rect::GetOpenGlPos()
{
    return Coord(Window::PixelToGLX(position.X), Window::PixelToGLY(position.Y));
}

void Rect::SetSize(Size size, bool render)
{
    MathSize(size);
    if (!render) {
        return;
    }

    UpdateVertices();
}

Size Rect::GetSize()
{
    return size;
}

void Rect::SetSideSize(Sides sides, bool render)
{
    const Coord& vertex1 = renderInstance->GetVertex1();
	const Coord& vertex2 = renderInstance->GetVertex2();

    if (sides.bottom != 0) {
        float glDelta = abs((float)sides.bottom / (float)Window::GetRenderResolution().GetWidth() * 2.0f);

        if (sides.bottom > 0) {
            renderInstance->SetVertexes(
                Coord(vertex1.X, vertex1.Y - glDelta),
                vertex2
            );
        }
        else {
            renderInstance->SetVertexes(
                Coord(vertex1.X, vertex1.Y + glDelta),
                vertex2
            );
        }
    }

    if (sides.top != 0) {
        float glDelta = abs((float)sides.top / (float)Window::GetRenderResolution().GetWidth() * 2.0f);

        if (sides.top > 0) {
            renderInstance->SetVertex2(
                Coord(vertex2.X, vertex2.Y + glDelta)
            );
        }
        else {
            renderInstance->SetVertex2(
                Coord(vertex2.X, vertex2.Y - glDelta)
            );
        }
    }

    if (sides.left != 0) {
        float glDelta = abs((float)sides.left / (float)Window::GetRenderResolution().GetWidth() * 2.0f);

        if (sides.left > 0) {
            renderInstance->SetVertex2(
                Coord(vertex2.X - glDelta, vertex2.Y)
            );
        }
        else {
            renderInstance->SetVertex2(
                Coord(vertex2.X + glDelta, vertex2.Y)
            );
        }
    }

    if (sides.right != 0) {
        float glDelta = abs((float)sides.right / (float)Window::GetRenderResolution().GetWidth() * 2.0f);

        if (sides.right > 0) {
            renderInstance->SetVertex1(
                Coord(vertex1.X + glDelta, vertex1.Y)
            );
        }
        else {
            renderInstance->SetVertex1(
                Coord(vertex1.X - glDelta, vertex1.Y)
            );
        }
    }

    size.SetWidth((vertex1.X - vertex2.X) * Window::GetRenderResolution().GetWidth() / 2.0f);
    size.SetHeight((vertex1.Y - vertex2.Y) * Window::GetRenderResolution().GetHeight() / 2.0f);

    position.X = Window::GLXToPixel((vertex1.X + vertex2.X) / 2.0f);
    position.Y = Window::GLYToPixel((vertex1.Y + vertex2.Y) / 2.0f);

    if (!render) {
        return;
    }

    UpdateVertices();
}

bool Rect::MouseHover(Mouse& mouse)
{
    if (mouse.IsEqual()) {
        return false;
    }

    const bool isHover = MouseInRect(mouse);

    if (isHover && OnMouseHover) {
        OnMouseHover(this, Window::GetWindow());
    }

    if (!isHover && OnMouseOver) {
        OnMouseOver(this, Window::GetWindow());
    }

    return isHover;
}

bool Rect::MouseClick(Mouse& mouse)
{
    if (!mouse.isClick() || !MouseInRect(mouse)) {
        return false;
    }

    if (OnMouseClick) {
        OnMouseClick(this, Window::GetWindow());
    }
    return true;
}

bool Rect::CollisionEnter(IGameObject& gameObject)
{
    if (!collision || collision == nullptr) {
        return false;
    }

    bool isEnter = collision->IsCollisionEnter(&gameObject);

    if (isEnter && OnCollisionEnterHandler) {
        OnCollisionEnterHandler(this, &gameObject, Window::GetWindow());
    }
}

void Rect::SetColor(Color color)
{
    this->color = color;
}

Color Rect::GetColor()
{
    return color;
}

Color Rect::GetBaseColor()
{
    return baseColor;
}

void Rect::SetPos(std::vector<Coord> vertices, bool render)
{
    MathPos(vertices[0], vertices[1]);
    if (!render) {
        return;
    }

    UpdateVertices();
}

void Rect::SetPos(Coord position, bool render)
{
    MathPos(position);
    if (!render) {
        return;
    }

    UpdateVertices();
}

void Rect::SetMaterial(std::shared_ptr<Material> material)
{
    renderInstance->SetMaterial(material);
}

std::weak_ptr<Material> Rect::GetMaterial()
{
    return renderInstance->GetMaterial();
}

void Rect::SetCollision(std::shared_ptr<ICollision> collision)
{
    this->collision = collision;
}

std::weak_ptr<ICollision> Rect::GetCollision()
{
    return collision;
}

const std::string& Rect::GetTitleString()
{
    return title;
}

std::string_view Rect::GetTitle()
{
    return title;
}

void Rect::SetTitle(std::string title)
{
    this->title = title;
}

void Rect::SetMoveDirection(Directions moveDirection)
{
    this->moveDirection = moveDirection;
}

Directions Rect::GetMoveDirection()
{
    return moveDirection;
}

const bool Rect::IsMouseOverlap()
{
    return MouseInRect(*Window::GetMouse().lock());
}

void Rect::SetLayer(Layer layer)
{
    this->layer = layer;
}

Layer Rect::GetLayer()
{
    return layer;
}

bool Rect::IsKinematic()
{
    return kinematic;
}

void Rect::SetKinematic(bool kinematic)
{
    this->kinematic = kinematic;
}

const Coord& Rect::GetDistanceTo(IGameObject& gameObject)
{
    Coord temp = gameObject.GetPos();
    return temp - position;
}

void Rect::HookMouseHover(MouseHoverHandler handler)
{
    OnMouseHover = handler;
}

void Rect::HookMouseOver(MouseHoverHandler handler)
{
    OnMouseOver = handler;
}

void Rect::HookMouseClick(MouseClickHandler handler)
{
    OnMouseClick = handler;
}

void Rect::HookOnCollisionEnter(OnCollisionEnter handler)
{
    this->OnCollisionEnterHandler = handler;
}

bool Rect::operator==(const Rect& other) const
{
    return position == other.position && 
        *renderInstance == *other.renderInstance && size == other.size &&
        color == other.color && baseColor == other.baseColor &&
        title == other.title;
}

bool Rect::operator!=(const Rect& other) const
{
    return !(*this == other);
}

Rect& Rect::operator=(const Rect&& other)
{
    if (this == &other) {
        return *this;
    }

    this->position = other.position;

    *this->renderInstance == *other.renderInstance;

    this->size = other.size;

    this->color = other.color;
    this->baseColor = other.baseColor;

    this->OnMouseHover = other.OnMouseHover;
    this->OnMouseOver = other.OnMouseOver;
    this->OnMouseClick = other.OnMouseClick;

    this->title = other.title;

    return *this;
}
