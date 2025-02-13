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
#include "../Window.h"
#include "FontRenderOptions.h"

class Font
{
	std::string title;
	std::string path;

	Size size;

	glm::mat4 projection;

	std::map<wchar_t, Character> characters;

	GLuint shader;

	bool loaded;

	bool LoadFont();
public:
	Font(
		std::string title, 
		std::string path, 
		Size size = Size(14, 14)
	);
	~Font();

	void RenderText(
		std::wstring text, 
		Coord pos, 
		std::unique_ptr<FontRenderOptions> options = std::make_unique<FontRenderOptions>()
	);

	bool IsLoaded();
};

