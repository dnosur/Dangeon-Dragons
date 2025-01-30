#pragma once
#include "Window.h"
#include "Layers.h"

#include "collisions/ICollision.h"
#include "Sides.h"

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
	const Coord& GetPos();
	const Coord& GetOpenGlPos();

	std::vector<Coord> GetVertices();

	void SetColor(Color color);
	Color GetColor();

	void SetPos(std::vector<Coord> vertices);
	void SetPos(Coord pos);

	Directions GetMoveDirection();

	void SetMoveDirection(Directions moveDirection);

	void RotateToDirection(Directions direction);

	Color GetBaseColor();

	void SetSize(Size size);
	Size GetSize();

	void SetSideSize(Sides sides);

	void SetMaterial(std::shared_ptr<Material> material);

	std::weak_ptr<Material> GetMaterial();
	void SetCollision(std::shared_ptr<ICollision> collision);
	std::weak_ptr<ICollision> GetCollision();

	const std::string& GetTitleString();

	std::string_view GetTitle();
	void SetTitle(std::string title);

	void SetLayer(Layer layer);
	Layer GetLayer();

	bool IsKinematic();
	void SetKinematic(bool kinematic);

	const Coord& GetDistanceTo(IGameObject& gameObject);

	const bool IsMouseOverlap();

	void HookMouseHover(MouseHoverHandler handler);
	void HookMouseOver(MouseHoverHandler handler);

	void HookMouseClick(MouseClickHandler handler);

	void HookOnCollisionEnter(OnCollisionEnter handler);
};