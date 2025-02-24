#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Coord.h"
#include "../IGameObject.h"

class Camera
{
    Coord position;  // Позиция камеры в пикселях
    Size size;       // Размер области видимости камеры
    Size mapSize;    // Размер карты

    std::shared_ptr<IGameObject> observed;
    std::string title;

    Coord oldPos;

    void UpdateCamera();
public:
    Camera(std::string title, Size cameraSize, Size mapSize);

    void Update();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    Coord GetPosition() const;
    void SetObservedObj(std::shared_ptr<IGameObject> obj);

    const Coord& GetOldObservedPos();

    std::weak_ptr<IGameObject> GetObservedObj();
};

