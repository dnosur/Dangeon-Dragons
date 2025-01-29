#pragma once
#include "../Shader.h"

#include "../Coord.h"
#include "../Size.h"

struct Image
{
	std::string title;
	std::string path;

	GLuint image;
	Shader* shader;

	Size size;

	Coord vertexes[2];

	Image();
	Image(std::string title, std::string path, GLint image, Size size, Shader* shader);
	~Image();

	bool operator==(const Image& other) const;
	bool operator!=(const Image& other) const;

	Image& operator=(const Image& other);
};