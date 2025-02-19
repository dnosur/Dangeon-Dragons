#include "HpBar.h"
#include "../../../../../Dodge/images/SlicedImage.h"
#include "../../../../../Dodge/Sides.h"

void HpBar::Draw()
{
    line->Update();
    bar->Update();
    icon->Update();

    line->SetSideSize(Sides(0, 0, 0, 0));
}

void HpBar::Initialize()
{
    bar = std::make_unique<Rect>(
        "hpBar",
        ProgressBar::GetPos(),
        ProgressBar::GetSize(),
        Color(1.0f, 1.0f, 1.0f, 1.0f)
    );

    bar->GetMaterial().lock()->SetDiffuseMap(
        std::make_unique<Image>(
            ImagesController::LoadImg(
                "Content/UI/Cryo's Mini GUI/GUI/Pngs/Bars.png",
                "hpBar"
            )
        )
    );

    bar->GetMaterial().lock()->SetDiffuseMapVerticies(
        SlicedImage::CalculateTextureVertexes(
            Size(128, 128),
            bar->GetMaterial().lock()->GetDiffuseMap().lock()->GetSize(),
            Coord(2, 0)
        )
    );

    line = std::make_unique<Rect>(
        "hpLine",
        Coord(150, 35),
        Size(120, 10),
        Color(1.0f, 0, 0)
    );

    icon = std::make_unique<Rect>(
        "hpIcon",
        Coord(45, 35),
        Size(32, 32),
        Color(1.0f, 1.0f, 1.0f, 1.0f)
    );

    icon->GetMaterial().lock()->SetDiffuseMap(
        std::make_unique<Image>(
            ImagesController::LoadImg(
                "Content/UI/Cryo's Mini GUI/GUI/Pngs/icons.png",
                "hpIcon"
            )
        )
    );


    icon->GetMaterial().lock()->SetDiffuseMapVerticies(
        SlicedImage::CalculateTextureVertexes(
            Size(32, 32),
            icon->GetMaterial().lock()->GetDiffuseMap().lock()->GetSize(),
            Coord(0, 0)
        )
    );
}

HpBar::HpBar(int hp)
    : hp(hp), 
    ProgressBar(Coord(150, 30), Size(200, 100))
{
    Initialize();
}

void HpBar::SetPos(Coord position)
{
}

Coord HpBar::GetPos() const
{
	return Coord();
}

void HpBar::SetSize(Size size)
{
	bar->SetSize(size);
}

Size HpBar::GetSize() const
{
	return bar->GetSize();
}

void HpBar::SetSides(Sides sides)
{
	bar->SetSideSize(sides);
}

void HpBar::SetHp(int hp)
{
    this->hp = hp;
}

int HpBar::GetHp() const
{
	return hp;
}

void HpBar::Update()
{
	Draw();
}
