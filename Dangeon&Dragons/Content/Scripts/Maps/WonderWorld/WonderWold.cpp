#include "WonderWold.h"

#include "../../Characters/Enemys/Skeleton.h"
#include "../../../../Dodge/raycast/Raycast.h"
#include "../../../../Dodge/GameObjects.h"

void WonderWold::CreateCamera()
{
	camera = std::make_shared<Camera>(
		"Player",
		Size(0, 0),
		Size(1000, 1000),
		window
	);
}

void WonderWold::SpawnPlayer()
{
	std::unique_ptr<Material> playerMaterial = std::make_unique<BaseFigureMaterial>();
	std::weak_ptr<IGameObject> weakPlayerSpawn = GetClassByName("PlayerSpawnPoint");
	std::shared_ptr<IGameObject> playerSpawn = weakPlayerSpawn.lock();

	if (playerSpawn == nullptr) {
		return;
	}

	playerMaterial->SetShader(
		std::make_shared<Shader>(
			"Player",
			"Dodge/shaders/Test/vertex.vs",
			"Dodge/shaders/Test/fragment.frag"
		)
	);

	playerMaterial->SetDiffuse(Color(1, 1, 1));
	playerMaterial->SetDiffuseMap(
		std::make_shared<Image>(
			ImagesController::LoadImg(
				"Content/Assets/lpc_entry/males/player.png",
				"Player"
			)
		)
	);

	player = std::make_shared<Player>(
		"Player",
		*window,
		std::make_unique<BoxCollision>(
			playerSpawn->GetPos(),
			Size(24, 16),
			-1,
			(char*)"Player",
			(char*)"Player"
		),
		std::move(playerMaterial),
		Directions::DOWN,
		playerSpawn->GetPos(),
		Size(64, 64),
		50,
		53,
		48,
		100,
		100,
		true,
		false,
		false
	);

	camera->SetObservedObj(player);

	WindowPointerController::SetPointer(
		window->GetWindow(), 
		WindowPointer<Player>("player", player.get())
	);

	GameObjects::Add(std::dynamic_pointer_cast<class Pawn>(player));
}

void WonderWold::SpawnSkeleton(Coord pos)
{
	for (std::weak_ptr<IGameObject>& weakSpawn : GetClassesByName("SkeletonSpawnPoint")) {
		std::shared_ptr<IGameObject> spawn = weakSpawn.lock();
		if (spawn == nullptr) {
			continue;
		}

		//skeleton->SetTarget(player);
		std::unique_ptr<Material> skeletonMaterial = std::make_unique<BaseFigureMaterial>();
		skeletonMaterial->SetShader(
			std::make_shared<Shader>(
				"Skeleton",
				"Dodge/shaders/Test/vertex.vs",
				"Dodge/shaders/Test/fragment.frag"
			)
		);

		skeletonMaterial->SetDiffuse(Color(1, 1, 1));
		skeletonMaterial->SetDiffuseMap(
			std::make_shared<Image>(
				ImagesController::LoadImg(
					"Content/Assets/lpc_entry/males/skeleton.png",
					"Skeleton"
				)
			)
		);

		skeletonMaterial->SetCamera(camera);

		std::shared_ptr<Skeleton> skeleton = std::make_unique<Skeleton>(
			"Skeleton",
			*window,
			std::make_unique<BoxCollision>(
				spawn->GetPos(),
				Size(24, 16),
				-1,
				(char*)"Skeleton",
				(char*)"Enemy"
			),
			std::move(skeletonMaterial),
			Directions::DOWN,
			spawn->GetPos(),
			Size(64, 64),
			50,
			53,
			48,
			100,
			100,
			true,
			false,
			false
		);

		GameObjects::Add(std::dynamic_pointer_cast<class Pawn>(skeleton));
		enemys.push_back(std::move(skeleton));
		return;
	}
}

void WonderWold::OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject)
{
}

Propertie* WonderWold::GetObjectPropertie(std::string propertie_name, IGameObject* object)
{
	return nullptr;
}

void WonderWold::Initialize()
{
	CreateCamera();

	SpawnPlayer();
	SpawnSkeleton(Coord(450, 300));

	std::unique_ptr<Audio> main = std::make_unique<Audio>("main", "Content/Sounds/WonderWorld/main.wav");
	main->SetVolume(0.05f);

	std::unique_ptr<Audio> wind = std::make_unique<Audio>("wind", "Content/Sounds/WonderWorld/light-wind.wav");
	wind->SetVolume(0.15f);

	audioController.Load(std::move(main));
	audioController.Load(std::move(wind));

	audioController.Play("main", true);
	audioController.Play("wind", true);
}

WonderWold::WonderWold(Window* window, std::unique_ptr<TileMap>  tileMap, Coord pos)
	: TinyMap(window, std::move(tileMap), pos)
{
	Initialize();
}

void WonderWold::SetCamera(std::unique_ptr<Camera> camera)
{
	this->camera = std::move(camera);
}

void WonderWold::Update()
{
	std::weak_ptr<IGameObject> observed = camera->GetObservedObj();
	std::shared_ptr<IGameObject> lockedObserved = observed.lock();

	Coord cameraOffset = camera->GetOffset();
	bool cameraMove = cameraOffset.X != 0 || cameraOffset.Y != 0;

	std::cout << "1\n";

	for (std::shared_ptr<IGameObject>& obj : gameObjects)
	{
		if (cameraMove) {
			Coord temp = obj->GetPos();
			obj->SetPos(temp + cameraOffset);
		}

		animationController.Play(obj->GetTitle());

		if (lockedObserved == nullptr) {
			continue;
		}

		const Coord& distance = lockedObserved->GetDistanceTo(*obj);

		if (distance.X >= 500 || distance.X <= -838 ||
			distance.Y >= 584|| distance.Y <= -200) {
			continue;
		}

		obj->Update();
	}

	std::cout << "2\n";

	if (cameraMove) {
		for (std::shared_ptr<class Pawn>& pawn : enemys) {
			Coord temp = pawn->GetPos();
			pawn->SetPos(temp + cameraOffset);
			if (std::shared_ptr<Skeleton> skeleton = std::dynamic_pointer_cast<Skeleton>(pawn)) {
				skeleton->SetPathOffset(cameraOffset);
			}

			std::shared_ptr<ICollision> collision = pawn->GetCollision().lock();
			if (collision == nullptr) {
				continue;
			}

			collision->SetPoints({
				pawn->GetPos()
			});
		}

		for (std::shared_ptr<IGameObject>& obj : gameClasses)
		{
			Coord temp = obj->GetPos();
			obj->SetPos(temp + cameraOffset);
			obj->GetCollision().lock()->SetPoints({
				obj->GetPos()
			});
		}
	}

	std::cout << "3\n";

	UpdatePawns();
}

void WonderWold::UpdatePawns()
{
	camera->DropOffset();
	for (std::shared_ptr<class Pawn>& pawn : enemys)
	{
		pawn->Update();
	}

	std::cout << "4\n";

	player->Update();
}
