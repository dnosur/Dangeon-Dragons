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
#include "../../Utilities/RaycastUtilities.h"

Skeleton::Skeleton(
	const char* title, Window& window, ICollision* collision, 
	Material* material, Directions moveDirection, Coord pos, Size size, 
	float speed, float maxSpeed, float minSpeed, float health, float maxHealth, 
	bool isPlayable, bool isKinematic, bool isHidden, std::vector<IAnimation*> animations
) : Pawn(
	title, window, collision,
	material, moveDirection, pos, size,
	speed, maxSpeed, minSpeed,
	health, maxHealth, false, isKinematic,
	isHidden, animations)
{
	Initialize();
}

Coord Skeleton::GetStartPos()
{
	return startPos;
}

Coord Skeleton::GetDistanceTo(IGameObject& gameObject)
{
	return gameObject.GetPos() - pos;
}

float Skeleton::GetFloatDistanceTo(IGameObject& gameObject)
{
	return CalculateDistanceWithSize(
		startPos, 
		gameObject.GetPos(),
		gameObject.GetSize()
	);
}

bool Skeleton::IsNear(IGameObject& gameObject)
{
	return (std::abs(gameObject.GetPos().X) == std::abs(this->pos.X)
			&& std::abs(gameObject.GetPos().Y) == std::abs(this->pos.Y)) ||
			(std::abs(gameObject.GetPos().X - this->pos.X) <= damageDistance &&
			std::abs(gameObject.GetPos().Y - this->pos.Y) <= damageDistance);
}

bool Skeleton::IsNear(Coord pos)
{
	return (std::abs(pos.X) == std::abs(this->pos.X)
			&& std::abs(pos.Y) == std::abs(this->pos.Y)) ||
			(std::abs(pos.X - this->pos.X) <= damageDistance &&
			std::abs(pos.Y - this->pos.Y) <= damageDistance);
}

void Skeleton::SetTarget(std::shared_ptr<Pawn> target)
{
	this->target = target;
	std::cout << this->target.lock().get()->GetTitle() << std::endl;
}

void Skeleton::SetTarget(std::weak_ptr<Pawn>& target)
{
	this->target = target;
}

std::weak_ptr<class Pawn> Skeleton::GetTarget()
{
	return target;
}

void Skeleton::ViewPawn(Pawn* pawn)
{
	bool upper = pawn->GetPos().Y < this->pos.Y;

	if (moveDirection == DOWN) {

	}
}

void Skeleton::SetPathOffset(Coord offset)
{
	for (int i = movementIndex; i < movements.size(); i++) {
		movements[i]->position += offset;
	}
}

void Skeleton::Update()
{
	AIMovement();
	Draw();
	//animations[GetAnimationName()]->Play();
}

void Skeleton::LoadAnimations()
{
	playerImages = new SlicedImage(
		material->GetDiffuseMap(),
		{
			9, 9, 9, 9,
			6, 6, 6, 6,
			7, 7, 7, 7,
			6
		},
		13,
		Size(64, 64)
	);

	for (VertexAnimation*& animation : playerImages->CreateVertexAnimations(
		std::make_pair(
			std::vector<const char*>({
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
		animations.AddAnimation(animation);
	}

	animations["die"]->SetStopOnEnd(true);
}

const char* Skeleton::GetAnimationName()
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

const char* Skeleton::GetAnimationMovementName(Coord direction)
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

Directions Skeleton::GetDirection(Coord direction)
{
	if (direction == Coord(1, 0)) {
		return Directions::RIGHT;
	}

	if (direction == Coord(-1, 0)) {
		return Directions::LEFT;
	}

	if (direction == Coord(0, 1)) {
		return Directions::DOWN;
	}

	if (direction == Coord(0, -1)) {
		return Directions::UP;
	}

	if (direction == Coord(1, 1)) {
		return Directions::DOWN;
	}

	if (direction == Coord(1, -1)) {
		return Directions::UP;
	}

	if (direction == Coord(-1, 1)) {
		return Directions::DOWN;
	}

	if (direction == Coord(-1, -1)) {
		return Directions::UP;
	}

	return Directions::DOWN;
}

void Skeleton::Initialize()
{
	SetLayer(Layer::Enemy);
	action = Actions::Idle;

	startPos = pos;
	startPosVertexes[0] = vertexes[0];
	startPosVertexes[1] = vertexes[1];

	damage = 5.0f;
	damageDistance = 32.0f;

	viewDistance = 300.0f;
	viewWidth = 10.0f;

	movementIndex = 0;
	offset = Coord(0, 0);

	LoadAudio();
	LoadAnimations();
}

void Skeleton::Draw()
{
	material->Use(this);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	const bool isHasDiffuseVertexs = material->GetDiffuseMapVerticies().size() >= 2 && material->GetDiffuseMap() != nullptr;
	const Coord& textCoord1 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
	const Coord& textCoord2 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

	const Coord& vertex1 = vertexes[0];
	const Coord& vertex2 = vertexes[1];

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

void Skeleton::Move()
{
}

void Skeleton::Drag(Coord newPos)
{
	Audio* walk = audioController["walk"];
	if (walk != nullptr && walk->GetState() != AudioStates::PLAYING) {
		walk->Play();
	}

	SetPos(newPos);
}

bool Skeleton::CheckForCollision(Coord position)
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

		if (collisionObj->GetCollision()->IsCollisionEnter(position, Size(24, 24))) {
			return false;
		}
	}

	return true;
}

bool Skeleton::CheckForCollision()
{
	return false;
}

void Skeleton::AIMovement()
{
	if (isDead) return;

	if (!movements.empty() && movements.size() == movementIndex) {
		movements.clear();
		action = Actions::Idle;
		animations.Play(GetAnimationName());
		movementIndex = 0;

		if (target.lock()) {
			return;
		}

		Thread* findTarget = new Thread(nullptr, [&]() {
			std::weak_ptr<Player> player = GameObjects::GetDynamicByTitle<Player>("Player");
			if (player.lock() == nullptr) {
				return;
			}

			std::unique_ptr<Ray> ray = std::move(RayFactory::CreateRay(
				new Coord(startPos),
				new Coord(player.lock()->GetStartPos())
			));

			if (ray == nullptr || ray->raySize > viewDistance) {
				ray.release();
				return;
			}
			ray.release();

			std::unique_ptr<Ray> rayToTarget = std::move(RayFactory::CreateRay(
				new Coord(startPos),
				new Coord(player.lock()->GetStartPos())
			));

			std::weak_ptr<IGameObject> target = Raycast::RaycastFirst(
				rayToTarget
			);

			if (target.lock() != player.lock()) {
				return;
			}

			std::cout << "Found player\n";
			this->SetTarget(std::dynamic_pointer_cast<Pawn>(player.lock()));
		});

		findTarget->Detach();
		return;
	}

	if (!movements.empty()) {
		Movement* movement = movements[movementIndex];

		action = movement->action;
		moveDirection = movement->direction;

		SetPos(movement->position);
		IAnimation* anim = movement->animation;

		if (anim == nullptr) {
			return;
		}

		animations.Play(anim->GetTitle());

		movement->complete = true;
		movementIndex++;
		return;
	}

	//Движение к цели
	if (!findingPath && target.lock()) {
		std::thread([this]() { 
			std::lock_guard<std::mutex> lock(pathMutex);

			std::shared_ptr<Pawn> target_ptr = target.lock();
			if (target_ptr == nullptr) {
				return;
			}

			Coord targetPos;

			if (Player* player = dynamic_cast<Player*>(target_ptr.get())) {
				targetPos = player->GetStartPos();
			}
			else {
				targetPos = target_ptr->GetPos();
			}

			std::unique_ptr<Ray> ray = RayFactory::CreateRay(&startPos, &targetPos);

			if (ray == nullptr || ray->raySize > viewDistance) {
				ray.release();
				return;
			}

			FindPath(GetPos(), targetPos);
			findingPath = false;
		}).detach();
		//std::cout << "Skeleton moving to " << target->GetTitle() << "...\n";
		return;
	}

	//Буждание
	if (!findingPath && !target.lock()) {
		std::thread([this]() {
			float wanderRadius = 100.0f;
			Coord randomPosition = GenerateRandomPosition(GetPos(), wanderRadius);

			std::lock_guard<std::mutex> lock(pathMutex);
			FindPath(GetPos(), randomPosition);
			findingPath = false;
		}).detach();
		//std::cout << "Skeleton wandering...\n";
	}

	//std::cout << "Skeleton waiting...\n";
}

Coord Skeleton::GenerateRandomPosition(Coord center, float radius)
{
	unsigned int seed = std::random_device{}();
	std::mt19937 gen(seed);
	std::uniform_real_distribution<float> distribution(0.0f, RAND_MAX);

	int num1 = distribution(gen);
	int num2 = distribution(gen);

	float angle = static_cast<float>(num1) / RAND_MAX * 2 * M_PI; // Случайный угол
	float distance = static_cast<float>(num2) / RAND_MAX * radius; // Случайное расстояние в пределах радиуса
	float offsetX = distance * cos(angle);
	float offsetY = distance * sin(angle);

	Coord randomPosition = {
		static_cast<double>(center.X + offsetX),
		static_cast<double>(center.Y + offsetY)
	};

	// Убедимся, что позиция проходима
	if (!IsWalkable(randomPosition)) {
		return GenerateRandomPosition(center, radius); // Рекурсивно ищем другую позицию
	}

	return randomPosition;
}

bool Skeleton::FindPath(Coord start, Coord goal)
{
	findingPath = true;

	//Текущий путь
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;

	//Закрытый
	std::unordered_map<int, bool> closedList;

	//Все пути
	std::unordered_map<int, float> openListCosts;

	auto GetKey = [](Coord pos) { return pos.X * 10000 + pos.Y; };

	//Начальная позиция
	Node* startNode = new Node(
		new Movement(
			GetAnimationName(),
			moveDirection,
			action,
			animations[GetAnimationName()],
			pos
		),
		0.0f, 
		std::hypot(goal.X - start.X, goal.Y - start.Y)
	);

	openList.push(startNode);
	openListCosts[GetKey(start)] = startNode->gCost;

	while (!openList.empty()) {
		Node* currentNode = openList.top();
		openList.pop();
		if (closedList[GetKey(currentNode->movement->position)]) {
			continue;
		}

		//Цель достигнута
		if (Pawn::IsNear(currentNode->movement->position, goal, damageDistance - 10)) {
			Node* node = currentNode;
			while (node != nullptr) {
				movements.push_back(node->movement);
				node = node->parent;
			}
			std::reverse(movements.begin(), movements.end());
			return true;
		}

		closedList[GetKey(currentNode->movement->position)] = true;

		//Проверяем все стороны движения
		std::vector<Movement*> neighbors = GetNeighbors(currentNode->movement->position);
		for (Movement*& neighbor : neighbors) {
			Coord& neighborPos = neighbor->position;
			int neighborKey = GetKey(neighborPos);

			if (closedList[neighborKey]) continue;

			//Рассчитываем стоимость пути до соседа
			float tentativeGCost = currentNode->gCost + std::hypot(neighborPos.X - currentNode->movement->position.X, neighborPos.Y - currentNode->movement->position.Y);

			//Ищим уже существующий более оптимальный путь
			if (openListCosts.find(neighborKey) != openListCosts.end() && 
				tentativeGCost >= openListCosts[neighborKey]) {
				continue;
			}

			Node* neighborNode = new Node(neighbor, tentativeGCost, std::hypot(goal.X - neighborPos.X, goal.Y - neighborPos.Y), currentNode);
			openList.push(neighborNode);
			openListCosts[neighborKey] = tentativeGCost;
		}
	}

	return false;
}

bool Skeleton::FindTarget()
{
	return true;
}

std::vector<Movement*> Skeleton::GetNeighbors(Coord position)
{
	std::vector<Movement*> neighbors;
	std::vector<Coord> directions = {
		{ 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, // Основные направления
		{ 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } // Диагональные направления
	};

	for (Coord& dir : directions) {
		Coord neighbor = { 
			position.X + ((speed) * 0.1f) * dir.X, 
			position.Y + ((speed) * 0.1f) * dir.Y 
		};

		if (IsWalkable(neighbor)) { // Проверяем, можно ли пройти
			//std::make_pair(GetAnimationMovementName(dir), neighbor)

			const char* title = GetAnimationMovementName(dir);
			neighbors.push_back(
				new Movement(
					title, 
					GetDirection(dir), Actions::Move,
					animations[title], neighbor
				)
			);
		}
	}

	return neighbors;
}

bool Skeleton::IsWalkable(Coord position)
{
	return CheckForCollision(position); // Ваш метод проверки препятствий
}
