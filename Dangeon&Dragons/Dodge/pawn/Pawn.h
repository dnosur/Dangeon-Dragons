#pragma once
#include "../animator/SpriteAnimationController.h"
#include "../collisions/ICollision.h"
#include "../Directions.h"

#include "../Material.h"

#include "../Coord.h"
#include "../Size.h"


class Pawn : public IGameObject
{
protected:
	Window* window;

	MouseHoverHandler OnMouseHover;
	MouseHoverHandler OnMouseOver;

	MouseClickHandler OnMouseClick;

	OnCollisionEnter OnCollisionEnterHandler;

	std::vector<Coord> vertexes;
	ICollision* collision;
	Material* material;

	Directions moveDirection;

	SpriteAnimationController animations;

	Coord pos;
	Size size;

	char* title;

	float speed;
	float maxSpeed;
	float minSpeed;

	float health;
	float maxHealth;

	float weight;

	bool isDead;
	bool isPlayable;

	bool isKinematic;

	bool isHidden;

	virtual void Initialize() = 0;
	virtual void Draw() = 0;

	void MathPos(std::vector<Coord> vertexes);
	void MathPos(Coord& pos);

	bool MouseInRect(Mouse& mouse);
public:
	Pawn(
		const char* title, Window& window,
		ICollision* collision, Material* material, Directions moveDirection, 
		Coord pos, Size size, float speed, float maxSpeed, float minSpeed, 
		float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
		std::vector<SpriteAnimation> animations = {}
	);
	~Pawn() = default;

	void SetMoveDirection(Directions moveDirection);

	void SetPos(std::vector<Coord> vertexes);
	void SetPos(Coord pos);

	void RotateToDirection(Directions direction);

	void SetTitle(const char* title);

	void SetSize(Size size);

	void SetSpeed(float speed);
	void SetMaxSpeed(float maxSpeed);
	void SetMinSpeed(float minSpeed);

	void SetHealth(float health);
	void SetMaxHealth(float maxHealth);

	void SetWeight(float weight);

	void SetIsPlayable(bool isPlayable);
	void SetIsKinematic(bool isKinematic);
	void SetIsHidden(bool isHidden);

	void SetCollision(ICollision* collision);

	void SetMaterial(Material* material);

	void SetColor(Color color);

	void AddAnimation(SpriteAnimation animation);
	void AddAnimations(std::vector<SpriteAnimation> animations);

	void Damage(float damage);
	void Die();

	bool MouseHover(Mouse& mouse);

	bool MouseClick(Mouse& mouse);

	bool CollisionEnter(IGameObject& gameObject);

	virtual void Update() = 0;

	void HookMouseHover(MouseHoverHandler OnMouseHover);
	void HookMouseOver(MouseHoverHandler OnMouseOver);
	void HookMouseClick(MouseClickHandler OnMouseClick);

	void HookOnCollisionEnter(OnCollisionEnter handler);

	Window* GetWindow();

	Coord GetPos();
	std::vector<Coord> GetVertices();

	Size GetSize();

	Color GetColor();

	Material* GetMaterial();
	Directions GetMoveDirection();

	ICollision* GetCollision();

	Color GetBaseColor();

	SpriteAnimationController GetAnimations();

	float GetSpeed();
	float GetMaxSpeed();
	float GetMinSpeed();

	const char* GetTitle();

	float GetHealth();
	float GetMaxHealth();

	float GetWeight();

	bool GetIsPlayable();
	bool GetIsKinematic();
	bool GetIsHidden();

	const bool IsMouseOverlap();

	const bool IsDead();
};