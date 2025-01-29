#pragma once
#include "../../../../Dodge/tiny/TinyMap.h"
#include "../../../../Dodge/camera/Camera.h"
#include "../../Characters/Player/Player.h"

#include <mutex>
#include <thread>

class WonderWold 
	: public TinyMap
{
	Player* player;
	Camera* camera;

	std::vector<class Pawn*> enemys;

	AudioController audioController;

	std::mutex pawnUpdate;
	std::mutex posUpdate;

	void CreateCamera();
	void SpawnPlayer();
	void SpawnSkeleton(Coord pos);

	void OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject) override;

	Propertie* GetObjectPropertie(std::string propertie_name, IGameObject* object);

	void Initialize();
public:
	WonderWold(Window* window, TileMap* tileMap, Coord pos = Coord());
	~WonderWold();

	float moveSpeed = .4f;

	void SetCamera(Camera* camera);

	void Update() override;
	void UpdatePawns();
};

