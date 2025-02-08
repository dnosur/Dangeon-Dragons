#pragma once
#include "../../../../Dodge/Coord.h"
#include "../../../../Dodge/Size.h"

#include <functional>

class ProgressBar
{
	Coord pos;
	Size size;

	int maxValue;
	int currentValue;
	bool isFinished;

	std::function<void(ProgressBar&)> OnChangeValue;

	virtual void Draw() = 0;
	virtual void Initialize() = 0;
public:
	ProgressBar(
		Coord pos, Size size, 
		int maxValue = 100, int currentValue = 0, bool isFinished = false
	);
	~ProgressBar() = default;

	void SetPos(Coord pos);
	const Coord& GetPos() const;

	void SetSize(Size size);
	const Size& GetSize() const;

	void SetMaxValue(int value);
	const int& GetMaxValue() const;

	void SetCurrentValue(int value);
	const int& GetCurrentValue() const;

	void NextValue();

	void Finish();
	bool IsFinished();

	void OnChangeValueHandler(std::function<void(ProgressBar&)> onChangeValue);

	virtual void Update() = 0;
};