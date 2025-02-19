#pragma once
#include "../ProgressBar.h"

#include <string>
#include "../../../../../Dodge/images/ImagesController.h"

class TextureProgressBar :
    public ProgressBar
{
	std::unique_ptr<ImagesController> images;
	std::unique_ptr<Color> color;

	void LoadImages(std::string_view path);

	void Initialize() override;
	void Draw() override;
public:
	TextureProgressBar(
		Coord position,
		Size size,
		std::string_view path,
		int maxValue = 100,
		int currentValue = 0,
		bool isFinished = false,
		std::unique_ptr<Color> color = std::make_unique<Color>(1, 1, 1)
	);
	~TextureProgressBar() = default;

	void Update() override;
};

