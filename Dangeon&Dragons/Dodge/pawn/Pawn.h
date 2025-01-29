#pragma once
#include "../animator/AnimationController.h"
#include "../collisions/ICollision.h"
#include "../Directions.h"

#include "../Material.h"

#include "../Coord.h"
#include "../Size.h"

#include "../images/SlicedImage.h"

#include "Actions.h"

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

	AnimationController animations;
	AudioController audioController;

	Coord pos;
	Size size;

	SlicedImage* playerImages;

	Layer layer;

	Actions action;

	std::string title;

	float speed;
	float maxSpeed;
	float minSpeed;

	float health;
	float maxHealth;

	float weight;

	float damage;
	float damageDistance;
	IGameObject* damageObject;

	float viewDistance;
	float interactiveDistance;
	IGameObject* interactiveObject;

	bool isDead;
	bool isPlayable;

	bool isHidden;

	bool kinematic;

	virtual void LoadAnimations() = 0;
	virtual std::string_view GetAnimationName() = 0;

	virtual void LoadAudio() = 0;

	virtual void Initialize() = 0;
	virtual void Draw() = 0;

	void MathPos(std::vector<Coord> vertexes);
	void MathPos(Coord& pos);

	bool MouseInRect(Mouse& mouse);

	virtual void AIMovement() = 0;
public:
	Pawn(
<<<<<<< Updated upstream
		const char* title, Window& window,
		ICollision* collision, Material* material, Directions moveDirection, 
=======
		std::string title, Window& window,
		std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
>>>>>>> Stashed changes
		Coord pos, Size size, float speed, float maxSpeed, float minSpeed, 
		float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
		std::vector<IAnimation*> animations = {}
	);
	~Pawn() = default;

	void SetMoveDirection(Directions moveDirection);

	void SetPos(std::vector<Coord> vertexes);
	void SetPos(Coord pos);

	void RotateToDirection(Directions direction);

	void SetTitle(std::string title);

	void SetSize(Size size);

	void SetSpeed(float speed);
	void SetMaxSpeed(float maxSpeed);
	void SetMinSpeed(float minSpeed);

	void SetHealth(float health);
	void SetMaxHealth(float maxHealth);

	void SetWeight(float weight);

	void SetIsPlayable(bool isPlayable);
	void SetIsHidden(bool isHidden);

	void SetCollision(ICollision* collision);

	void SetMaterial(Material* material);

	void SetColor(Color color);

	void AddAnimation(IAnimation* animation);
	void AddAnimations(std::vector<IAnimation*> animations);

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
	const Coord& GetPos();

	const Coord& GetOpenGlPos();

	std::vector<Coord> GetVertices();

	Size GetSize();

	Color GetColor();

	Material* GetMaterial();
	Directions GetMoveDirection();

	ICollision* GetCollision();

	Color GetBaseColor();

	AnimationController GetAnimations();

	Layer GetLayer();
	void SetLayer(Layer layer);

	Actions GetAction();
	void SetAction(Actions action);

	bool IsKinematic();
	void SetKinematic(bool kinamatic);

	float GetSpeed();
	float GetMaxSpeed();
	float GetMinSpeed();

	std::string_view GetTitle();

	float GetHealth();
	float GetMaxHealth();

	float GetWeight();

	bool GetIsPlayable();
	bool GetIsHidden();

	virtual const Coord& GetDistanceTo(IGameObject& gameObject) = 0;
	virtual float GetFloatDistanceTo(IGameObject& gameObject) = 0;

	virtual bool IsNear(IGameObject& gameObject) = 0;
	virtual bool IsNear(Coord pos) = 0;
	const bool IsNear(Coord startPos, Coord targetPos, float distance = 10.0f);

	const bool IsMouseOverlap();

	const bool IsDead();
};