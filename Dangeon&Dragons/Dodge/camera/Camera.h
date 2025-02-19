#pragma once

#include "../Coord.h"

#include "../IGameObject.h"

class Camera
{
	Coord position;  // Позиция камеры в пикселях
	Size size;      // Размер области видимости камеры в пикселях
	Size mapSize;   // Размер карты в пикселях

	std::shared_ptr<IGameObject> observed;

	std::string title;

	void UpdateCamera();
public:
	Camera(std::string title, Size cameraSize, Size mapSize);

	void Update();

	float GetPixelToGLFactorX();
	float GetPixelToGLFactorY();

	Coord GetOffset();
	void DropOffset();

    Mat4 GetViewMatrix() const;

    Mat4 GetProjectionMatrix() const;

	Coord GetPosition() const;

	void SetObservedObj(std::shared_ptr<IGameObject> obj);
	std::weak_ptr<IGameObject> GetObservedObj();
};

