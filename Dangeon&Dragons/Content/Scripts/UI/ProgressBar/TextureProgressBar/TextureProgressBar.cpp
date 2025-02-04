#include "TextureProgressBar.h"
#include "../../../../../Dodge/utilities/string.h"

void TextureProgressBar::LoadImages(std::string_view path)
{
	if (!fs::exists(path) || !fs::is_directory(path)) {
		std::cerr << "Directory does not exist: " << path << std::endl;
		return;
	}

	std::vector<std::filesystem::path> links;
	for (const auto& entry : fs::directory_iterator(path)) {
		if (fs::is_regular_file(entry.path())) {
			links.push_back(entry.path());
		}
	}

	std::sort(links.begin(), links.end(), [](const std::filesystem::path& a, const std::filesystem::path& b) {
		return NaturalCompare(a.filename().string(), b.filename().string());
	});

	for (const auto& link : links) {
		images.Load(link.string().c_str(), link.filename().string().c_str());
	}
}

void TextureProgressBar::Initialize()
{
}

//18 - все картинки
//

void TextureProgressBar::Draw()
{
	const int index = (float)((float)images.GetSize() / (float)GetMaxValue()) * (GetCurrentValue() + 1);
	images.DrawImage(images[index ? index - 1 : index]->title, GetPos(), GetSize(), Size(1280, 720));

	if (index == images.GetSize()) {
		Finish();
	}
}

TextureProgressBar::TextureProgressBar(
	Coord pos, 
	Size size,
	std::string_view path, 
	int maxValue, 
	int currentValue, 
	bool isFinished
) : ProgressBar(pos, size, maxValue, currentValue, isFinished)
{
	LoadImages(path);
}

void TextureProgressBar::Update()
{
	Draw();
}
