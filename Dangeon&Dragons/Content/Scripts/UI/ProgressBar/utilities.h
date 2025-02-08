#pragma once
#include <memory>
#include "ProgressBar.h"

void SetProgressBarValue(std::weak_ptr<ProgressBar> progressBar, int value);

void NextProgressBarValue(std::weak_ptr<ProgressBar> progressBar);