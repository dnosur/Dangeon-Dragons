#pragma once
//В разработке 🙄

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

struct Coord;

#include "Character.h"
#include "../Color.h"

#include "../Shader.h"

class Font
{
	std::string title;
	std::string path;

	Size size;
	Size windowSize;

	glm::mat4 projection;

	std::map<char, Character> characters;

	std::unique_ptr<Shader> shader;

	bool loaded;

	bool LoadFont();
public:
	Font(
		std::string title, 
		std::string path, 
		Size windowSize = Size(1280, 720),
		Size size = Size(14, 14)
	);
	~Font();

	void RenderText(
		std::string text, 
		Coord pos, 
		float scale, 
		Color color = Color()
	);

	bool IsLoaded();
};

