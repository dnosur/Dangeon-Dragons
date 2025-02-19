#include "ImagesController.h"

#include "../shaders/ShadersController.h"

std::shared_ptr<Image> ImagesController::defaultImage;

int ImagesController::GetIndexByTitle(std::string_view title)
{
    auto it = images.find(std::string(title));
    return it != images.end() ? std::distance(images.begin(), it) : -1;
}

void ImagesController::ChangeIfExist(Image image)
{
    images[std::string(image.GetTitle())] = image;
}

void ImagesController::Draw(Image& item, Coord& position, Color& color, Size& size)
{
    item.Draw(position, size, color);
}

Image ImagesController::LoadImg(std::string_view path, std::string title)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path.data(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cout << "stbi_load error: " << stbi_failure_reason() << std::endl;
    }

    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
        return Image();
    }

    stbi_image_free(data);

    return Image(
        title,
        std::string(path),
        textureID,
        Size(
            width,
            height
        ),
        ShadersController::GetShaderID("BaseImage")
    );
}

void ImagesController::SetDefaultImage(std::unique_ptr<Image> image)
{
    defaultImage = std::move(image);
}

std::weak_ptr<Image> ImagesController::GetDafaultImage()
{
    return defaultImage;
}

void ImagesController::LoadFromFolder(std::string_view path)
{
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cerr << "Directory does not exist: " << path << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.path())) {
            std::string name = entry.path().filename().string();
            std::cout << "File: " << entry.path() << " " << name << std::endl;
            Load(entry.path().string().c_str(), name.c_str());
        }
    }
}

void ImagesController::Load(std::string_view path, std::string title, GLuint shader)
{
    Image image = ImagesController::LoadImg(path, title);
    if (shader) {
        image.SetShader(shader);
    }

    ChangeIfExist(image);
}

void ImagesController::LoadAndDrawImage(
    std::string_view path, std::string title,
    GLuint shader, Coord position,
    Size size
)
{
    Image image_obj = ImagesController::LoadImg(path, title);
    if (!image_obj.GetImage()) {
        return;
    }

    image_obj.Draw(position, size);

    ChangeIfExist(image_obj);
}

void ImagesController::DrawImage(std::string_view title, Coord position, Size size, Color color)
{
    const int index = GetIndexByTitle(title);
    if (index < 0) {
        return;
    }

    Draw(*this->operator[](index), position, color, size);
}

void ImagesController::DrawImage(Image*& image, Coord position, Size size, Color color)
{
    Draw(*image, position, color, size);
}

void ImagesController::DrawImage(std::weak_ptr<Image> image, Coord position, Size size, Color color)
{
    if (image.expired() || !image.lock()) {
        return;
    }

    Draw(*image.lock(), position, color, size);
}

const std::unordered_map<std::string, Image>& ImagesController::GetImages()
{
    return images;
}

void ImagesController::SetImages(std::vector<Image> images)
{
    Clear();
    for (Image& image : images) {
        this->images[std::string(image.GetTitle())] = image;
    }
}

int ImagesController::GetSize()
{
    return images.size();
}

void ImagesController::Clear()
{
    if (!images.size()) {
        return;
    }
    images.clear();
}

Image* ImagesController::operator[](int index)
{
    if (index < 0 || index >= GetSize()) {
        return nullptr;
    }
    auto it = images.begin();
    std::advance(it, index);
    return &it->second;
}

Image* ImagesController::operator[](std::string_view title)
{
    auto it = images.find(std::string(title));
    return it != images.end() ? &it->second : nullptr;
}
