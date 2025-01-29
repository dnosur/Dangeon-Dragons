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
	std::string title, Window& window, std::shared_ptr<ICollision> collision,
	std::shared_ptr<Material> material, Directions moveDirection, Coord pos, Size size,
	float speed, float maxSpeed, float minSpeed, float health, float maxHealth,
	bool isPlayable, bool isKinematic, bool isHidden, std::vector<std::shared_ptr<IAnimation>> animations
) : Pawn(
	title, window, std::move(collision),
	std::move(material), moveDirection, pos, size,
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

const Coord& Skeleton::GetDistanceTo(IGameObject& gameObject)
{
	Coord temp = gameObject.GetPos();
	return temp - pos;
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

void Skeleton::SetTarget(std::weak_ptr<Pawn> target)
{
	this->target = target;
}

class std::weak_ptr<class Pawn> Skeleton::GetTarget()
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
};

void Skeleton::LoadAnimations()
{
	std::unique_ptr<SlicedImage> playerImages = std::make_unique<SlicedImage>(
		material->GetDiffuseMap().lock(),
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

std::string_view Skeleton::GetAnimationMovementName(Coord direction)
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

void Skeleton::SetSideSize(Sides sides)
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
}

void Skeleton::Draw()
{
	material->Use(this);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	const bool isHasDiffuseVertexs = 
		material->GetDiffuseMapVerticies().size() >= 2 && 
		material->GetDiffuseMap().lock() != nullptr;

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
	std::weak_ptr<Audio> weakWalk = audioController["walk"];
	std::shared_ptr<Audio> walk = weakWalk.lock();
	if (walk == nullptr) return;

	if (walk != nullptr && walk->GetState() != AudioStates::PLAYING) {
		walk->Play();
	}

	SetPos(newPos);
}

bool Skeleton::CheckForCollision(Coord position)
{
	WindowPointer<std::vector<std::shared_ptr<IGameObject>>>* solidCollisionsObjects = WindowPointerController::GetValue<std::vector<std::shared_ptr<IGameObject>>>(window->GetWindow(), "SolidCollisions");
	if (!solidCollisionsObjects || solidCollisionsObjects->GetValue().empty()) {
		return true;
	}

	for (std::shared_ptr<IGameObject>& collisionObj : solidCollisionsObjects->GetValue()) {
		std::shared_ptr<ICollision> collision = collisionObj->GetCollision().lock();
		if (collision == nullptr) {
			continue;
		}

		std::vector<Coord> points = collision->GetPoints();

		if (collisionObj == nullptr || collision == nullptr) {
			continue;
		}

		if (collision->IsCollisionEnter(position, Size(24, 24))) {
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
	Coord& vertex1 = vertexes[0];
	Coord& vertex2 = vertexes[1];

	float glDelta = (float)sideSize / (float)window->GetSize().GetWidth() * 2.0f;

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

	size.SetWidth((vertex1.X - vertex2.X) * window->GetSize().GetWidth() / 2.0f);
	size.SetHeight((vertex1.Y - vertex2.Y) * window->GetSize().GetHeight() / 2.0f);

	pos.X = window->GLXToPixel((vertex1.X + vertex2.X) / 2.0f);
	pos.Y = window->GLYToPixel((vertex1.Y + vertex2.Y) / 2.0f);
}

void Skeleton::AIMovement()
{
	if (isDead) return;

	std::shared_ptr<class Pawn> _target = target.lock();

	if (!movements.empty() && movements.size() == movementIndex) {
		movements.clear();
		action = Actions::Idle;
		animations.Play(GetAnimationName());
		movementIndex = 0;

		if (target.expired() || !_target) {
			return;
		}

		Thread* findTarget = new Thread(nullptr, [&]() {
			std::weak_ptr<Player> player = GameObjects::GetDynamicByTitle<Player>("Player");
			std::shared_ptr<Player> _player = player.lock();

			if (_player == nullptr) {
				return;
			}

			std::unique_ptr<Ray> ray = std::move(RayFactory::CreateRay(
				std::move(std::make_unique<Coord>(startPos)),
				std::move(std::make_unique<Coord>(_player->GetStartPos()))
			));

			if (ray == nullptr || ray->raySize > viewDistance) {
				ray.release();
				return;
			}

			std::weak_ptr<IGameObject> target = Raycast::RaycastFirst(
				RayFactory::CreateRay(
					std::move(std::make_unique<Coord>(startPos)),
					std::move(std::make_unique<Coord>(_player->GetStartPos()))
				)
			);

			if (_target != _player) {
				return;
			}
			this->SetTarget(player);
		});

		findTarget->Detach();
		return;
	}

	if (!movements.empty()) {
		std::shared_ptr<Movement>& movement = movements[movementIndex];

		action = movement->action;
		moveDirection = movement->direction;

		SetPos(movement->position);
		std::shared_ptr<IAnimation>& anim = movement->animation;

		if (anim == nullptr) {
			return;
		}

		animations.Play(anim->GetTitle());

		movement->complete = true;
		movementIndex++;
		return;
	}

	//Движение к цели
	if (!findingPath && _target) {
		std::thread([this, _target]() { 
			std::lock_guard<std::mutex> lock(pathMutex);
			Coord targetPos;

			if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(_target)) {
				targetPos = player->GetStartPos();
			}
			else {
				targetPos = _target->GetPos();
			}

			std::unique_ptr<Ray> ray = std::move(
				RayFactory::CreateRay(
					std::move(std::make_unique<Coord>(startPos)),
					std::move(std::make_unique<Coord>(targetPos))
				)
			);

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
	if (!findingPath && !_target) {
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
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes> openList;

	//Закрытый
	std::unordered_map<int, bool> closedList;

	//Все пути
	std::unordered_map<int, float> openListCosts;

	auto GetKey = [](Coord pos) { return pos.X * 10000 + pos.Y; };

	//Начальная позиция
	std::shared_ptr<Node> startNode = std::make_shared<Node>(
		std::make_unique<Movement>(
			GetAnimationName(),
			moveDirection,
			action,
			animations[GetAnimationName()].lock(),
			pos
		),
		0.0f, 
		std::hypot(goal.X - start.X, goal.Y - start.Y)
	);

	openList.push(startNode);
	openListCosts[GetKey(start)] = startNode->gCost;

	while (!openList.empty()) {
		std::shared_ptr<Node> currentNode = openList.top();
		openList.pop();
		if (closedList[GetKey(currentNode->movement->position)]) {
			continue;
		}

		//Цель достигнута
		if (Pawn::IsNear(currentNode->movement->position, goal, damageDistance - 10)) {
			std::shared_ptr<Node> node = currentNode;
			int i = 0;
			while (node != nullptr) {
				movements.push_back(node->movement);
				node = node->parent;
				i++;
			}

			std::reverse(movements.begin(), movements.end());
			return true;
		}

		closedList[GetKey(currentNode->movement->position)] = true;

		//Проверяем все стороны движения
		for (std::unique_ptr<Movement>& neighbor : GetNeighbors(currentNode->movement->position)) {
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

			std::unique_ptr<Node> neighborNode = std::make_unique<Node>(
				std::move(neighbor),
				tentativeGCost, 
				std::hypot(goal.X - neighborPos.X, goal.Y - neighborPos.Y), 
				currentNode
			);

			openList.push(std::move(neighborNode));
			openListCosts[neighborKey] = tentativeGCost;
		}
	}

	return false;
}

bool Skeleton::FindTarget()
{
	return true;
}

std::vector<std::unique_ptr<Movement>> Skeleton::GetNeighbors(Coord position)
{
	std::vector<std::unique_ptr<Movement>> neighbors;
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

			std::string_view title = GetAnimationMovementName(dir);
			neighbors.push_back(
				std::make_unique<Movement>(
					title, 
					GetDirection(dir), Actions::Move,
					animations[title].lock(), neighbor
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
