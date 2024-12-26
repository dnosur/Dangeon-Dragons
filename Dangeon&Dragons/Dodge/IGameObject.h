#pragma once
#include <boost/container/vector.hpp>
#include <boost/container/small_vector.hpp>

#include "Window.h"
#include "Layers.h"

#include "collisions/ICollision.h"

class Material;
class CollisionsController;
enum Directions;

__interface IGameObject;
__interface ICollision;

typedef void(__stdcall* MouseHoverHandler)(IGameObject* object, GLFWwindow* window);
typedef void(__stdcall* MouseClickHandler)(IGameObject* object, GLFWwindow* window);

typedef void(__stdcall* OnCollisionEnter)(IGameObject* object, IGameObject* sender, GLFWwindow* window);

__interface IGameObject
{
	void Draw();
	void Update();

	bool MouseHover(Mouse& mouse);
	bool CollisionEnter(IGameObject& gameObject);

	Window* GetWindow();

	Coord GetPos();
	Coord GetOpenGlPos();

	boost::container::vector<Coord> GetVertices();

	void SetColor(Color color);
	Color GetColor();

	void SetPos(boost::container::vector<Coord> vertices);
	void SetPos(Coord pos);

	Directions GetMoveDirection();

	void SetMoveDirection(Directions moveDirection);

	void RotateToDirection(Directions direction);

	Color GetBaseColor();

	Size GetSize();

	void SetMaterial(Material* material);

	Material* GetMaterial();
	void SetCollision(ICollision* collision);
	ICollision* GetCollision();

	const char* GetTitle();
	void SetTitle(const char* title);

	void SetLayer(Layer layer);
	Layer GetLayer();

	bool IsKinematic();
	void SetKinematic(bool kinematic);

	Coord GetDistanceTo(IGameObject& gameObject);

	const bool IsMouseOverlap();

	void HookMouseHover(MouseHoverHandler handler);
	void HookMouseOver(MouseHoverHandler handler);

	void HookMouseClick(MouseClickHandler handler);

	void HookOnCollisionEnter(OnCollisionEnter handler);
};