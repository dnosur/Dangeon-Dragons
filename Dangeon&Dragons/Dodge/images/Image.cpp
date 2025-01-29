#include "Image.h"

Image::Image()
{
	image = -1;
	shader = new Shader();
}

Image::Image(
	std::string title, 
	std::string path, 
	GLint image, 
	Size size, 
	Shader* shader
) : title(title), path(path), image(image), shader(shader), size(size)
{
}

Image::~Image()
{
}

bool Image::operator==(const Image& other) const
{
	return other.title == this->title && 
		other.path == this->path &&
		other.image == image && 
		other.shader == shader;
}

bool Image::operator!=(const Image& other) const
{
	return !(*this == other);
}

Image& Image::operator=(const Image& other)
{
    if (this == &other) {
        return *this;
    }

	this->title = other.title;
	this->path = other.path;
	this->size = other.size;

	this->image = other.image;
	this->shader = other.shader;
    return *this;
}
