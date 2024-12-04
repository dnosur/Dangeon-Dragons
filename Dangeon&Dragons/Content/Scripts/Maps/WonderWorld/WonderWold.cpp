#include "WonderWold.h"

void WonderWold::OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject)
{
}

WonderWold::WonderWold(Window* window, TileMap* tileMap, Coord pos)
	: TinyMap(window, tileMap, pos)
{
}

WonderWold::~WonderWold()
{
}

void WonderWold::Update()
{
	for (IGameObject* obj : gameObjects)
	{
		animationController.Play(obj->GetTitle());
		obj->Update();
	}
}
