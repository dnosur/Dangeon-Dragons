#include "Camera.h"

#include "../functions.h"

#include "../Material.h"


void Camera::UpdateCamera()
{
    if (!observed) return;

    // �������� ������� ������� (������) � ��������
    Coord playerPosition = observed->GetPos();

    // ���������� ������ ������������ ������
    position = playerPosition - Coord(size.width / 2.0, size.height / 2.0);

    // ������������ �������� ������ ��������� �����
    position.X = Max<double>(0.0, Min<double>(position.X, mapSize.width - size.width));
    position.Y = Max<double>(0.0, Min<double>(position.Y, mapSize.height - size.height));

    // �������
    std::cout << "Player: " << playerPosition.X << " " << playerPosition.Y << std::endl;
    std::cout << "Camera Position (pixels): " << position.X << ", " << position.Y << std::endl;
}

float Camera::GetPixelToGLFactorX()
{
    return 2.0f / window->GetRenderResolution().width;
}

float Camera::GetPixelToGLFactorY()
{
    return 2.0f / window->GetRenderResolution().height;
}

Coord Camera::GetOffset()
{
    if (!observed) return Coord(0.0f, 0.0f);

    return position - observed->GetPos();
}

void Camera::DropOffset()
{
    position = observed->GetPos();
}

Camera::Camera(std::string title, Size cameraSize, Size mapSize, Window* window)
    : size(cameraSize), mapSize(mapSize), window(window), observed(nullptr), title(title) 
{
}

void Camera::Update()
{
    UpdateCamera();
}


Mat4 Camera::GetViewMatrix() const {
    // ������� ����: ����� ����� ������������ ������� ������
    return Mat4::Translate(Vec2(-position.X, -position.Y));
}

Mat4 Camera::GetProjectionMatrix() const {
    // ��������������� ��������
    return Mat4::Ortho(0.0f, size.width, size.height, 0.0f);
}

Coord Camera::GetPosition() const
{
    return Coord(position.X, position.Y);
}

void Camera::SetObservedObj(std::shared_ptr<IGameObject> obj)
{
    this->observed = obj;
    position = this->observed->GetPos();
}

std::weak_ptr<IGameObject> Camera::GetObservedObj()
{
    return observed;
}
