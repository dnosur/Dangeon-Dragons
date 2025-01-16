#pragma once

#include "../Coord.h"

#include "../IGameObject.h"

class Camera
{
	Coord position;  // ������� ������ � ��������
	Size size;      // ������ ������� ��������� ������ � ��������
	Size mapSize;   // ������ ����� � ��������

	std::shared_ptr<IGameObject> observed;

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
	std::shared_ptr<IGameObject> GetObservedObj();
};

