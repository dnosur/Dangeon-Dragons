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

    for (wchar_t c = 0x0020; c <= 0x04FF; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph " << c << std::endl;
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

        characters.insert(std::pair<wchar_t, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    loaded = true;
    return true;
}

Font::Font(
    std::string title, 
    std::string path, 
    Size size
)
{
    this->title = title;
    this->path = path;

    this->size = size;

    const Size& windowSize = Window::GetRenderResolutionView();

    projection = glm::ortho(
        0.0f, 
        static_cast<float>(windowSize.width),
        0.0f, 
        static_cast<float>(windowSize.height)
    );

	loaded = false;

    shader = std::make_unique<Shader>(
        title,
        "Dodge/shaders/Font/vertex.vs", 
        "Dodge/shaders/Font/fragment.frag"
    );

	LoadFont();
}

Font::~Font()
{
}

void Font::RenderText(std::wstring text, Coord pos, float scale, Color color)
{
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader->Use();
    shader->SetVec4("textColor", color.r, color.g, color.b, color.a);
    shader->SetMat4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (wchar_t c : text)
    {
        if (!characters.count(c)) {
            continue;
        }

        Character ch = characters[c];

        float xpos = pos.X + ch.bearing.width * scale;
        float ypos = pos.Y - (ch.size.height - ch.bearing.height) * scale;

        float w = ch.size.width * scale;
        float h = ch.size.height * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.X += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

bool Font::IsLoaded()
{
    return loaded;
}
