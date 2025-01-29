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

<<<<<<< Updated upstream
	int GetIndexByTitle(char* title);
=======
	static std::shared_ptr<Image> defaultImage;

	int GetIndexByTitle(std::string& title);
>>>>>>> Stashed changes
	void ChangeIfExist(Image image);

	void Draw(Image& item, Coord& position, Color& color, Size& windowSize, Size& size, bool reverse = false);
public:
	static Image LoadImg(std::string path, std::string title);

<<<<<<< Updated upstream
	void Load(const char* path, const char* title, Shader* shader = nullptr);
	void LoadAndDrawImage(const char* path, const char* title, Shader* shader, Coord position, Size size, Size windowSize);
=======
	static void SetDefaultImage(std::unique_ptr<Image> image);
	static std::weak_ptr<Image> GetDafaultImage();

	void Load(std::string path, std::string title, Shader* shader = nullptr);
	void LoadAndDrawImage(std::string path, std::string title, Shader* shader, Coord position, Size size, Size windowSize);
>>>>>>> Stashed changes

	void DrawImage(std::string title, Coord position, Size size, Size windowSize, Color color = Color(1.0f, 1.0f, 1.0f), bool reverse = false);

	std::vector<Image> GetImages();
	void SetImages(std::vector<Image> images);

	int GetSize();

	void Clear();

	Image* operator[](int index);
	Image* operator[](std::string title);
};