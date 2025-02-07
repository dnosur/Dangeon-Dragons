#pragma once
#include "Font.h"

#include <unordered_map>

class Fonts
{
	static std::unordered_map<std::string, std::unique_ptr<Font>> fonts;
public:
	static void LoadFont(std::string title, std::string path, Size size = Size(14, 14));
	static Font* GetFont(std::string title);
};