#include "Rect.h"
#include "../shaders/ShadersController.h"

std::vector<unsigned int> defaultIndicies = {
    0, 1, 2,
    2, 3, 0
};

bool Rect::MouseInRect(Mouse& mouse)
{
    float normMouseX = (mouse.GetMouseCoord().X / window->GetRenderResolution().GetWidth()) * 2.0f - 1.0f;
    float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / window->GetRenderResolution().GetHeight()) * 2.0f;

    return (normMouseX >= vertex1.X && normMouseX <= vertex2.X &&
        normMouseY >= vertex1.Y && normMouseY <= vertex2.Y);
}

void Rect::MathPos(Coord& vertex1, Coord& vertex2)
{
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;

    float width = (vertex2.X - vertex1.X) * (window->GetRenderResolution().GetWidth() / 2.0f);
    float height = (vertex2.Y - vertex1.Y) * (window->GetRenderResolution().GetHeight() / 2.0f);

    // ������ ������������ �� ������ ������� ���������
    size = Size(round(std::abs(width)), round(std::abs(height)));

    // ������� ����� � OpenGL-�����������
    float centerX_GL = (vertex1.X + vertex2.X) / 2.0f;
    float centerY_GL = (vertex1.Y + vertex2.Y) / 2.0f;

    // ����������� OpenGL-���������� � �������
    pos = Coord(
        ((centerX_GL + 1.0f) / 2.0f) * (float)window->GetRenderResolution().GetWidth(),
        ((1.0f - (centerY_GL + 1.0f) / 2.0f) * (float)window->GetRenderResolution().GetHeight())
    );
}

void Rect::MathPos(Coord& pos)
{
    this->pos = pos;
    float glCenterX = window->PixelToGLX(pos.X);
    float glCenterY = window->PixelToGLY(pos.Y);

    float glWidth = (float)size.GetWidth() / (float)window->GetRenderResolution().GetWidth() * 2.0f;
    float glHeight = (float)size.GetHeight() / (float)window->GetRenderResolution().GetHeight() * 2.0f;

    // Calculate the vertex1 and vertex2 coordinates
    vertex2.X = glCenterX - glWidth / 2.0f;
    vertex1.Y = glCenterY - glHeight / 2.0f;
    vertex1.X = glCenterX + glWidth / 2.0f;
    vertex2.Y = glCenterY + glHeight / 2.0f;
}

void Rect::MathSize(Size& size)
{
    this->size = size;
    MathPos(pos);
}

void Rect::MathSide(double& sideSize, bool isWidth)
{


}

Rect::Rect()
{
    title = (char*)"Undefined";
    window = NULL;

    collision = nullptr;
    material = nullptr;

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    kinematic = false;
    this->layer = Layer::Undefined;

    moveDirection = Directions::DOWN;

    VAO = VBO = EBO = 0;
}

Rect::Rect(
    std::string title,
    Window& window, Coord
    pos, Size size, Color color, 
    Directions moveDirection
)
{
    this->title = title;

    this->window = &window;
    this->size = size;
    this->color = baseColor = color;

    MathPos(pos);

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    material = std::make_unique<BaseFigureMaterial>();
    material->SetShader(
        ShadersController::GetShaderID("BaseFigure")
    );

    material->SetDiffuse(color);
    material->SetDiffuseMap(ImagesController::GetDafaultImage().lock());

    this->moveDirection = moveDirection;

    kinematic = false;
    this->layer = Layer::GameObject;

    collision = nullptr;

    VAO = VBO = EBO = 0;
}

Rect::Rect(
    std::string title, 
    Window& window, 
    Coord vertex1, Coord vertex2, 
    Color color, Directions moveDirection
)
{
    this->title = title;

    this->window = &window;
    this->color = baseColor = color;

    MathPos(vertex1, vertex2);

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    material = std::make_unique<BaseFigureMaterial>();
    material->SetShader(
        ShadersController::GetShaderID("BaseFigure")
    );

    this->moveDirection = moveDirection;

    kinematic = false;
    this->layer = Layer::GameObject;

    collision = nullptr;

    VAO = VBO = EBO = 0;
}

Rect::Rect(
    std::string title, 
    Window& window, 
    Coord vertex1, Coord vertex2, 
    Coord textureVertex1, Coord textureVertex2, 
    Color color, Directions moveDirection
)
{
    this->title = title;

    this->window = &window;
    this->color = baseColor = color;

    MathPos(vertex1, vertex2);

    OnMouseHover = OnMouseOver = nullptr;
    OnCollisionEnterHandler = nullptr;
    OnMouseClick = nullptr;

    material = std::make_unique<BaseFigureMaterial>();
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

    VAO = VBO = EBO = 0;
}

void Rect::InitQuads(
    unsigned int& VAO, unsigned int& VBO, unsigned int& EBO,
    std::vector<float> vertices, std::vector<unsigned int>& indices
) {
    if (VAO || VBO || EBO) {
        return;
    }

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // Передаём данные вершин в OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Передаём индексы вершин в OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Определяем атрибуты вершин
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Атрибут текстурных координат
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Rect::Update()
{
    Draw();
}

void Rect::Draw()
{
    //glPushAttrib(GL_ALL_ATTRIB_BITS);

    if (!VBO && !VAO && !EBO) {
        InitializeRender();
	}

    material->Use(this);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glPopAttrib();

    material->Disable(this);
}

void Rect::UpdateVertices()
{
    std::vector<float> vertices = GetRenderVertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(unsigned int), vertices.data());
}

void Rect::UpdateVertices(std::vector<float> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(unsigned int), vertices.data());
}

void Rect::InitializeRender()
{
    InitQuads(VAO, VBO, EBO, GetRenderVertices());
}

std::vector<float> Rect::GetRenderVertices()
{
    const bool isHasDiffuseVertexs =
        material->GetDiffuseMapVerticies().size() >= 2 &&
        material->GetDiffuseMap().lock() != nullptr;
    const Coord& textCoord1 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
    const Coord& textCoord2 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

    return {
        // positions         // colors
         (float)vertex1.X, (float)vertex1.Y, 0.0f,  (float)textCoord1.X,(float)textCoord1.Y,
         (float)vertex2.X, (float)vertex1.Y, 0.0f, (float)textCoord2.X, (float)textCoord1.Y,
         (float)vertex2.X, (float)vertex2.Y, 0.0f,  (float)textCoord2.X,(float)textCoord2.Y,
         (float)vertex1.X, (float)vertex2.Y, 0.0f,  (float)textCoord1.X, (float)textCoord2.Y
    };
}

std::vector<float> Rect::GetVerticesByDirection(Rect& rect, Directions moveDirection, bool returnTexCoords)
{
    Coord vertex1 = rect.GetVertices()[0];
    Coord vertex2 = rect.GetVertices()[1];

    const bool isHasDiffuseVertexs = 
        rect.material->GetDiffuseMapVerticies().size() >= 2 && 
        rect.material->GetDiffuseMap().lock() != nullptr;
    const Coord& textCoord1 = isHasDiffuseVertexs ? rect.material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
    const Coord& textCoord2 = isHasDiffuseVertexs ? rect.material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

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

    // ��������� �����������
    moveDirection = direction;
}

const Coord& Rect::GetPos()
{
    return pos;
}

const Coord& Rect::GetOpenGlPos()
{
    return Coord(window->PixelToGLX(pos.X), window->PixelToGLY(pos.Y));
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
    if (sides.bottom != 0) {
        float glDelta = abs((float)sides.bottom / (float)window->GetRenderResolution().GetWidth() * 2.0f);

        if (sides.bottom > 0) {
            vertex1.Y -= glDelta;
        }
        else {
            vertex1.Y += glDelta;
        }
    }

    if (sides.top != 0) {
        float glDelta = abs((float)sides.top / (float)window->GetRenderResolution().GetWidth() * 2.0f);

        if (sides.top > 0) {
            vertex2.Y += glDelta;
        }
        else {
            vertex2.Y -= glDelta;
        }
    }

    if (sides.left != 0) {
        float glDelta = abs((float)sides.left / (float)window->GetRenderResolution().GetWidth() * 2.0f);

        if (sides.left > 0) {
            vertex2.X -= glDelta;
        }
        else {
            vertex2.X += glDelta;
        }
    }

    if (sides.right != 0) {
        float glDelta = abs((float)sides.right / (float)window->GetRenderResolution().GetWidth() * 2.0f);

        if (sides.right > 0) {
            vertex1.X += glDelta;
        }
        else {
            vertex1.X -= glDelta;
        }
    }

    size.SetWidth((vertex1.X - vertex2.X) * window->GetRenderResolution().GetWidth() / 2.0f);
    size.SetHeight((vertex1.Y - vertex2.Y) * window->GetRenderResolution().GetHeight() / 2.0f);

    pos.X = window->GLXToPixel((vertex1.X + vertex2.X) / 2.0f);
    pos.Y = window->GLYToPixel((vertex1.Y + vertex2.Y) / 2.0f);

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
        OnMouseHover(this, window->GetWindow());
    }

    if (!isHover && OnMouseOver) {
        OnMouseOver(this, window->GetWindow());
    }

    return isHover;
}

bool Rect::MouseClick(Mouse& mouse)
{
    if (!mouse.isClick() || !MouseInRect(mouse)) {
        return false;
    }

    if (OnMouseClick) {
        OnMouseClick(this, window->GetWindow());
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
        OnCollisionEnterHandler(this, &gameObject, window->GetWindow());
    }
}

Window* Rect::GetWindow()
{
    return window;
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

std::vector<Coord> Rect::GetVertices()
{
    return { vertex1, vertex2 };
}

void Rect::SetPos(std::vector<Coord> vertices, bool render)
{
    MathPos(vertices[0], vertices[1]);
    if (!render) {
        return;
    }

    UpdateVertices();
}

void Rect::SetPos(Coord pos, bool render)
{
    MathPos(pos);
    if (!render) {
        return;
    }

    UpdateVertices();
}

void Rect::SetMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}

std::weak_ptr<Material> Rect::GetMaterial()
{
    return material;
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
    return MouseInRect(*window->GetMouse().lock());
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
    return temp - pos;
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
    return window == other.window && pos == other.pos && 
        vertex1 == other.vertex1 && vertex2 == other.vertex2 && size == other.size &&
        color == other.color && baseColor == other.baseColor && material == other.material &&
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

    this->window = other.window;
    this->pos = other.pos;

    this->vertex1 = other.vertex1;
    this->vertex2 = other.vertex2;

    this->size = other.size;

    this->color = other.color;
    this->baseColor = other.baseColor;

    this->OnMouseHover = other.OnMouseHover;
    this->OnMouseOver = other.OnMouseOver;
    this->OnMouseClick = other.OnMouseClick;

    material = other.material;

    this->title = other.title;

    return *this;
}
