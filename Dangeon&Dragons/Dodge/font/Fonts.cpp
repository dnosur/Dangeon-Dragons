#include "Fonts.h"

std::unordered_map<std::string, std::unique_ptr<Font>> Fonts::fonts;

void Fonts::LoadFont(std::string title, std::string path, Size size)
{
	auto it = fonts.find(title);
	if (it == fonts.end()) {
		fonts[title] = std::make_unique<Font>(title, std::move(path), size);
		return;
	}

	std::cout << "Font '" << title << "' is already loaded!" << std::endl;
}

Font* Fonts::GetFont(std::string title)
{
	auto it = fonts.find(title);
	if (it != fonts.end()) {
		return it->second.get();
	}

	return nullptr;
}
