#pragma once
#include "../animator/AnimationController.h"
#include "../collisions/ICollision.h"
#include "../Directions.h"

#include "../Material.h"

#include "../Coord.h"
#include "../Size.h"

#include "../images/SlicedImage.h"

#include "Actions.h"

#include "../render/RectRenderInstance.h"
#include "../../Content/Scripts/Characters/CharacterTypes.h"
#include "../other/Offset.h"

class Pawn : public IGameObject
{
protected:
	MouseHoverHandler OnMouseHover;
	MouseHoverHandler OnMouseOver;

	MouseClickHandler OnMouseClick;

	OnCollisionEnter OnCollisionEnterHandler;

	std::weak_ptr<Pawn> target;

	std::shared_ptr<ICollision> collision;

	Directions moveDirection;

	std::unique_ptr<RectRenderInstance> renderInstance;

	AnimationController animations;
	AudioController audioController;

	Offset offset;

	Coord startPos;
	Coord startPosVertexes[2];

	Coord position;
	Size size;

	std::unique_ptr<SlicedImage> playerImages;

	CharacterTypes characterType;

	Layer layer;

	Actions action;

	std::string title;

	float speed;
	float maxSpeed;
	float minSpeed;

	float health;
	float maxHealth;

	float weight;

	float viewWidth;

	float damage;
	float damageDistance;
	std::weak_ptr<IGameObject> damageObject;

	float viewDistance;
	float interactiveDistance;
	std::weak_ptr<IGameObject> interactiveObject;

	bool isDead;
	bool isPlayable;

	bool isHidden;

	bool kinematic;

	virtual void LoadAnimations() = 0;

	virtual void LoadAudio() = 0;
	virtual void Draw() = 0;

	void MathPos(std::vector<Coord> vertexes);
	void MathPos(Coord& position);

	void MathSize(Size& size);

	virtual void MathSide(double& sideSize, bool isWidth) = 0;

	bool MouseInRect(Mouse& mouse);

	virtual bool CheckForCollision() = 0;
	virtual bool CheckForCollision(Coord position, Size size = Size(24, 24)) = 0;

	virtual void AIMovement() = 0;

	virtual void InitializeRender() = 0;
public:
	Pawn(
		std::string title,
		CharacterTypes characterType,
		std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
		Coord position, Size size, float speed, float maxSpeed, float minSpeed, 
		float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
		std::vector<std::shared_ptr<IAnimation>> animations = {}
	);
	virtual ~Pawn() = default;

	virtual void Initialize() = 0;

	void SetMoveDirection(Directions moveDirection);

	void SetPos(std::vector<Coord> vertexes, bool render = true);
	void SetPos(Coord position, bool render = true);

	void RotateToDirection(Directions direction);

	void SetTitle(std::string title);

	void SetSize(Size size, bool render = true);

	virtual void SetSideSize(Sides sides, bool render = true) = 0;

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

	void Damage(float damage);
	void Die();

	bool MouseHover(Mouse& mouse);

	bool MouseClick(Mouse& mouse);

	bool CollisionEnter(IGameObject& gameObject);

	virtual void Update() = 0;

	virtual void UpdateVertices() = 0;

	virtual void UpdateVertices(std::vector<float>& vertices) = 0;

	void SetTarget(std::weak_ptr<Pawn> target);

	std::weak_ptr<class Pawn> GetTarget();

	void HookMouseHover(MouseHoverHandler OnMouseHover);
	void HookMouseOver(MouseHoverHandler OnMouseOver);
	void HookMouseClick(MouseClickHandler OnMouseClick);

	void HookOnCollisionEnter(OnCollisionEnter handler);
	const Coord& GetPos();

	Coord GetStartPos();

	const Coord& GetOpenGlPos();

	Size GetSize();

	Color GetColor();

	Offset& GetOffset();

	std::weak_ptr<Material> GetMaterial();
	Directions GetMoveDirection();

	std::weak_ptr<ICollision> GetCollision();

	Color GetBaseColor();

	AnimationController& GetAnimations();

	virtual std::string_view GetAnimationName() = 0;
	virtual std::string_view GetAnimationMovementName(Coord& direction) = 0;

	Layer GetLayer();
	void SetLayer(Layer layer);

	Actions GetAction();
	void SetAction(Actions action);

	bool IsKinematic();
	void SetKinematic(bool kinamatic);

	float GetSpeed();
	float GetMaxSpeed();
	float GetMinSpeed();

	float GetViewDistance();

	float GetViewWidth();

	std::string_view GetTitle();
	const std::string& GetTitleString();

	float GetHealth();
	float GetMaxHealth();

	float GetWeight();

	float GetDamageDistance();

	bool GetIsPlayable();
	bool GetIsHidden();

	virtual const Coord& GetDistanceTo(IGameObject& gameObject) = 0;
	virtual float GetFloatDistanceTo(IGameObject& gameObject) = 0;

	virtual bool IsNear(IGameObject& gameObject) = 0;
	virtual bool IsNear(Coord position) = 0;
	const bool IsNear(Coord startPos, Coord targetPos, float distance = 10.0f);

	const bool IsMouseOverlap();

	const bool IsDead();

	const bool IsWalkable(Coord& position);

	virtual const std::type_index& GetClassTypeId() = 0;
};