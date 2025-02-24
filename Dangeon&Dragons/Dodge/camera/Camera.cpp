#include "Camera.h"

#include "../functions.h"

#include "../Material.h"


Camera::Camera(std::string title, Size cameraSize, Size mapSize)
    : size(cameraSize), mapSize(mapSize), observed(nullptr), title(title), oldPos(Coord(0, 0))
{
}

void Camera::UpdateCamera()
{
    if (!observed) return;

    // 🔹 Получаем позицию игрока
    Coord playerPosition = observed->GetPos();

    // 🔹 Получаем размеры игрока
    double playerWidth = observed->GetSize().GetWidth();
    double playerHeight = observed->GetSize().GetHeight();

    // 🔹 Корректируем центр игрока (сместим позицию в центр его спрайта)
    double centeredX = playerPosition.X + playerWidth / 2.0;
    double centeredY = playerPosition.Y + playerHeight / 2.0 + Window::GetRenderResolution().GetHeight();

    // 🔹 Центрируем камеру на центре игрока
    position = Coord(centeredX - size.width / 2.0, centeredY - size.height / 2.0);

    // 🔹 Ограничиваем границы, чтобы камера не выходила за карту
    position.X = Window::PixelToGLX(Min<double>(position.X, mapSize.width - size.width));
    position.Y = Window::PixelToGLY(Min<double>(position.Y, mapSize.height - size.height));

    oldPos = playerPosition;

    std::cout << "Player pos: " << playerPosition.X << ", " << playerPosition.Y << std::endl;
    std::cout << "Camera pos GL: " << position.X << ", " << position.Y << std::endl;
}


void Camera::Update()
{
    if (oldPos != observed->GetPos()) {
        UpdateCamera();
    }
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position.X, -position.Y, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix() const {
    float left = 0.0f;
    float right = static_cast<float>(size.width);
    float bottom = static_cast<float>(size.height);
    float top = 0.0f;

    // Переводим пиксели в OpenGL-координаты от -1 до 1
    float scaleX = 2.0f / (right - left);
    float scaleY = 2.0f / (bottom - top);

    // Используем ортографическую проекцию, но с нормализацией в OpenGL координаты
    glm::mat4 projection = glm::ortho(left * scaleX, right * scaleX, top * scaleY, bottom * scaleY, -1.0f, 1.0f);

    return projection;
}

Coord Camera::GetPosition() const
{
    return position;
}

void Camera::SetObservedObj(std::shared_ptr<IGameObject> obj)
{
    observed = obj;
    position = observed->GetPos();
}

const Coord& Camera::GetOldObservedPos()
{
    return oldPos;
}

std::weak_ptr<IGameObject> Camera::GetObservedObj()
{
    return observed;
}