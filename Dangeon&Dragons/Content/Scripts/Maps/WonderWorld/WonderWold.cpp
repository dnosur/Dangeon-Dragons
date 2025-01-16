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
	IGameObject* playerSpawn = GetClassByName("PlayerSpawnPoint");

	playerMaterial->SetShader(
		new Shader(
			"Player",
			"Dodge/shaders/Test/vertex.vs",
			"Dodge/shaders/Test/fragment.frag"
		)
	);

	playerMaterial->SetDiffuse(Color(1, 1, 1));
	playerMaterial->SetDiffuseMap(
		new Image(
			ImagesController::LoadImg(
				"Content/Assets/lpc_entry/males/player.png",
				"Player"
			)
		)
	);

	player = std::unique_ptr<Player>(new Player(
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
	));


	camera->SetObservedObj(std::shared_ptr<Player>(player.get()));

	WindowPointerController::SetPointer(
		window->GetWindow(), 
		WindowPointer<Player>("player", player.get())
	);

	GameObjects::Add(std::shared_ptr<class Pawn>(player.get()));
}

void WonderWold::SpawnSkeleton(Coord pos)
{
	for (IGameObject* spawn : GetClassesByName("SkeletonSpawnPoint")) {
		//skeleton->SetTarget(player);
		std::unique_ptr<Material> skeletonMaterial = std::make_unique<BaseFigureMaterial>();
		skeletonMaterial->SetShader(
			new Shader(
				"Skeleton",
				"Dodge/shaders/Test/vertex.vs",
				"Dodge/shaders/Test/fragment.frag"
			)
		);

		skeletonMaterial->SetDiffuse(Color(1, 1, 1));
		skeletonMaterial->SetDiffuseMap(
			new Image(
				ImagesController::LoadImg(
					"Content/Assets/lpc_entry/males/skeleton.png",
					"Skeleton"
				)
			)
		);

		skeletonMaterial->SetCamera(camera);

		std::unique_ptr<Skeleton> skeleton = std::make_unique<Skeleton>(
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

		GameObjects::Add(std::shared_ptr<class Pawn>(skeleton.get()));
		enemys.push_back(std::move(skeleton));
	}
}

void WonderWold::OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject)
{
}

Propertie* WonderWold::GetObjectPropertie(const char* propertie_name, IGameObject* object)
{
	return nullptr;
}

void WonderWold::Initialize()
{
	CreateCamera();

	SpawnPlayer();
	SpawnSkeleton(Coord(450, 300));

	Audio* main = new Audio("main", "Content/Sounds/WonderWorld/main.wav");
	main->SetVolume(0.05f);

	Audio* wind = new Audio("wind", "Content/Sounds/WonderWorld/light-wind.wav");
	wind->SetVolume(0.15f);

	audioController.Load(main);
	audioController.Load(wind);

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
	Coord cameraOffset = camera->GetOffset();
	bool cameraMove = cameraOffset.X != 0 || cameraOffset.Y != 0;

	for (IGameObject* obj : gameObjects)
	{
		if (cameraMove) {
			obj->SetPos(obj->GetPos() + cameraOffset);
		}

		animationController.Play(obj->GetTitle());
		Coord distance = observed.lock()->GetDistanceTo(*obj);

		if (distance.X >= 500 || distance.X <= -838 ||
			distance.Y >= 584|| distance.Y <= -200) {
			continue;
		}

		obj->Update();
	}

	if (cameraMove) {
		for (std::unique_ptr<class Pawn>& pawn : enemys) {
			pawn->SetPos(pawn->GetPos() + cameraOffset);
			if (Skeleton* skeleton = dynamic_cast<Skeleton*>(pawn.get())) {
				skeleton->SetPathOffset(cameraOffset);
			}

			const std::shared_ptr<ICollision> collision = pawn->GetCollision().lock();
			if (collision == nullptr) {
				continue;
			}

			collision->SetPoints({
				pawn->GetPos()
			});
		}

		for (IGameObject* obj : gameClasses)
		{
			obj->SetPos(obj->GetPos() + cameraOffset);
			obj->GetCollision().lock()->SetPoints({
				obj->GetPos()
			});
		}
	}

	UpdatePawns();
}

void WonderWold::UpdatePawns()
{
	camera->DropOffset();
	for (std::unique_ptr<class Pawn>& pawn : enemys)
	{
		pawn->Update();
	}

	player->Update();
}
