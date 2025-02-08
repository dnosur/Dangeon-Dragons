#pragma once
#include "../Screen.h"
#include "../../UI/ProgressBar/ProgressBar.h"

class LoadingScreen :
    public Screen
{
protected:
	std::shared_ptr<ProgressBar> progressBar;

private:
	void Initialize() override;
	void Draw() override;

public: 
	LoadingScreen(std::unique_ptr<ProgressBar> progressBar);
	~LoadingScreen() = default;

	void Update() override;
};

