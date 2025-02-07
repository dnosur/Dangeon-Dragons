#pragma once
#include "../LoadingScreen/LoadingScreen.h"

class MainWindowLoading : protected LoadingScreen
{
	std::shared_ptr<ImagesController> images;
	std::shared_ptr<int> imageIndex;

	void Initialize() override;
	void Draw() override;
public:
	MainWindowLoading(int maxValue = 100);
	~MainWindowLoading() = default;

	std::weak_ptr<ProgressBar> GetProgressBar();

	void Update() override;
};

