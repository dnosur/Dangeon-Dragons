#pragma once
#include "../ProgressBar.h"

#include <string>
#include "../../../../../Dodge/images/ImagesController.h"

class TextureProgressBar :
    public ProgressBar
{
	ImagesController images;

	void LoadImages(std::string_view path);

	void Initialize() override;
	void Draw() override;
public:
	TextureProgressBar(
		Coord pos, 
		Size size,
		std::string_view path, 
		int maxValue = 100, 
		int currentValue = 0, 
		bool isFinished = false
	);
	~TextureProgressBar() = default;

	void Update() override;
};

