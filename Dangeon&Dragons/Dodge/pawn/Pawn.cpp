#include "Pawn.h"
#include "../render/RectRenderInstance.h"
#include "../utilities/ptrs.h"

void Pawn::MathPos(std::vector<Coord> vertexes)
{
	Coord& vertex1 = vertexes[0];
	Coord& vertex2 = vertexes[1];

	size = Size(vertex2.X - vertex1.X, vertex2.Y - vertex1.Y);

	float centerX_GL = float(vertex1.X + vertex2.X) / 2.0f;
	float centerY_GL = float(vertex1.Y + vertex2.Y) / 2.0f;

	renderInstance->SetVertexes(vertex1, vertex2);

	position = Coord(((centerX_GL + 1.0f) / 2.0f) * (float)Window::GetRenderResolution().GetWidth(),
		((1.0f - (centerY_GL + 1.0f) / 2.0f) * (float)Window::GetRenderResolution().GetHeight()));
}

void Pawn::MathPos(Coord& position)
{
	this->position = position;

	float glCenterX = Window::PixelToGLX(position.X);
	float glCenterY = Window::PixelToGLY(position.Y);

	float glWidth = (float)(size.GetWidth()) / (float)Window::GetRenderResolution().GetWidth() * 2.0f;
	float glHeight = (float)size.GetHeight() / (float)Window::GetRenderResolution().GetHeight() * 2.0f;

	float halfWidth = glWidth / 2.0f;
	float halfHeight = glHeight / 2.0f;

	Coord vertex1, vertex2;

	vertex1.X = glCenterX - halfWidth;
	vertex1.Y = glCenterY - halfHeight;

	vertex2.X = glCenterX + halfWidth;
	vertex2.Y = glCenterY + halfHeight;

	renderInstance->SetVertexes(vertex1, vertex2);
}

void Pawn::MathSize(Size& size)
{
	this->size = size;
	MathPos(position);
}

bool Pawn::MouseInRect(Mouse& mouse)
{
	const Coord& vertex1 = renderInstance->GetVertex1();
	const Coord& vertex2 = renderInstance->GetVertex2();

	float normMouseX = (mouse.GetMouseCoord().X / Window::GetRenderResolution().GetWidth()) * 2.0f - 1.0f;
	float normMouseY = 1.0f - (mouse.GetMouseCoord().Y / Window::GetRenderResolution().GetHeight()) * 2.0f;

	return (normMouseX >= vertex1.X && normMouseX <= vertex2.X &&
		normMouseY >= vertex1.Y && normMouseY <= vertex2.Y);
}

Pawn::Pawn(
	std::string title,
	std::shared_ptr<ICollision> collision, std::shared_ptr<Material> material, Directions moveDirection,
	Coord position, Size size, float speed, float maxSpeed, float minSpeed,
	float health, float maxHealth, bool isPlayable, bool isKinematic, bool isHidden,
	std::vector<std::shared_ptr<IAnimation>> animations
){

	SetTitle(title);

	renderInstance = std::make_unique<RectRenderInstance>(std::move(material));

	this->collision = collision;

	this->size = size;
	MathPos(position);

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

void Pawn::SetPos(std::vector<Coord> vertexes, bool render)
{
	MathPos(vertexes);

	if (!render) {
		return;
	}

	UpdateVertices();
}

void Pawn::SetPos(Coord position, bool render)
{
	MathPos(position);

	if (!render) {
		return;
	}

	UpdateVertices();
}

void Pawn::RotateToDirection(Directions direction)
{
}

void Pawn::SetTitle(std::string title)
{
	this->title = title;
}

void Pawn::SetSize(Size size, bool render)
{
	MathSize(size);

	if (!render) {
		return;
	}

	UpdateVertices();
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
	renderInstance->SetMaterial(material);
}

void Pawn::SetColor(Color color)
{
	if (!ValidWeakPtr<Material>(renderInstance->GetMaterial())) {
		return;
	}

	renderInstance->GetMaterial().lock()->SetDiffuse(color);
}

void Pawn::AddAnimation(std::shared_ptr<IAnimation> animation)
{
	animations.AddAnimation(animation);
}

void Pawn::AddAnimations(std::vector<std::shared_ptr<IAnimation>> animations)
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
		OnMouseHover(this, Window::GetWindow());
	}

	if (!isHover && OnMouseOver) {
		OnMouseOver(this, Window::GetWindow());
	}

	return isHover;
}

bool Pawn::MouseClick(Mouse& mouse)
{
	if (!mouse.isClick() || !MouseInRect(mouse)) {
		return false;
	}

	OnMouseClick(this, Window::GetWindow());
	return true;
}

bool Pawn::CollisionEnter(IGameObject& gameObject)
{
	if (!collision || collision == nullptr) {
		return false;
	}

	bool isEnter = collision->IsCollisionEnter(&gameObject);

	if (isEnter && OnCollisionEnterHandler) {
		OnCollisionEnterHandler(this, &gameObject, Window::GetWindow());
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

const Coord& Pawn::GetPos()
{
	return position;
}

const Coord& Pawn::GetOpenGlPos()
{
	return Coord(Window::PixelToGLX(position.X), Window::PixelToGLY(position.Y));
}

Size Pawn::GetSize()
{
	return size;
}

Color Pawn::GetColor()
{
	return ValidWeakPtr<Material>(renderInstance->GetMaterial()) 
		? renderInstance->GetMaterial().lock()->GetDiffuse() 
		: Color();
}

std::weak_ptr<Material> Pawn::GetMaterial()
{
	return renderInstance->GetMaterial();
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
	return ValidWeakPtr<Material>(renderInstance->GetMaterial())
		? renderInstance->GetMaterial().lock()->GetDiffuse()
		: Color();
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

std::string_view Pawn::GetTitle()
{
	return title;
}

const std::string& Pawn::GetTitleString()
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
	return MouseInRect(*Window::GetMouse().lock());
}

const bool Pawn::IsDead()
{
	return health <= 0;
}
