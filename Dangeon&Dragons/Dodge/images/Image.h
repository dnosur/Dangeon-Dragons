#pragma once
#include "../Shader.h"

#include "../Coord.h"
#include "../Size.h"

#include <vector>

class Image
{
	std::string title;
	std::string path;

	GLuint image;
	GLuint shader;

	Size size;

	Coord position;

	unsigned int VBO, VAO, EBO;

	void InitializeRender();

	void UpdateVertices();

	void SetPos(Coord& position);
public:
	Image();
	Image(std::string title, std::string path, GLint image, Size size, GLuint shader = 0);
	~Image();

	std::string_view GetTitle();

	std::string_view GetPath();

	const GLuint GetImage();

	const GLuint GetShader();
	void SetShader(GLuint& shader);

	const Size& GetSize();

	const Coord& GetPos();

	void Draw(Color color = Color(1.0f, 1.0f, 1.0f));
	void Draw(Coord& position, Color color = Color(1.0f, 1.0f, 1.0f));
	void Draw(Coord& position, Size& size, Color color = Color(1.0f, 1.0f, 1.0f));

	void SetSize(Size size);

	//Change render vertices
	void Resize(Size size);

	std::vector<float> GetRenderVertices();

	bool operator==(const Image& other) const;
	bool operator!=(const Image& other) const;

	Image& operator=(const Image& other);
};