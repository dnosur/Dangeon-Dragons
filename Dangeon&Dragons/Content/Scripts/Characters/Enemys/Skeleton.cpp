#include "Skeleton.h"
#include "../../AI/Node.h"
#include "../Player/Player.h"

#include <queue>
#include <math.h>
#include <corecrt_math_defines.h>
#include <random>

#include "../../../../Dodge/threads/Thread.h"
#include "../../../../Dodge/GameObjects.h"
#include "../../../../Dodge/raycast/Raycast.h"
#include "../../../../Dodge/raycast/RayFactory.h"
#include "../../../../Dodge/figures/Rect.h"
#include "../../../../Dodge/utilities/ptrs.h"

#include "../../Utilities/RaycastUtilities.h"
#include "../../AI/Algorithms/WanderContext.h"

Skeleton::Skeleton(
	std::string title, std::shared_ptr<ICollision> collision,
	std::shared_ptr<Material> material, Directions moveDirection, Coord position, Size size,
	float speed, float maxSpeed, float minSpeed, float health, float maxHealth,
	bool isPlayable, bool isKinematic, bool isHidden, std::vector<std::shared_ptr<IAnimation>> animations
) : Pawn(
	title, CharacterTypes::Monster, std::move(collision),
	std::move(material), moveDirection, position, size,
	speed, maxSpeed, minSpeed,
	health, maxHealth, false, isKinematic,
	isHidden, animations)
{
	Initialize();
}

const Coord& Skeleton::GetDistanceTo(IGameObject& gameObject)
{
	Coord temp = gameObject.GetPos();
	return temp - position;
}

float Skeleton::GetFloatDistanceTo(IGameObject& gameObject)
{
	return CalculateDistanceWithSize(
		position,
		gameObject.GetPos(),
		gameObject.GetSize()
	);
}

bool Skeleton::IsNear(IGameObject& gameObject)
{
	return (std::abs(gameObject.GetPos().X) == std::abs(this->position.X)
			&& std::abs(gameObject.GetPos().Y) == std::abs(this->position.Y)) ||
			(std::abs(gameObject.GetPos().X - this->position.X) <= damageDistance &&
			std::abs(gameObject.GetPos().Y - this->position.Y) <= damageDistance);
}

bool Skeleton::IsNear(Coord position)
{
	return (std::abs(position.X) == std::abs(this->position.X)
			&& std::abs(position.Y) == std::abs(this->position.Y)) ||
			(std::abs(position.X - this->position.X) <= damageDistance &&
			std::abs(position.Y - this->position.Y) <= damageDistance);
}

void Skeleton::ViewPawn(class Pawn* pawn)
{
	bool upper = pawn->GetPos().Y < this->position.Y;

	if (moveDirection == DOWN) {

	}
}

void Skeleton::Update()
{
	if (Window::GetGameStatus() == GameStatuses::Start) {
		AIMovement();
	}

	Draw();
	//animations[GetAnimationName()]->Play();
}

void Skeleton::UpdateVertices()
{
	renderInstance->UpdateVertices();
}

void Skeleton::UpdateVertices(std::vector<float>& vertices)
{
	renderInstance->UpdateVertices(vertices);
}

const std::type_index& Skeleton::GetClassTypeId()
{
	return typeid(this);
}

void Skeleton::LoadAnimations()
{
	if (!ValidWeakPtr<Material>(renderInstance->GetMaterial())) {
		return;
	}

	playerImages = std::make_unique<SlicedImage>(
		renderInstance->GetMaterial().lock()->GetDiffuseMap().lock(),
		std::vector<int>{
			9, 9, 9, 9,
			6, 6, 6, 6,
			7, 7, 7, 7,
			6
		},
		13,
		Size(64, 64)
	);

	for (std::unique_ptr<VertexAnimation>& animation : playerImages->CreateVertexAnimations(
		std::make_pair(
			std::vector<std::string>({
				"walk_top",
				"walk_right",
				"walk_down",
				"walk_left",

				"dagger_top",
				"dagger_right",
				"dagger_down",
				"dagger_left",

				"idle_top",
				"idle_right",
				"idle_down",
				"idle_left",

				"die"
				}), std::vector<int>({
					//Walk
					300,
					300,
					300,
					300,

					//Dagger
					100,
					100,
					100,
					100,

					//Idle
					200,
					200,
					200,
					200,

					//Die
					100
				})
		))
		)
	{
		animation->SetGameObject(this);
		animations.AddAnimation(std::move(animation));
	}

	animations["die"].lock()->SetStopOnEnd(true);
}

std::string_view Skeleton::GetAnimationName()
{
	if (action == Actions::Dead) {
		return "die";
	}

	if (action == Actions::Idle) {
		if (moveDirection == Directions::UP) {
			return "idle_top";
		}

		if (moveDirection == Directions::LEFT) {
			return "idle_left";
		}

		if (moveDirection == Directions::DOWN) {
			return "idle_down";
		}

		if (moveDirection == Directions::RIGHT) {
			return "idle_right";
		}
	}

	if (action == Actions::Move) {
		if (moveDirection == Directions::UP) {
			return "walk_top";
		}

		if (moveDirection == Directions::LEFT) {
			return "walk_left";
		}

		if (moveDirection == Directions::DOWN) {
			return "walk_down";
		}

		if (moveDirection == Directions::RIGHT) {
			return "walk_right";
		}
	}

	if (action == Actions::Attack) {
		if (moveDirection == Directions::UP) {
			return "dagger_top";
		}

		if (moveDirection == Directions::LEFT) {
			return "dagger_left";
		}

		if (moveDirection == Directions::DOWN) {
			return "dagger_down";
		}

		if (moveDirection == Directions::RIGHT) {
			return "dagger_right";
		}
	}

	return "idle_down";
}

std::string_view Skeleton::GetAnimationMovementName(Coord& direction)
{
	if (direction == Coord(1, 0)) {
		return "walk_right";
	}

	if (direction == Coord(-1, 0)) {
		return "walk_left";
	}

	if (direction == Coord(0, 1)) {
		return "walk_down";
	}

	if (direction == Coord(0, -1)) {
		return "walk_top";
	}

	if (direction == Coord(1, 1)) {
		return "walk_down";
	}

	if (direction == Coord(1, -1)) {
		return "walk_top";
	}

	if (direction == Coord(-1, 1)) {
		return "walk_down";
	}

	if (direction == Coord(-1, -1)) {
		return "walk_top";
	}

	return "walk_down";
}

void Skeleton::LoadAudio()
{
	//Audio walk = Audio("walk", "Content/Audio/Enemies/Skeleton/walk.wav");
	//Audio attack = Audio("Content/Audio/Enemies/Skeleton/attack.wav");
	//Audio die = Audio("Content/Audio/Enemies/Skeleton/die.wav");
	//Audio hurt = Audio("Content/Audio/Enemies/Skeleton/hurt.wav");

	audioController.Load("walk", "Content/Sounds/Skeleton/skeleton-walk.wav");
}

void Skeleton::Initialize()
{
	SetLayer(Layer::Enemy);
	action = Actions::Idle;

	startPos = position;
	startPosVertexes[0] = renderInstance->GetVertex1();
	startPosVertexes[1] = renderInstance->GetVertex2();

	damage = 5.0f;
	damageDistance = 32.0f;

	viewDistance = 300.0f;
	viewWidth = 10.0f;

	aiContext = std::make_unique<AIContext>(
		std::make_unique<WanderContext>()
	);

	LoadAudio();
	LoadAnimations();
}

void Skeleton::SetSideSize(Sides sides, bool render)
{
	if (sides.bottom != 0) {
		MathSide(sides.bottom, false);
	}

	if (sides.top != 0) {
		MathSide(sides.top, false);
	}

	if (sides.left != 0) {
		MathSide(sides.left, true);
	}

	if (sides.right != 0) {
		MathSide(sides.right, true);
	}

	if (!render) {
		return;
	}

	UpdateVertices();
}

void Skeleton::Draw()
{
	renderInstance->Render();
}

void Skeleton::Move()
{
}

void Skeleton::Drag(Coord newPos)
{
	std::weak_ptr<Audio> weakWalk = audioController["walk"];
	std::shared_ptr<Audio> walk = weakWalk.lock();
	if (walk == nullptr) return;

	if (walk != nullptr && walk->GetState() != AudioStates::PLAYING) {
		walk->Play();
	}

	SetPos(newPos);
}

bool Skeleton::CheckForCollision(Coord position, Size size)
{
	WindowPointer<std::vector<std::shared_ptr<IGameObject>>>* solidCollisionsObjects = WindowPointerController::GetValue<std::vector<std::shared_ptr<IGameObject>>>("SolidCollisions");
	if (!solidCollisionsObjects || solidCollisionsObjects->GetValue().lock()->empty()) {
		return true;
	}

	for (std::shared_ptr<IGameObject>& collisionObj : *solidCollisionsObjects->GetValue().lock()) {
		std::shared_ptr<ICollision> collision = collisionObj->GetCollision().lock();
		if (collision == nullptr) {
			continue;
		}

		std::vector<Coord> points = collision->GetPoints();

		if (collisionObj == nullptr || collision == nullptr) {
			continue;
		}

		if (collision->IsCollisionEnter(position, size)) {
			return false;
		}
	}

	return true;
}

bool Skeleton::CheckForCollision()
{
	return false;
}

void Skeleton::MathSide(double& sideSize, bool isWidth)
{
	const Coord& vertex1 = renderInstance->GetVertex1();
	const Coord& vertex2 = renderInstance->GetVertex2();

	float glDelta = (float)sideSize / (float)Window::GetRenderResolution().GetWidth() * 2.0f;

	if (isWidth) {
		if (sideSize > 0) {
			renderInstance->SetVertex1(
				Coord(vertex1.X + glDelta, vertex1.Y)
			);
		}
		else {
			renderInstance->SetVertex2(
				Coord(vertex2.X - glDelta, vertex2.Y)
			);
		}
	}
	else {
		if (sideSize > 0) {
			renderInstance->SetVertex1(
				Coord(vertex1.X + glDelta, vertex1.Y)
			);
		}
		else {
			renderInstance->SetVertex2(
				Coord(vertex2.X, vertex2.Y - glDelta)
			);
		}
	}

	size.SetWidth((vertex1.X - vertex2.X) * Window::GetRenderResolution().GetWidth() / 2.0f);
	size.SetHeight((vertex1.Y - vertex2.Y) * Window::GetRenderResolution().GetHeight() / 2.0f);

	position.X = Window::GLXToPixel((vertex1.X + vertex2.X) / 2.0f);
	position.Y = Window::GLYToPixel((vertex1.Y + vertex2.Y) / 2.0f);
}

void Skeleton::AIMovement()
{
	aiContext->Invoke(this, aiContext.get());
}

void Skeleton::InitializeRender()
{
	renderInstance->Initialize();
}
