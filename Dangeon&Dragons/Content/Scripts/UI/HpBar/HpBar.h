#pragma once
#include "../../../../Dodge/figures/Rect.h"

class HpBar
{
	std::unique_ptr<Rect> bar;
	std::unique_ptr<Rect> line;
	std::unique_ptr<Rect> icon;

	Window* window;

	int hp;

	void Draw() const;
public:
	HpBar(Window& window);
	~HpBar() = default;

	void SetPos(Coord pos);
	Coord GetPos() const;

	void SetSize(Size size);
	Size GetSize() const;

	void SetSides(Sides sides);

	void SetHp(int hp);
	int GetHp() const;

	void Update() const;
};