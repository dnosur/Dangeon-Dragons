#pragma once
#include "../LoadingScreen/Screen.h"

class MainWindowLoading : protected Screen
{
	int maxValue;
	int currentValue;
	bool isFinished;

	void Initialize() override;
	void Draw() override;
public:
	MainWindowLoading(int maxValue = 100, int currentValue = 0, bool isFinished = false);
	~MainWindowLoading() = default;

	void SetMaxValue(int value);
	const int& GetMaxValue() const;

	void SetCurrentValue(int value);
	const int& GetCurrentValue() const;

	bool IsFinished();

	void Update() override;
};

