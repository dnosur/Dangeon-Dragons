#pragma once

#include "../Coord.h"

#include "../IGameObject.h"

class Camera
{
	Coord position;  // Позиция камеры в пикселях
	Size size;      // Размер области видимости камеры в пикселях
	Size mapSize;   // Размер карты в пикселях

	IGameObject* observed;

	char* title;

	Window* window;

	void UpdateCamera();
public:
	Camera(const char* title, Size cameraSize, Size mapSize, Window* window);

	void Update();

	float GetPixelToGLFactorX();
	float GetPixelToGLFactorY();

	Coord GetOffset();
	void DropOffset();

    Mat4 GetViewMatrix() const;

    Mat4 GetProjectionMatrix() const;

	Coord GetPosition() const;

	void SetObservedObj(IGameObject* obj);
	IGameObject* GetObservedObj();
};

