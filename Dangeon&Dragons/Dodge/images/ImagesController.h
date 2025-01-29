#pragma once
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>
#include <GL/freeglut.h>
#include <vector>

#include "../Size.h"
#include "../Coord.h"
#include "Image.h"

#include "../lib/stb_image.h"
#include "../Color.h"

class ImagesController
{
	std::vector<Image> images;

	static std::shared_ptr<Image> defaultImage;

	int GetIndexByTitle(std::string& title);
	void ChangeIfExist(Image image);

	void Draw(Image& item, Coord& position, Color& color, Size& windowSize, Size& size, bool reverse = false);
public:
	static Image LoadImg(std::string path, std::string title);

	static void SetDefaultImage(std::unique_ptr<Image> image);
	static std::weak_ptr<Image> GetDafaultImage();

	void Load(std::string path, std::string title, Shader* shader = nullptr);
	void LoadAndDrawImage(std::string path, std::string title, Shader* shader, Coord position, Size size, Size windowSize);

	void DrawImage(std::string title, Coord position, Size size, Size windowSize, Color color = Color(1.0f, 1.0f, 1.0f), bool reverse = false);

	std::vector<Image> GetImages();
	void SetImages(std::vector<Image> images);

	int GetSize();

	void Clear();

	Image* operator[](int index);
	Image* operator[](std::string title);
};