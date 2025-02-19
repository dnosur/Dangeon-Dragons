#include "MainWindowLoading.h"

#include <memory>
#include <filesystem>

#include"../../../../Dodge/utilities/string.h"
#include "../../UI/ProgressBar/TextureProgressBar/TextureProgressBar.h"
#include "../../../../Dodge/utilities/random.h"
#include "../../../../Dodge/font/Fonts.h"

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

			*imageIndexWeak.lock() = randm(0, imagesWeak.lock()->GetSize() - 1);
	});
}

void MainWindowLoading::Draw()
{
	const Size& windowSize = Window::GetRenderResolutionView();
	if (images->GetSize()) {
		images->DrawImage(images->operator[](*imageIndex)->GetTitle(), Coord(0, 0), windowSize);
		Fonts::GetFont("DreiFraktur")->RenderText(
			L"Подсказка касаемо того как вам играть.. Что-то там ещё туда сюда какой-то текст со смыслом!",
			Coord(Window::GetSize().width / 4.0f, 150),
			std::make_unique<FontRenderOptions>(
				1.0f,
				.0f,
				std::make_unique<Size>(1000, 90),
				std::make_unique<Padding>(0, 15.0f, 0, 0),
				Color(0.93f, 0.89f, 0.41f)
			)
		);
	}
}
	
MainWindowLoading::MainWindowLoading(int maxValue)
	: LoadingScreen(
		std::make_unique<TextureProgressBar>(
			Coord(Window::GetRenderResolution().GetWidth() / 4, 0),
			Window::GetRenderResolutionView() / 2,
			"Content/UI/LoadBar/",
			maxValue,
			0,
			false,
			std::make_unique<Color>(1, 1, 1)
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
	Draw();
	progressBar->Update();
}
