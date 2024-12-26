#pragma once
#include <memory>

#include "../Shader.h"

#include "../Coord.h"
#include "../Size.h"

struct Image
{
	char* title;
	char* path;

	GLuint image;
	std::unique_ptr<Shader> shader;

	Size size;

	Coord vertexes[2];

	Image();
	Image(const char* title, const char* path, GLint image, Size size, Shader* shader);
	Image(const Image& other);
	~Image();

	bool operator==(const Image& other) const;
	bool operator!=(const Image& other) const;

	Image& operator=(const Image& other) noexcept;
};