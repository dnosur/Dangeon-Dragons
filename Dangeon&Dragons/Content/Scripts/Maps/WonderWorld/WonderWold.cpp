#include "WonderWold.h"

#include "../../Characters/Enemys/Skeleton.h"
#include "../../../../Dodge/raycast/Raycast.h"
#include "../../../../Dodge/GameObjects.h"
#include "../../../../Dodge/shaders/ShadersController.h"


void WonderWold::SpawnPlayer()
{
	std::unique_ptr<Material> playerMaterial = std::make_unique<BaseFigureMaterial>();
	std::weak_ptr<IGameObject> weakPlayerSpawn = GetClassByName("PlayerSpawnPoint");
	std::shared_ptr<IGameObject> playerSpawn = weakPlayerSpawn.lock();

	if (playerSpawn == nullptr) {
		return;
	}

	playerMaterial->SetShader(
		ShadersController::GetShaderID("BaseFigure")
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

	//playerMaterial->SetCamera(camera);

	player = std::make_shared<Player>(
		"Player",
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

	Window::GetCamera().lock()->SetObservedObj(player);

	WindowPointerController::SetPointer(
		WindowPointer<Player>("player", player)
	);

	GameObjects::Add(std::dynamic_pointer_cast<class Pawn>(player));
}

void WonderWold::SpawnSkeleton(Coord position)
{
	for (std::weak_ptr<IGameObject>& weakSpawn : GetClassesByName("SkeletonSpawnPoint")) {
		std::shared_ptr<IGameObject> spawn = weakSpawn.lock();
		if (spawn == nullptr) {
			continue;
		}

		//skeleton->SetTarget(player);
		std::unique_ptr<Material> skeletonMaterial = std::make_unique<BaseFigureMaterial>();
		skeletonMaterial->SetShader(
			ShadersController::GetShaderID("BaseFigure")
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

		std::shared_ptr<class Skeleton> skeleton = std::make_unique<class Skeleton>(
			"Skeleton",
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
	SpawnPlayer();
	SpawnSkeleton(Coord(450, 300));

	for (std::shared_ptr<IGameObject>& obj : gameObjects) {
		if (!obj->GetMaterial().lock() || obj->GetMaterial().expired()) {
			continue;
		}
	}

	for (std::shared_ptr<IGameObject>& classObj : gameClasses) {
		if (!classObj->GetMaterial().lock() || classObj->GetMaterial().expired()) {
			continue;
		}
	}

	std::unique_ptr<Audio> main = std::make_unique<Audio>("main", "Content/Sounds/WonderWorld/main.wav");
	main->SetVolume(0.05f);

	std::unique_ptr<Audio> wind = std::make_unique<Audio>("wind", "Content/Sounds/WonderWorld/light-wind.wav");
	wind->SetVolume(0.15f);

	audioController.Load(std::move(main));
	audioController.Load(std::move(wind));

	audioController.Play("main", true);
	audioController.Play("wind", true);
}

WonderWold::WonderWold(std::unique_ptr<TileMap>  tileMap, Coord position)
	: TinyMap(std::move(tileMap), position)
{
	Initialize();
}

void WonderWold::Update()
{
	if (!Window::GetCamera().lock() || Window::GetCamera().expired()) {
		std::cout << "NULL CAMERA!" << std::endl;
		return;
	}

	std::shared_ptr<IGameObject> lockedObserved = Window::GetCamera().lock()->GetObservedObj().lock();
	if (!lockedObserved) {
		std::cout << "Camera need observed object!" << std::endl;
		return;
	}

	bool isPause = Window::GetGameStatus() == GameStatuses::Pause;

	for (std::shared_ptr<IGameObject>& obj : gameObjects)
	{
		if (!isPause) {
			animationController.Play(obj->GetTitle());
		}

		if (lockedObserved == nullptr) {
			continue;
		}

		const Coord& distance = lockedObserved->GetDistanceTo(*obj);

		if (distance.X >= Window::GetRenderResolutionView().width * 0.5f || distance.X <= -(Window::GetRenderResolutionView().width * 0.65f) ||
			distance.Y >= Window::GetRenderResolutionView().height * 0.5f || distance.Y <= -(Window::GetRenderResolutionView().height * 0.65f)) {
			continue;
		}

		obj->Update();
	}

	UpdatePawns();
}

void WonderWold::UpdatePawns()
{
	for (std::shared_ptr<class Pawn>& pawn : enemys)
	{
		pawn->Update();
	}

	player->Update();

	if (Window::GetCamera().lock() && !Window::GetCamera().expired()) {
		Window::GetCamera().lock()->Update();
	}
}
