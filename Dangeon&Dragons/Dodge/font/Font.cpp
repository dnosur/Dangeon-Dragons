#include "Font.h"
#include "../functions.h"

bool Font::LoadFont()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, 14);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character(
            texture,
            Size(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Size(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint)face->glyph->advance.x
        );

        characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    loaded = true;
    return true;
}

<<<<<<< Updated upstream
Font::Font(const char* title, const char* path, Size size)
{
	copyStr(title, this->title);
	copyStr(path, this->path);
=======
Font::Font(
    std::string title, 
    std::string path, 
    Size windowSize, 
    Size size
)
{
    this->title = title;
    this->path = path;
>>>>>>> Stashed changes

    this->size = size;
	loaded = false;

	LoadFont();
}

Font::~Font()
{
}

void Font::RenderText(std::string text, Coord pos, float scale, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glEnable(GL_TEXTURE_2D);

    for (auto c : text) {
        Character ch = characters[c];

        float xpos = pos.X + ch.bearing.width * scale;
        float ypos = pos.Y - (ch.size.height - ch.bearing.height) * scale;

        float w = ch.size.width * scale;
        float h = ch.size.height * scale;

        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(xpos, ypos);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(xpos + w, ypos);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(xpos + w, ypos + h);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(xpos, ypos + h);
        glEnd();

        pos.X += (ch.advance >> 6) * scale;
    }

    glDisable(GL_TEXTURE_2D);
}

bool Font::IsLoaded()
{
    return loaded;
}
