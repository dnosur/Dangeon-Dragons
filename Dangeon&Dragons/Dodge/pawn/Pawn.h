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
	std::shared_ptr<ICollision> collision;
	std::shared_ptr<Material> material;

	Directions moveDirection;

	AnimationController animations;
	AudioController audioController;

	Coord pos;
	Size size;

	SlicedImage* playerImages;

	Layer layer;

	Actions action;

	char* title;

	float speed;
	float maxSpeed;
	float minSpeed;

	float health;
	float maxHealth;

	float weight;

	float damage;
	float damageDistance;
<<<<<<< Updated upstream
	std::shared_ptr<IGameObject> damageObject;

	float viewDistance;
	float interactiveDistance;
	std::shared_ptr<IGameObject> interactiveObject;
=======
	std::weak_ptr<IGameObject> damageObject;

	float viewDistance;
	float interactiveDistance;
	std::weak_ptr<IGameObject> interactiveObject;
>>>>>>> Stashed changes

	bool isDead;
	bool isPlayable;

	bool isHidden;

	bool kinematic;

	virtual void LoadAnimations() = 0;
	virtual const char* GetAnimationName() = 0;

	virtual void LoadAudio() = 0;

	virtual void Initialize() = 0;
	virtual void Draw() = 0;

	void MathPos(std::vector<Coord> vertexes);
	void MathPos(Coord& pos);

	bool MouseInRect(Mouse& mouse);

	virtual void AIMovement() = 0;
public:
	Pawn(
		const char* title, Window& window,
		std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
		Coord pos, Size size, float speed, float maxSpeed, float minSpeed, 
		float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
		std::vector<IAnimation*> animations = {}
	);
<<<<<<< Updated upstream
=======
	virtual ~Pawn() = default;
>>>>>>> Stashed changes

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
	void SetIsHidden(bool isHidden);

	void SetCollision(std::shared_ptr<ICollision> collision);

	void SetMaterial(std::shared_ptr<Material> material);

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

	Coord GetPos();
	Coord GetOpenGlPos();

	std::vector<Coord> GetVertices();

	Size GetSize();

	Color GetColor();

	std::weak_ptr<Material> GetMaterial();
	Directions GetMoveDirection();

	std::weak_ptr<ICollision> GetCollision();

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

	const char* GetTitle();

	float GetHealth();
	float GetMaxHealth();

	float GetWeight();

	bool GetIsPlayable();
	bool GetIsHidden();

	virtual Coord GetDistanceTo(IGameObject& gameObject) = 0;
	virtual float GetFloatDistanceTo(IGameObject& gameObject) = 0;

	virtual bool IsNear(IGameObject& gameObject) = 0;
	virtual bool IsNear(Coord pos) = 0;
	const bool IsNear(Coord startPos, Coord targetPos, float distance = 10.0f);

	const bool IsMouseOverlap();

	const bool IsDead();
};