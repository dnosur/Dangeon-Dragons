#pragma once
#include "../../../../Dodge/tiny/TinyMap.h"
#include "../../../../Dodge/camera/Camera.h"
#include "../../Characters/Player/Player.h"

#include <mutex>
#include <thread>

class WonderWold 
	: public TinyMap
{
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;

	std::vector<std::shared_ptr<class Pawn>> enemys;

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
	WonderWold(Window* window, std::unique_ptr<TileMap> tileMap, Coord pos = Coord());

	void SetCamera(std::unique_ptr<Camera> camera);

	void Update() override;
	void UpdatePawns();
};

