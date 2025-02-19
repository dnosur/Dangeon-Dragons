#include "PauseMenu.h"

void PauseMenu::Initialize()
{
}

void PauseMenu::Draw()
{
	std::weak_ptr<ImagesController> images = Window::GetImagesController();
	if (!images.lock() || images.expired()) {
		return;
	}

	const Size& renderResolution = Window::GetRenderResolutionView();

	images.lock()->DrawImage(
		ImagesController::GetDafaultImage(),
		Coord(), 
		renderResolution, 
		Color(0, 0, 0, .5f)
	);

	images.lock()->DrawImage(
		"pauseMenu",
		Coord(renderResolution.width / 4.5, 0),
		renderResolution
	);
}

void PauseMenu::Update()
{
	Draw();
}
