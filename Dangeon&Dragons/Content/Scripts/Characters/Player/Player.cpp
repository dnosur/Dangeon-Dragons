#include "Player.h"

#include <future>

#include "../../../../Dodge/raycast/Raycast.h"
#include "../../../../Dodge/raycast/RayFactory.h"

#include "../../Utilities/PlayerUtilities.h"
#include "../../../../Dodge/threads/Thread.h"

void Player::LoadAnimations()
{
	playerImages = new SlicedImage(
		material->GetDiffuseMap(),
		{
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

	for (VertexAnimation*& animation : playerImages->CreateVertexAnimations(
		std::make_pair(
			std::vector<const char*>({
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
		animations.AddAnimation(animation);
	}

	animations["die"]->SetStopOnEnd(true);
}

void Player::Initialize()
{
	SetLayer(Layer::MainPlayer);
	action = Actions::Idle;

	startPos = pos;
	startPosVertexes[0] = vertexes[0];
	startPosVertexes[1] = vertexes[1];

	damage = 60.0f;
	damageDistance = 60.0f;

	interactiveDistance = 60.0f;

	raycastMutex = new std::mutex();

	LoadAnimations();
	LoadAudio();

	WindowPointer<Keyboard>* keyboard = WindowPointerController::GetValue<Keyboard>(window->GetWindow(), "Keyboard");
	if (keyboard != nullptr) {
		this->keyboard = &keyboard->GetValue();
	}
}

void Player::Draw()
{
	material->Use(this);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	const bool isHasDiffuseVertexs = material->GetDiffuseMapVerticies().size() >= 2 && material->GetDiffuseMap() != nullptr;
	const Coord& textCoord1 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
	const Coord& textCoord2 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

	const Coord& vertex1 = startPosVertexes[0];
	const Coord& vertex2 = startPosVertexes[1];

	float vertices[] = {
		// positions         // colors
		 vertex1.X, vertex1.Y, 0.0f,  textCoord1.X, textCoord1.Y,
		 vertex2.X, vertex1.Y, 0.0f,  textCoord2.X, textCoord1.Y,
		 vertex2.X, vertex2.Y, 0.0f,  textCoord2.X, textCoord2.Y,
		 vertex1.X, vertex2.Y, 0.0f,  textCoord1.X, textCoord2.Y
	};

	unsigned int VBO, VAO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//diffuse
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_QUADS, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glPopAttrib();
	material->Disable(this);
}

void Player::Move()
{
	if (!health) {
		return;
	}

	KeyboardKey key = keyboard->GetKey();

	if (!key.pressed) {
		action = Actions::Idle;
		return;
	}

	float speedBonus = .0f;
	bool isAttck = false;

	if (key.Pressed(KeyboardKeys::Shift)) {
		speedBonus = maxSpeed - speed;

		if (keyboard->GetLastKey(1) == nullptr) {
			return;
		}

		key = *keyboard->GetLastKey(1);
	}

	if (key.Pressed(KeyboardKeys::Space)) {
		if (action == Actions::Move) {
			if (keyboard->GetLastKey(1) == nullptr) {
				return;
			}

			key = *keyboard->GetLastKey(1);
		}

		isAttck = true;
	}


	if (key.Pressed(KeyboardKeys::W)) {
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
	else if (key.Pressed(KeyboardKeys::S)) {
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
	else if (key.Pressed(KeyboardKeys::A)) {
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
	else if (key.Pressed(KeyboardKeys::D)) {
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

	if (isAttck) {
		action = Actions::Attack;
	}
}

void Player::Drag(Coord newPos)
{
	if (!CheckForCollision(newPos, Size(24, 24))) {
		std::cout << "Collision" << std::endl;
		return;
	}

	Audio* walk = audioController["walk-grass"];
	if (walk != nullptr && walk->GetState() != AudioStates::PLAYING) {
		audioController.Play("walk-grass");
	}
	pos += newPos - startPos;
}

void Player::Raycasting()
{
	Ray* interactiveRay = RayFactory::CreateRay(
		&startPos,
		&moveDirection,
		interactiveDistance,
		20
	);

	Ray* damageRay = RayFactory::CreateRay(
		&startPos,
		&moveDirection,
		damageDistance,
		20
	);

	IGameObject* interactiveCollision = Raycast::RaycastFirst(
		interactiveRay
	);

	IGameObject* damageCollision = Raycast::RaycastFirst(
		damageRay
	);


	if (interactiveCollision != nullptr && 
		interactiveCollision->GetLayer() != Layer::MainPlayer && 
		interactiveCollision->GetLayer() != Layer::Enemy
	) {
		SetRaycastedObject(interactiveCollision, interactiveObject, new Color(.5f, 1, .5f));
	}
	else if(interactiveObject != nullptr) {
		interactiveObject->GetMaterial()->SetDiffuse(Color(1, 1, 1));
		interactiveObject = nullptr;
	}

	if (damageCollision != nullptr && 
		interactiveCollision->GetLayer() != Layer::MainPlayer && 
		damageCollision->GetLayer() == Layer::Enemy
	) {
		SetRaycastedObject(damageCollision, damageObject, new Color(.9f, .9f, .1f));
	}
	else if(damageObject != nullptr) {
		damageObject->GetMaterial()->SetDiffuse(Color(1, 1, 1));
		damageObject = nullptr;
	}
}

bool Player::CheckForCollision()
{
	WindowPointer<std::vector<IGameObject*>>* solidCollisionsObjects = WindowPointerController::GetValue<std::vector<IGameObject*>>(
		window->GetWindow(), 
		"SolidCollisions"
	);

	if (!solidCollisionsObjects || solidCollisionsObjects->GetValue().empty()) {
		return true;
	}

	for (IGameObject* collisionObj : solidCollisionsObjects->GetValue()) {
		std::vector<Coord> points = collisionObj->GetCollision()->GetPoints();

		if (collisionObj == nullptr || collisionObj->GetCollision() == nullptr) {
			continue;
		}

		if (collisionObj->GetCollision()->IsCollisionEnter(this)) {
			return false;
		}
	}

	return true;
}

bool Player::CheckForCollision(Coord pos, Size size)
{
	WindowPointer<std::vector<IGameObject*>>* solidCollisionsObjects = WindowPointerController::GetValue<std::vector<IGameObject*>>(window->GetWindow(), "SolidCollisions");
	if (!solidCollisionsObjects || solidCollisionsObjects->GetValue().empty()) {
		return true;
	}

	for (IGameObject* collisionObj : solidCollisionsObjects->GetValue()) {
		std::vector<Coord> points = collisionObj->GetCollision()->GetPoints();

		if (collisionObj == nullptr || collisionObj->GetCollision() == nullptr) {
			continue;
		}

		if (collisionObj->GetCollision()->IsCollisionEnter(pos, size)) {
			return false;
		}
	}

	return true;
}

void Player::AIMovement()
{
}

const char* Player::GetAnimationName()
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
	Audio* walkGrass = new Audio("walk-grass", "Content/Sounds/WonderWorld/walk-grass.wav");
	walkGrass->SetVolume(0.5f);

	audioController.Load(walkGrass);
}

Player::Player(
	const char* title, Window& window, ICollision* collision,
	Material* material, Directions moveDirection, Coord pos, Size size, 
	float speed, float maxSpeed, float minSpeed, 
	float health, float maxHealth, bool isPlayable, bool isKinematic, 
	bool isHidden, std::vector<IAnimation*> animations)
	: Pawn(
		title, window, collision, 
		material, moveDirection, pos, size, 
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

Coord Player::GetDistanceTo(IGameObject& gameObject)
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

bool Player::IsNear(Coord pos)
{
	return (std::abs(pos.X) == std::abs(this->startPos.X)
		&& std::abs(pos.Y) == std::abs(this->startPos.Y)) ||
		(std::abs(pos.X - this->startPos.X) <= damageDistance &&
			std::abs(pos.Y - this->startPos.Y) <= damageDistance);
}

void Player::Update()
{
	Thread* th = new Thread("PlayerRaycast", [this]() {
		Raycasting();
	});

	Move();
	Draw();

	th->Join();
	delete th;

	animations[GetAnimationName()]->Play();
}
