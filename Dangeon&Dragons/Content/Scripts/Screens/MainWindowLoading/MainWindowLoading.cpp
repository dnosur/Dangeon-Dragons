#include "MainWindowLoading.h"
#include <filesystem>

#include"../../../../Dodge/utilities/string.h"
#include "../../UI/ProgressBar/TextureProgressBar/TextureProgressBar.h"

void MainWindowLoading::Initialize()
{

}

void MainWindowLoading::Draw()
{
}
	
MainWindowLoading::MainWindowLoading(int maxValue) 
	: LoadingScreen(
		std::make_unique<TextureProgressBar>(
			Coord(320, 0),
			Size(1280 / 2, 720 / 2),
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
	progressBar->Update();
}
