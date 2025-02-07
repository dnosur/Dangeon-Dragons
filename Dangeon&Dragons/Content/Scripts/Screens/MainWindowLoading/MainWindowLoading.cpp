#include "MainWindowLoading.h"
#include <filesystem>

#include"../../../../Dodge/utilities/string.h"
#include "../../UI/ProgressBar/TextureProgressBar/TextureProgressBar.h"

void MainWindowLoading::Initialize()
{
	images = std::make_shared<ImagesController>();
	imageIndex = std::make_shared<int>(0);

	images->LoadFromFolder("Content/Images/LoadingScreen");

	std::weak_ptr<ImagesController> imagesWeak = images;
	std::weak_ptr<int> imageIndexWeak = imageIndex;

	progressBar->OnChangeValueHandler([
		imagesWeak, imageIndexWeak
	](ProgressBar& progressBar) {
			if (imagesWeak.expired() || imageIndexWeak.expired() ||
				!imagesWeak.lock() || !imageIndexWeak.lock()) {
				return;
			}

			*imageIndexWeak.lock() = rand() % imagesWeak.lock()->GetSize();
	});
}

void MainWindowLoading::Draw()
{
}
	
MainWindowLoading::MainWindowLoading(int maxValue) 
	: LoadingScreen(
		std::make_unique<TextureProgressBar>(
			Coord(Window::GetRenderResolution().GetWidth() / 4, 0),
			Window::GetRenderResolutionView() / 2,
			"Content/UI/LoadBar/",
			maxValue
		)
	)
{
	Initialize();
}

std::weak_ptr<ProgressBar> MainWindowLoading::GetProgressBar()
{
	return progressBar;
}

void MainWindowLoading::Update()
{
	const Size& windowSize = Window::GetRenderResolutionView();
	if (images->GetSize()) {
		images->DrawImage(images->operator[](*imageIndex)->title, Coord(0, 0), windowSize, windowSize);
	}
	progressBar->Update();
}
