#include "Pawn.h"

void Pawn::MathPos(std::vector<Coord> vertexes)
{
	this->vertexes = vertexes;

	Coord& vertex1 = vertexes[0];
	Coord& vertex2 = vertexes[1];

	size = Size(vertex2.X - vertex1.X, vertex2.Y - vertex1.Y);

	float centerX_GL = float(vertex1.X + vertex2.X) / 2.0f;
	float centerY_GL = float(vertex1.Y + vertex2.Y) / 2.0f;

	pos = Coord(((centerX_GL + 1.0f) / 2.0f) * (float)window->GetSize().GetWidth(),
		((1.0f - (centerY_GL + 1.0f) / 2.0f) * (float)window->GetSize().GetHeight()));
}

void Pawn::MathPos(Coord& pos)
{
	this->pos = pos;

	float glCenterX = window->PixelToGLX(pos.X);
	float glCenterY = window->PixelToGLY(pos.Y);

	float glWidth = (float)(size.GetWidth()) / (float)window->GetSize().GetWidth() * 2.0f;
	float glHeight = (float)size.GetHeight() / (float)window->GetSize().GetHeight() * 2.0f;

	float halfWidth = glWidth / 2.0f;
	float halfHeight = glHeight / 2.0f;

	Coord vertex1, vertex2;

	vertex1.X = glCenterX - halfWidth;
	vertex1.Y = glCenterY - halfHeight;

	vertex2.X = glCenterX + halfWidth;
	vertex2.Y = glCenterY + halfHeight;

	vertexes = std::vector<Coord>({ vertex1, vertex2 });
}

bool Pawn::MouseInRect(Mouse& mouse)
{
	Coord& vertex1 = vertexes[0];
	Coord& vertex2 = vertexes[1];

	float normMouseX = (mouse.GetMouseCoord().X / window->GetSize().GetWidth()) * 2.0f - 1.0f;
	float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / window->GetSize().GetHeight()) * 2.0f;

	return (normMouseX >= vertex1.X && normMouseX <= vertex2.X &&
		normMouseY >= vertex1.Y && normMouseY <= vertex2.Y);
}

Pawn::Pawn(
	const char* title, Window& window,
	std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
	Coord pos, Size size, float speed, float maxSpeed, float minSpeed,
	float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
	std::vector<IAnimation*> animations
){
	this->window = &window;

	SetTitle(title);

	this->collision = collision;
	this->material = material;

	this->size = size;
	MathPos(pos);

	this->moveDirection = moveDirection;

	this->speed = speed;
	this->maxSpeed = maxSpeed;
	this->minSpeed = minSpeed;

	this->health = health;
	this->maxHealth = maxHealth;

	this->isPlayable = isPlayable;
	this->kinematic = isKinematic;
	this->isHidden = isHidden;

	SetLayer(Layer::Pawn);

	SetAction(Actions::Idle);

	this->animations.AddAnimations(animations);
}

void Pawn::SetMoveDirection(Directions moveDirection)
{
	this->moveDirection = moveDirection;
}

void Pawn::SetPos(std::vector<Coord> vertexes)
{
	MathPos(vertexes);
}

void Pawn::SetPos(Coord pos)
{
	MathPos(pos);
}

void Pawn::RotateToDirection(Directions direction)
{
}

void Pawn::SetTitle(const char* title)
{
	copyStr(title, this->title);
}

void Pawn::SetSize(Size size)
{
	this->size = size;
}

void Pawn::SetSpeed(float speed)
{
	this->speed = speed;
}

void Pawn::SetMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void Pawn::SetMinSpeed(float minSpeed)
{
	this->minSpeed = minSpeed;
}

void Pawn::SetHealth(float health)
{
	this->health = health;
}

void Pawn::SetMaxHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
}

void Pawn::SetWeight(float weight)
{
	this->weight = weight;
}

void Pawn::SetIsPlayable(bool isPlayable)
{
	this->isPlayable = isPlayable;
}

bool Pawn::IsKinematic()
{
	return kinematic;
}

void Pawn::SetKinematic(bool kinamatic)
{
	this->kinematic = kinamatic;
}

void Pawn::SetIsHidden(bool isHidden)
{
	this->isHidden = isHidden;
}

void Pawn::SetCollision(std::shared_ptr<ICollision> collision)
{
	this->collision = collision;
}

void Pawn::SetMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}

void Pawn::SetColor(Color color)
{
	material->SetDiffuse(color);
}

void Pawn::AddAnimation(IAnimation* animation)
{
	animations.AddAnimation(animation);
}

void Pawn::AddAnimations(std::vector<IAnimation*> animations)
{
	this->animations.AddAnimations(animations);
}

void Pawn::Damage(float damage)
{
	if (health <= 0) {
		return;
	}
	health -= damage;
}

void Pawn::Die()
{
	health = 0;
}

bool Pawn::MouseHover(Mouse& mouse)
{
	if (mouse.IsEqual()) {
		return false;
	}

	const bool isHover = MouseInRect(mouse);

	if (isHover && OnMouseHover) {
		OnMouseHover(this, window->GetWindow());
	}

	if (!isHover && OnMouseOver) {
		OnMouseOver(this, window->GetWindow());
	}

	return isHover;
}

bool Pawn::MouseClick(Mouse& mouse)
{
	if (!mouse.isClick() || !MouseInRect(mouse)) {
		return false;
	}

	OnMouseClick(this, window->GetWindow());
	return true;
}

bool Pawn::CollisionEnter(IGameObject& gameObject)
{
	if (!collision || collision == nullptr) {
		return false;
	}

	bool isEnter = collision->IsCollisionEnter(&gameObject);

	if (isEnter && OnCollisionEnterHandler) {
		OnCollisionEnterHandler(this, &gameObject, window->GetWindow());
	}
}

void Pawn::HookMouseHover(MouseHoverHandler onMouseHover)
{
	this->OnMouseHover = onMouseHover;
}

void Pawn::HookMouseOver(MouseHoverHandler onMouseOver)
{
	this->OnMouseOver = onMouseOver;
}

void Pawn::HookMouseClick(MouseClickHandler onMouseClick)
{
	this->OnMouseClick = onMouseClick;
}

void Pawn::HookOnCollisionEnter(OnCollisionEnter onCollisionEnter)
{
	OnCollisionEnterHandler = onCollisionEnter;
}

Window* Pawn::GetWindow()
{
	return window;
}

Coord Pawn::GetPos()
{
	return pos;
}

Coord Pawn::GetOpenGlPos()
{
	return Coord(window->PixelToGLX(pos.X), window->PixelToGLY(pos.Y));
}

std::vector<Coord> Pawn::GetVertices()
{
	return vertexes;
}

Size Pawn::GetSize()
{
	return size;
}

Color Pawn::GetColor()
{
	return material->GetDiffuse();
}

std::weak_ptr<Material> Pawn::GetMaterial()
{
	return material;
}

Directions Pawn::GetMoveDirection()
{
	return moveDirection;
}

std::weak_ptr<ICollision> Pawn::GetCollision()
{
	return collision;
}

Color Pawn::GetBaseColor()
{
	return material->GetDiffuse();
}

AnimationController Pawn::GetAnimations()
{
	return animations;
}

Layer Pawn::GetLayer()
{
	return layer;
}

void Pawn::SetLayer(Layer layer)
{
	this->layer = layer;
}

Actions Pawn::GetAction()
{
	return action;
}

void Pawn::SetAction(Actions action)
{
	this->action = action;
}

float Pawn::GetSpeed()
{
	return speed;
}

float Pawn::GetMaxSpeed()
{
	return maxSpeed;
}

float Pawn::GetMinSpeed()
{
	return minSpeed;
}

const char* Pawn::GetTitle()
{
	return title;
}

float Pawn::GetHealth()
{
	return health;
}

float Pawn::GetMaxHealth()
{
	return maxHealth;
}

float Pawn::GetWeight()
{
	return weight;
}

bool Pawn::GetIsPlayable()
{
	return isPlayable;
}

bool Pawn::GetIsHidden()
{
	return isHidden;
}

const bool Pawn::IsNear(Coord startPos, Coord targetPos, float distance)
{
	return (std::abs(startPos.X) == std::abs(targetPos.X)
		&& std::abs(startPos.Y) == std::abs(targetPos.Y)) ||
		(std::abs(startPos.X - targetPos.X) <= distance &&
			std::abs(startPos.Y - targetPos.Y) <= distance);
}

const bool Pawn::IsMouseOverlap()
{
	return MouseInRect(window->GetMouse());
}

const bool Pawn::IsDead()
{
	return health <= 0;
}
