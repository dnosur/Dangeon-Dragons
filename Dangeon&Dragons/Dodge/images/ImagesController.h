#pragma once
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>
#include <GL/freeglut.h>

#include <vector>
#include <unordered_map>
#include <filesystem>

#include <functional>

#include "../Size.h"
#include "../Coord.h"
#include "Image.h"

#include "../lib/stb_image.h"
#include "../Color.h"

namespace fs = std::filesystem;

class ImagesController
{
	std::unordered_map<std::string, Image> images;

	static std::shared_ptr<Image> defaultImage;

	int GetIndexByTitle(std::string_view title);
	void ChangeIfExist(Image image);

	void Draw(Image& item, Coord& position, Color& color, Size& size);
public:
	static Image LoadImg(std::string_view path, std::string title);

	static void SetDefaultImage(std::unique_ptr<Image> image);
	static std::weak_ptr<Image> GetDafaultImage();

	void LoadFromFolder(std::string_view path);

	void Load(std::string_view path, std::string title, GLuint shader = 0);
	void LoadAndDrawImage(std::string_view path, std::string title, GLuint shader, Coord position, Size size);

	void DrawImage(std::string_view title, Coord position, Size size, Color color = Color(1.0f, 1.0f, 1.0f));
	void DrawImage(Image*& image, Coord position, Size size, Color color = Color(1.0f, 1.0f, 1.0f));
	void DrawImage(std::weak_ptr<Image> image, Coord position, Size size, Color color = Color(1.0f, 1.0f, 1.0f));

	const std::unordered_map<std::string, Image>& GetImages();
	void SetImages(std::vector<Image> images);

	int GetSize();

	void Clear();

	Image* operator[](int index);
	Image* operator[](std::string_view title);
};