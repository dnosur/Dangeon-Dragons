#include "ProgressBar.h"

ProgressBar::ProgressBar(Coord pos, Size size, int maxValue, int currentValue, bool isFinished)
	: pos(pos), size(size), maxValue(maxValue), currentValue(currentValue), isFinished(isFinished)
{
}

void ProgressBar::SetPos(Coord pos)
{
	this->pos = pos;
}

const Coord& ProgressBar::GetPos() const
{
	return this->pos;
}

void ProgressBar::SetSize(Size size)
{
	this->size = size;
}

const Size& ProgressBar::GetSize() const
{
	return this->size;
}

void ProgressBar::SetMaxValue(int value)
{
	this->maxValue = value;
}

const int& ProgressBar::GetMaxValue() const
{
	return this->maxValue;
}

void ProgressBar::SetCurrentValue(int value)
{
	this->currentValue = value;
	if (OnChangeValue != nullptr) {
		OnChangeValue(*this);
	}
}

const int& ProgressBar::GetCurrentValue() const
{
	return this->currentValue;
}

void ProgressBar::NextValue()
{
	currentValue++;
	if (OnChangeValue != nullptr) {
		OnChangeValue(*this);
	}
}

void ProgressBar::Finish()
{
	isFinished = true;
}

bool ProgressBar::IsFinished()
{
	return isFinished;
}

void ProgressBar::OnChangeValueHandler(std::function<void(ProgressBar&)> onChangeValue)
{
	this->OnChangeValue = onChangeValue;
}
