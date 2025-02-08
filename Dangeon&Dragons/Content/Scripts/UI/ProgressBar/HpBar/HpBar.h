#pragma once
#include "../../../../../Dodge/figures/Rect.h"
#include "../../ProgressBar/ProgressBar.h"

class HpBar 
	: public ProgressBar
{
	std::unique_ptr<Rect> bar;
	std::unique_ptr<Rect> line;
	std::unique_ptr<Rect> icon;

	Window* window;

	int hp;

	void Draw() override;
	void Initialize() override;
public:
	HpBar(Window& window, int hp = 100);
	~HpBar() = default;

	void SetPos(Coord pos);
	Coord GetPos() const;

	void SetSize(Size size);
	Size GetSize() const;

	void SetSides(Sides sides);

	void SetHp(int hp);
	int GetHp() const;

	void Update() override;
};