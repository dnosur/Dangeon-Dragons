#include "utilities.h"

void SetProgressBarValue(std::weak_ptr<ProgressBar> progressBar, int value)
{
	if (progressBar.lock() != nullptr) {
		progressBar.lock()->SetCurrentValue(value);
	}
}

void NextProgressBarValue(std::weak_ptr<ProgressBar> progressBar)
{
	if (progressBar.lock() != nullptr) {
		progressBar.lock()->NextValue();
	}
}
