#pragma once
#include "../../../../Dodge/tiny/TinyMap.h"

class WonderWold 
	: public TinyMap
{

	void OnTriggerEnter(IGameObject* object, IGameObject* triggeredObject) override;
public:
	WonderWold(Window* window, TileMap* tileMap, Coord pos = Coord());
	~WonderWold();

	void Update() override;
};

