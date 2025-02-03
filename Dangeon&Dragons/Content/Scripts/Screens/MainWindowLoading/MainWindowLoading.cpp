#include "MainWindowLoading.h"

void MainWindowLoading::Initialize()
{
	
}

void MainWindowLoading::Draw()
{
}

MainWindowLoading::MainWindowLoading(
	int maxValue, 
	int currentValue, 
	bool isFinished
) : maxValue(maxValue), currentValue(currentValue), isFinished(isFinished)
{
	Initialize();
}

void MainWindowLoading::SetMaxValue(int value)
{
	this->maxValue = value;
}

const int& MainWindowLoading::GetMaxValue() const
{
	return this->maxValue;
}

void MainWindowLoading::SetCurrentValue(int value)
{
	this->currentValue = value;
}

const int& MainWindowLoading::GetCurrentValue() const
{
	return this->currentValue;
}

bool MainWindowLoading::IsFinished()
{
	return isFinished;
}

void MainWindowLoading::Update()
{
}
