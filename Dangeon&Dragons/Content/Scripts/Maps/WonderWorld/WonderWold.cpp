#include "WonderWold.h"

#include "../../Characters/Enemys/Skeleton.h"
#include "../../../../Dodge/raycast/Raycast.h"
#include "../../../../Dodge/GameObjects.h"

void WonderWold::CreateCamera()
{
	camera = new Camera(
		"Player",
		Size(0, 0),
		Size(1000, 1000),
		window
	);
}

void WonderWold::SpawnPlayer()
{
	Material* playerMaterial = new BaseFigureMaterial();
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

	player = new Player(
		"Player",
		*window,
		new BoxCollision(
			playerSpawn->GetPos(),
			Size(24, 16),
			-1,
			(char*)"Player",
			(char*)"Player"
		),
		playerMaterial,
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
		WindowPointer<Player*>("player", &player)
	);

	GameObjects::Add(player);
}

void WonderWold::SpawnSkeleton(Coord pos)
{

	for (IGameObject* spawn : GetClassesByName("SkeletonSpawnPoint")) {
		//skeleton->SetTarget(player);
		Material* skeletonMaterial = new BaseFigureMaterial();
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

		Skeleton* skeleton = new Skeleton(
			"Skeleton",
			*window,
			new BoxCollision(
				spawn->GetPos(),
				Size(24, 16),
				-1,
				(char*)"Skeleton",
				(char*)"Enemy"
			),
			skeletonMaterial,
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

		enemys.push_back(skeleton);
		GameObjects::Add(skeleton);
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

WonderWold::WonderWold(Window* window, TileMap* tileMap, Coord pos)
	: TinyMap(window, tileMap, pos)
{
	Initialize();
}

WonderWold::~WonderWold()
{

}

void WonderWold::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void WonderWold::Update()
{
	IGameObject* observed = camera->GetObservedObj();
	Coord cameraOffset = camera->GetOffset();
	bool cameraMove = cameraOffset.X != 0 || cameraOffset.Y != 0;

	for (IGameObject* obj : gameObjects)
	{
		if (cameraMove) {
			obj->SetPos(obj->GetPos() + cameraOffset);
		}

		animationController.Play(obj->GetTitle());
		Coord distance = observed->GetDistanceTo(*obj);

		if (distance.X >= 500 || distance.X <= -838 ||
			distance.Y >= 584|| distance.Y <= -200) {
			continue;
		}

		obj->Update();
	}

	if (cameraMove) {
		for (class Pawn* pawn : enemys) {
			pawn->SetPos(pawn->GetPos() + cameraOffset);
			if (Skeleton* skeleton = dynamic_cast<Skeleton*>(pawn)) {
				skeleton->SetPathOffset(cameraOffset);
			}

			if (pawn->GetCollision() == nullptr) {
				continue;
			}

			pawn->GetCollision()->SetPoints({
				pawn->GetPos()
			});
		}

		for (IGameObject* obj : gameClasses)
		{
			obj->SetPos(obj->GetPos() + cameraOffset);
			obj->GetCollision()->SetPoints({
				obj->GetPos()
			});
		}
	}

	UpdatePawns();
}

void WonderWold::UpdatePawns()
{
	camera->DropOffset();
	for (IGameObject* obj : enemys)
	{
		obj->Update();
	}

	player->Update();
}
