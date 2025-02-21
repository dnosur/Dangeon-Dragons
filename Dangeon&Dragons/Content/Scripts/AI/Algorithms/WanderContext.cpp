#include "WanderContext.h"

#include <random>
#include <queue>

#include "../../Characters/Enemys/Skeleton.h"
#include "../../../../Dodge/threads/Thread.h"
#include "../../../../Dodge/GameObjects.h"
#include "../../Characters/Player/Player.h"
#include "../../../../Dodge/raycast/RayFactory.h"
#include "../../../../Dodge/raycast/Raycast.h"
#include "../Node.h"

Coord WanderContext::GenerateRandomPosition(class Pawn* pawn, Coord center, float radius)
{
	unsigned int seed = std::random_device{}();
	std::mt19937 gen(seed);
	std::uniform_real_distribution<float> distribution(0.0f, RAND_MAX);

	int num1 = distribution(gen);
	int num2 = distribution(gen);

	float angle = static_cast<float>(num1) / RAND_MAX * 2 * M_PI; // ��������� ����
	float distance = static_cast<float>(num2) / RAND_MAX * radius; // ��������� ���������� � �������� �������
	float offsetX = distance * cos(angle);
	float offsetY = distance * sin(angle);

	Coord randomPosition = {
		static_cast<double>(center.X + offsetX),
		static_cast<double>(center.Y + offsetY)
	};

	// ��������, ��� ������� ���������
	if (!pawn->IsWalkable(randomPosition)) {
		return GenerateRandomPosition(pawn, center, radius); // ���������� ���� ������ �������
	}

	return randomPosition;
}

bool WanderContext::FindPath(class Pawn* pawn, Coord start, Coord goal)
{
	//������� ����
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes> openList;

	//��������
	std::unordered_map<int, bool> closedList;

	//��� ����
	std::unordered_map<int, float> openListCosts;

	auto GetKey = [](Coord position) { return position.X * 10000 + position.Y; };

	//��������� �������
	std::shared_ptr<Node> startNode = std::make_shared<Node>(
		std::make_unique<Movement>(
			pawn->GetAnimationName(),
			pawn->GetMoveDirection(),
			pawn->GetAction(),
			pawn->GetAnimations()[pawn->GetAnimationName()].lock(),
			pawn->GetPos()
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

		//���� ����������
		if (pawn->IsNear(currentNode->movement->position, goal, pawn->GetDamageDistance() - 10)) {
			std::shared_ptr<Node> node = currentNode;
			int i = 0;
			while (node != nullptr) {
				movements->AddMovement(std::move(node->movement));
				node = node->parent;
				i++;
			}

			std::reverse(movements->begin(), movements->end());
			return true;
		}

		closedList[GetKey(currentNode->movement->position)] = true;

		//��������� ��� ������� ��������
		for (std::unique_ptr<Movement>& neighbor : GetNeighbors(pawn, currentNode->movement->position)) {
			Coord& neighborPos = neighbor->position;
			int neighborKey = GetKey(neighborPos);

			if (closedList[neighborKey]) continue;

			//������������ ��������� ���� �� ������
			float tentativeGCost = currentNode->gCost + std::hypot(neighborPos.X - currentNode->movement->position.X, neighborPos.Y - currentNode->movement->position.Y);

			//���� ��� ������������ ����� ����������� ����
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

std::vector<std::unique_ptr<Movement>> WanderContext::GetNeighbors(class Pawn*& pawn, Coord position)
{
	std::vector<std::unique_ptr<Movement>> neighbors;
	std::vector<Coord> directions = {
		{ 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, // �������� �����������
		{ 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } // ������������ �����������
	};

	for (Coord& dir : directions) {
		Coord neighbor = {
			position.X + ((pawn->GetSpeed()) * 0.1f) * dir.X,
			position.Y + ((pawn->GetSpeed()) * 0.1f) * dir.Y
		};

		if (pawn->IsWalkable(neighbor)) { // ���������, ����� �� ������
			//std::make_pair(GetAnimationMovementName(dir), neighbor)

			std::string_view title = pawn->GetAnimationMovementName(dir);

			neighbors.push_back(
				std::make_unique<Movement>(
					title,
					GetDirection(dir), Actions::Move,
					pawn->GetAnimations()[title].lock(), neighbor
				)
			);
		}
	}

	return neighbors;
}

bool WanderContext::FindTarget()
{
    return false;
}

WanderContext::WanderContext()
	: movements(std::make_unique<MovementsController>()), findingPath(false)
{
}

bool WanderContext::Invoke(class Pawn* pawn, AIContext* sender)
{
	if (pawn->IsDead()) return true;

	std::shared_ptr<class Pawn> _target = pawn->GetTarget().lock();

	if (!movements->IsEmpty() && movements->IsComplete()) {
		movements->Clear();
		pawn->SetAction(Actions::Idle);

		pawn->GetAnimations().Play(pawn->GetAnimationName());

		if (pawn->GetTarget().expired() || !_target) {
			return false;
		}

		std::unique_ptr<Thread> findTarget = std::make_unique<Thread>("", [&]() {
			std::weak_ptr<Player> player = GameObjects::GetDynamicByTitle<Player>("Player");
			std::shared_ptr<Player> _player = player.lock();

			if (_player == nullptr) {
				return false;
			}

			std::unique_ptr<Ray> ray = std::move(RayFactory::CreateRay(
				std::move(std::make_unique<Coord>(pawn->GetStartPos())),
				std::move(std::make_unique<Coord>(_player->GetStartPos()))
			));

			if (ray == nullptr || ray->raySize > pawn->GetViewDistance()) {
				ray.release();
				return false;
			}

			std::weak_ptr<IGameObject> target = Raycast::RaycastFirst(
				RayFactory::CreateRay(
					std::move(std::make_unique<Coord>(pawn->GetStartPos())),
					std::move(std::make_unique<Coord>(_player->GetStartPos()))
				)
			);

			if (_target != _player) {
				return false;
			}
			pawn->SetTarget(player);
		});

		findTarget->Detach();
		return true;
	}

	if (!movements->IsEmpty()) {
		movements->MakeNext(pawn);
		return true;
	}

	if (!findingPath && _target) {
		std::thread([this, _target, pawn]() {
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
					std::move(std::make_unique<Coord>(pawn->GetStartPos())),
					std::move(std::make_unique<Coord>(targetPos))
				)
			);

			if (ray == nullptr || ray->raySize > pawn->GetViewDistance()) {
				ray.release();
				return true;
			}

			FindPath(pawn, pawn->GetPos(), targetPos);
			findingPath = false;
		}).detach();
		//std::cout << "Skeleton moving to " << target->GetTitle() << "...\n";
		return true;
	}

	//��������
	if (!findingPath && !_target) {
		std::thread([this, pawn]() {
			float wanderRadius = 100.0f;
			Coord randomPosition = GenerateRandomPosition(pawn, pawn->GetPos(), wanderRadius);
			std::lock_guard<std::mutex> lock(pathMutex);
			FindPath(pawn, pawn->GetPos(), randomPosition);
			findingPath = false;
		}).detach();
		//std::cout << "Skeleton wandering...\n";
	}

	//std::cout << "Skeleton waiting...\n";
}
