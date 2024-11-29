#pragma once
//В разработке 🙄

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

struct Coord;

#include "Character.h"
#include "../Color.h"

class Font
{
	char* title;
	char* path;

	Size size;

	std::map<char, Character> characters;

	bool loaded;

	bool LoadFont();
public:
	Font(const char* title, const char* path, Size size = Size(14, 14));
	~Font();

	void RenderText(std::string text, Coord pos, float scale, Color color = Color(0, 0, 0));

	bool IsLoaded();
};

