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
	std::string title;
	std::string path;

	Size size;

	std::map<char, Character> characters;

	bool loaded;

	bool LoadFont();
public:
<<<<<<< Updated upstream
	Font(const char* title, const char* path, Size size = Size(14, 14));
=======
	Font(
		std::string title, 
		std::string path, 
		Size windowSize = Size(1280, 720),
		Size size = Size(14, 14)
	);
>>>>>>> Stashed changes
	~Font();

	void RenderText(std::string text, Coord pos, float scale, Color color = Color(0, 0, 0));

	bool IsLoaded();
};

