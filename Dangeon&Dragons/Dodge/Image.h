#pragma once
#include "Shader.h"

struct Image
{
	char* title;
	char* path;

	GLuint image;
	Shader* shader;

	Image();
	Image(const char* title, const char* path, GLint image, Shader* shader);
	~Image();

	bool operator==(const Image& other) const;
	bool operator!=(const Image& other) const;

	Image& operator=(const Image& other);
};