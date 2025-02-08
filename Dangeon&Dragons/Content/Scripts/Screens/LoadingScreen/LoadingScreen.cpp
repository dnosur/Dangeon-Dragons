#include "LoadingScreen.h"
void LoadingScreen::Initialize()
{
}
void LoadingScreen::Draw()
{
}
LoadingScreen::LoadingScreen(std::unique_ptr<ProgressBar> progressBar)
	: progressBar(std::move(progressBar)),
	  Screen()
{
}

void LoadingScreen::Update()
{
}
