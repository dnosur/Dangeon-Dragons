#include "Player.h"

#include <future>

#include "../../../../Dodge/raycast/Raycast.h"
#include "../../../../Dodge/raycast/RayFactory.h"

#include "../../Utilities/PlayerUtilities.h"
#include "../../../../Dodge/threads/Thread.h"
#include "../../../../Dodge/figures/Rect.h"

void Player::LoadAnimations()
{
	playerImages = std::make_unique<SlicedImage>(
		material->GetDiffuseMap().lock(),
		std::vector<int>{
			7, 7, 7, 7,
			8, 8, 8, 8,
			9, 9, 9, 9,
			6, 6, 6, 6,
			13, 13, 13, 13,
			6
		},
		21,
		Size(64, 64)
	);

	for (std::unique_ptr<VertexAnimation>& animation : playerImages->CreateVertexAnimations(
		std::make_pair(
			std::vector<std::string>({
				"idle_top",
				"idle_right",
				"idle_down",
				"idle_left",

				"spear_top",
				"spear_right",
				"spear_down",
				"spear_left",

				"walk_top",
				"walk_right",
				"walk_down",
				"walk_left",

				"dagger_top",
				"dagger_right",
				"dagger_down",
				"dagger_left",

				"bow_top",
				"bow_right",
				"bow_down",
				"bow_left",

				"die"
				}), std::vector<int>({
					//Idle
					300,
					300,
					300,
					300,

					//Spear Attack
					200,
					200,
					200,
					200,

					//Walk
					100,
					100,
					100,
					100,

					//Dagger Attack
					100,
					100,
					100,
					100,

					//Bow Attack
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

void Player::Initialize()
{
	SetLayer(Layer::MainPlayer);
	action = Actions::Idle;

	startPos = position;
	startPosVertexes[0] = vertexes[0];
	startPosVertexes[1] = vertexes[1];

	damage = 60.0f;
	damageDistance = 60.0f;

	interactiveDistance = 60.0f;

	raycastMutex = new std::mutex();

	LoadAnimations();
	LoadAudio();
}

void Player::SetSideSize(Sides sides, bool render)
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

void Player::Draw()
{
	if (!VBO && !VAO && !EBO) {
		InitializeRender();
	}

	material->Use(this);
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glPopAttrib();

	material->Disable(this);
}

void Player::Move()
{
	std::shared_ptr<Keyboard> keyboard = Window::GetKeyboard().lock();

	if (!health || !keyboard) {
		return;
	}

	{
		KeyboardKey* key = keyboard->GetKeyDown();

		if (!key || !key->pressed) {
			action = Actions::Idle;
			return;
		}
	}

	float speedBonus = keyboard->Pressed(KeyboardKeys::Shift) ? 20.0f : .0f;

	if (keyboard->Pressed(KeyboardKeys::W)) {
		moveDirection = Directions::UP;
		action = Actions::Move;

		std::future<void>(
			std::async(
				std::launch::async,
				std::bind(
					&Player::Drag,
					this,
					Coord(startPos.X, startPos.Y - (speed + speedBonus) * 0.1f)
				)
			)
		);
	}
	if (keyboard->Pressed(KeyboardKeys::S)) {
		moveDirection = Directions::DOWN;
		action = Actions::Move;

		std::future<void>(
			std::async(
				std::launch::async,
				std::bind(
					&Player::Drag,
					this,
					Coord(startPos.X, startPos.Y + (speed + speedBonus) * 0.1f)
				)
			)
		);
	}
	if (keyboard->Pressed(KeyboardKeys::A)) {
		moveDirection = Directions::LEFT;
		action = Actions::Move;

		std::future<void>(
			std::async(
				std::launch::async,
				std::bind(
					&Player::Drag,
					this,
					Coord(startPos.X - (speed + speedBonus) * 0.1f, startPos.Y)
				)
			)
		);
	}
	if (keyboard->Pressed(KeyboardKeys::D)) {
		moveDirection = Directions::RIGHT;
		action = Actions::Move;

		std::future<void>(
			std::async(
				std::launch::async,
				std::bind(
					&Player::Drag,
					this,
					Coord(startPos.X + (speed + speedBonus) * 0.1f, startPos.Y)
				)
			)
		);
	}

	if (keyboard->Pressed(KeyboardKeys::Space)) {
		action = Actions::Attack;
	}
}

void Player::Drag(Coord newPos)
{
	if (!CheckForCollision(newPos, Size(24, 24))) {
		std::cout << "Collision" << std::endl;
		return;
	}

	std::weak_ptr<Audio> weakWalk = audioController["walk-grass"];
	std::shared_ptr<Audio> walk = weakWalk.lock();

	if (walk != nullptr && walk->GetState() != AudioStates::PLAYING) {
		audioController.Play("walk-grass");
	}

	position += newPos - startPos;
}

void Player::Raycasting()
{
	std::unique_ptr<Ray> interactiveRay = std::move(
		RayFactory::CreateRay(
			std::move(std::make_unique<Coord>(startPos)),
			std::move(std::make_unique<Directions>(moveDirection)),
			interactiveDistance,
			20
		)
	);

	std::unique_ptr<Ray> damageRay = std::move(
		RayFactory::CreateRay(
			std::move(std::make_unique<Coord>(startPos)),
			std::move(std::make_unique<Directions>(moveDirection)),
			damageDistance,
			20
		)
	);

	std::weak_ptr<IGameObject> interactiveCollision = Raycast::RaycastFirst(
		std::move(interactiveRay)
	);

	std::weak_ptr<IGameObject> damageCollision = Raycast::RaycastFirst(
		std::move(damageRay)
	);

	std::shared_ptr<IGameObject> _interactiveCollision = interactiveCollision.lock();
	std::shared_ptr<IGameObject> _interactiveObject = interactiveObject.lock();

	if (_interactiveCollision != nullptr &&
		_interactiveCollision->GetLayer() != Layer::MainPlayer &&
		_interactiveCollision->GetLayer() != Layer::Enemy
	) {
		SetRaycastedObject(interactiveCollision, interactiveObject, std::make_unique<Color>(.5f, 1, .5f));
	}
	else if(_interactiveObject != nullptr) {
		_interactiveObject->GetMaterial().lock()->SetDiffuse(Color(1, 1, 1));
		interactiveObject.reset();
	}

	std::shared_ptr<IGameObject> _damageCollision = damageCollision.lock();
	std::shared_ptr<IGameObject> _damageObject = damageObject.lock();

	if (_damageCollision != nullptr &&
		_interactiveCollision->GetLayer() != Layer::MainPlayer &&
		_damageCollision->GetLayer() == Layer::Enemy
	) {
		SetRaycastedObject(damageCollision, damageObject, std::make_unique<Color>(.9f, .9f, .1f));
	}
	else if(_damageObject != nullptr) {
		_damageObject->GetMaterial().lock()->SetDiffuse(Color(1, 1, 1));
		interactiveObject.reset();
	}
}

bool Player::CheckForCollision()
{
	WindowPointer<std::vector<std::shared_ptr<IGameObject>>>* solidCollisionsObjects = WindowPointerController::GetValue<std::vector<std::shared_ptr<IGameObject>>>(
		"SolidCollisions"
	);

	if (!solidCollisionsObjects || solidCollisionsObjects->GetValue().lock()->empty()) {
		return true;
	}

	for (std::shared_ptr<IGameObject>& collisionObj : *solidCollisionsObjects->GetValue().lock()) {
		std::shared_ptr<ICollision> collision = collisionObj->GetCollision().lock();
		if (!collision) {
			continue;
		}

		std::vector<Coord> points = collision->GetPoints();

		if (collisionObj == nullptr || collision == nullptr) {
			continue;
		}

		if (collision->IsCollisionEnter(this)) {
			return false;
		}
	}

	return true;
}

bool Player::CheckForCollision(Coord position, Size size)
{
	WindowPointer<std::vector<std::shared_ptr<IGameObject>>>* solidCollisionsObjects = WindowPointerController::GetValue<std::vector<std::shared_ptr<IGameObject>>>("SolidCollisions");
	if (!solidCollisionsObjects || solidCollisionsObjects->GetValue().lock()->empty()) {
		return true;
	}

	for (std::shared_ptr<IGameObject>& collisionObj : *solidCollisionsObjects->GetValue().lock()) {
		std::shared_ptr<ICollision> collision = collisionObj->GetCollision().lock();
		if (!collision) {
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

void Player::MathSide(double& sideSize, bool isWidth)
{
	Coord& vertex1 = vertexes[0];
	Coord& vertex2 = vertexes[1];

	float glDelta = (float)sideSize / (float)Window::GetRenderResolution().GetWidth() * 2.0f;

	if (isWidth) {
		if (sideSize > 0) {
			vertex1.X += glDelta;
		}
		else {
			vertex2.X -= glDelta;
		}
	}
	else {
		if (sideSize > 0) {
			vertex1.Y += glDelta;
		}
		else {
			vertex2.Y -= glDelta;
		}
	}

	size.SetWidth((vertex1.X - vertex2.X) * Window::GetRenderResolution().GetWidth() / 2.0f);
	size.SetHeight((vertex1.Y - vertex2.Y) * Window::GetRenderResolution().GetHeight() / 2.0f);

	position.X = Window::GLXToPixel((vertex1.X + vertex2.X) / 2.0f);
	position.Y = Window::GLYToPixel((vertex1.Y + vertex2.Y) / 2.0f);
}

void Player::AIMovement()
{
}

void Player::InitializeRender()
{
	Rect::InitQuads(VAO, VBO, EBO, GetRenderVertices());
}

std::vector<float> Player::GetRenderVertices()
{
	const bool isHasDiffuseVertexs =
		material->GetDiffuseMapVerticies().size() >= 2 &&
		material->GetDiffuseMap().lock() != nullptr;

	const Coord& textCoord1 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
	const Coord& textCoord2 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

	const Coord& vertex1 = vertexes[0];
	const Coord& vertex2 = vertexes[1];

	return {
		// positions         // colors
		 (float)vertex1.X, (float)vertex1.Y, 0.0f,  (float)textCoord1.X,(float)textCoord1.Y,
		 (float)vertex2.X, (float)vertex1.Y, 0.0f,  (float)textCoord2.X,(float)textCoord1.Y,
		 (float)vertex2.X, (float)vertex2.Y, 0.0f,  (float)textCoord2.X, (float)textCoord2.Y,
		 (float)vertex1.X, (float)vertex2.Y, 0.0f,  (float)textCoord1.X, (float)textCoord2.Y
	};
}

std::string_view Player::GetAnimationName()
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

void Player::LoadAudio()
{
	std::unique_ptr<Audio> walkGrass = std::make_unique<Audio>("walk-grass", "Content/Sounds/WonderWorld/walk-grass.wav");
	walkGrass->SetVolume(0.5f);

	audioController.Load(std::move(walkGrass));
}

Player::Player(
	std::string title, std::shared_ptr<ICollision> collision,
	std::shared_ptr<Material> material, Directions moveDirection, Coord position, Size size,
	float speed, float maxSpeed, float minSpeed, 
	float health, float maxHealth, bool isPlayable, bool isKinematic, 
	bool isHidden, std::vector<std::shared_ptr<IAnimation>> animations)
	: Pawn(
		title, std::move(collision),
		std::move(material), moveDirection, position, size,
		speed, maxSpeed, minSpeed, 
		health, maxHealth, isPlayable, isKinematic, 
		isHidden, animations)
{
	Initialize();
}

Coord Player::GetStartPos()
{
	return startPos;
}

const Coord& Player::GetDistanceTo(IGameObject& gameObject)
{
	return startPos - gameObject.GetPos();
}

float Player::GetFloatDistanceTo(IGameObject& gameObject)
{
	return CalculateDistanceWithSize(
		startPos, 
		gameObject.GetPos(), 
		gameObject.GetSize()
	);
}

bool Player::IsNear(IGameObject& gameObject)
{
	return (std::abs(gameObject.GetPos().X) == std::abs(this->startPos.X)
		&& std::abs(gameObject.GetPos().Y) == std::abs(this->startPos.Y)) ||
		(std::abs(gameObject.GetPos().X - this->startPos.X) <= damageDistance &&
			std::abs(gameObject.GetPos().Y - this->startPos.Y) <= damageDistance);
}

bool Player::IsNear(Coord position)
{
	return (std::abs(position.X) == std::abs(this->startPos.X)
		&& std::abs(position.Y) == std::abs(this->startPos.Y)) ||
		(std::abs(position.X - this->startPos.X) <= damageDistance &&
			std::abs(position.Y - this->startPos.Y) <= damageDistance);
}

void Player::Update()
{
	std::unique_ptr<Thread> th = std::make_unique<Thread>("PlayerRaycast", [this]() {
		Raycasting();
	});

	if (Window::GetGameStatus() == GameStatuses::Start) {
		Move();
		animations[GetAnimationName()].lock()->Play();
	}

	Draw();

	th->Join();
}

void Player::UpdateVertices()
{
	std::vector<float> vertices = GetRenderVertices();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(unsigned int), vertices.data());
}

void Player::UpdateVertices(std::vector<float>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(unsigned int), vertices.data());
}
