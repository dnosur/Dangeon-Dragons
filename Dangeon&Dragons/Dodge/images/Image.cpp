#include "Image.h"

#include "../Window.h"
#include "../shaders/ShadersController.h"

void Image::InitializeRender()
{
    std::vector<float> vertices = GetRenderVertices();

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //diffuse
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //normal
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //specular
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);

    //emissive
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Image::UpdateVertices()
{
    if (!VAO || !VBO || !EBO) {
		InitializeRender();
        return;
	}

    std::vector<float> vertices = GetRenderVertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr) {
        memcpy(ptr, vertices.data(), vertices.size() * sizeof(float));
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
}

void Image::SetPos(Coord& position)
{
    if (this->position == position) {
        return;
    }

	this->position = position;
	UpdateVertices();
}

Image::Image()
{
	image = -1;
	shader = 0;

	VBO = VAO = EBO = 0;
}

Image::Image(
	std::string title, 
	std::string path, 
	GLint image, 
	Size size, 
	GLuint shader
) : title(title), path(path), image(image), shader(shader), size(size)
{
	VBO = VAO = EBO = 0;
}

Image::~Image()
{
}

std::string_view Image::GetTitle()
{
    return title;
}

std::string_view Image::GetPath()
{
    return path;
}

const GLuint Image::GetImage()
{
    return image;
}

const GLuint Image::GetShader()
{
    return shader;
}

void Image::SetShader(GLuint& shader)
{
    this->shader = shader;
}

const Size& Image::GetSize()
{
    return size;
}

const Coord& Image::GetPos()
{
    return position;
}

void Image::Draw(Color color)
{
    if (!VAO || !VBO || !EBO) {
		InitializeRender();
	}

    ShadersController::Use(shader);
    ShadersController::SetInt(shader, "diffuseTexture", 0);
    ShadersController::SetVec4(shader, "diffuseColor", color.r, color.g, color.b, color.a);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glPopAttrib();

    ShadersController::Disable();
}

void Image::Draw(Coord& position, Color color)
{
    SetPos(position);

	if (!VAO || !VBO || !EBO) {
        InitializeRender();
	}

    ShadersController::Use(shader);
    ShadersController::SetInt(shader, "diffuseTexture", 0);
    ShadersController::SetVec4(shader, "diffuseColor", color.r, color.g, color.b, color.a);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glPopAttrib();

    ShadersController::Disable();
}

void Image::Draw(Coord& position, Size& size, Color color)
{
    if (this->position != position || this->size != size) {
		this->position = position;
		this->size = size;
		UpdateVertices();
	}

    if (!VAO || !VBO || !EBO) {
		InitializeRender();
    }

    ShadersController::Use(shader);
    ShadersController::SetInt(shader, "diffuseTexture", 0);
    ShadersController::SetVec4(shader, "diffuseColor", color.r, color.g, color.b, color.a);

   // glPushAttrib(GL_ALL_ATTRIB_BITS);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glPopAttrib();

    ShadersController::Disable();
}

void Image::SetSize(Size size)
{
    this->size = size;
}

void Image::Resize(Size size)
{
    this->size = size;
    UpdateVertices();
}

std::vector<float> Image::GetRenderVertices()
{
    const Size& windowSize = Window::GetSizeView();

    float normX = ((float)position.X / (float)windowSize.width) * 2.0f - 1.0f;
    float normY = ((float)position.Y / (float)windowSize.height) * 2.0f - 1.0f;

    float normW = ((float)size.width / (float)windowSize.width) * 2.0f;
    float normH = ((float)size.height / (float)windowSize.height) * 2.0f;

    return std::vector<float>{
        normX, normY, 0.0f,                 0.0f, 0.0f,
        normX + normW, normY, 0.0f,         1.0f, 0.0f,
        normX + normW, normY + normH, 0.0f, 1.0f, 1.0f,
        normX, normY + normH, 0.0f,         0.0f, 1.0f
    };
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
