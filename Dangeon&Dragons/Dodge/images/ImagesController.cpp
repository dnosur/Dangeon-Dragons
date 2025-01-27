#include "ImagesController.h"

std::shared_ptr<Image> ImagesController::defaultImage;

int ImagesController::GetIndexByTitle(char* title)
{
    int index = 0;
    for (Image& img : images) {
        if (!strcmp(title, img.title)) {
            return index;
        }
        index++;
    }

    return -1;
}

void ImagesController::ChangeIfExist(Image image)
{
    if (image.title == nullptr) {
        return;
    }

    const int index = GetIndexByTitle(image.title);
    if (index < 0) {
        images.push_back(image);
        return;
    }

    images[index] = image;
}

void ImagesController::Draw(Image& item, Coord& position, Color& color, Size& windowSize, Size& size, bool reverse)
{
    const GLuint image = item.image;

    float normX = (position.X / (float)windowSize.GetWidth()) * 2.0f - 1.0f;
    float normY = !reverse 
        ? (position.Y / (float)windowSize.GetHeight()) * 2.0f - 1.0f 
        : 1.0f - (position.Y / (float)windowSize.GetHeight()) * 2.0f;
    float normW = (size.width / (float)windowSize.GetWidth()) * 2.0f;
    float normH = (size.height / (float)windowSize.GetHeight()) * 2.0f;

    // Вершины и текстурные координаты
    float vertices[] = {
        // Позиции           // Текстурные координаты
        normX, normY, 0.0f,                 0.0f, 0.0f,  // Левый нижний угол
        normX + normW, normY, 0.0f,         1.0f, 0.0f,  // Правый нижний угол
        normX + normW, normY + normH, 0.0f, 1.0f, 1.0f,  // Правый верхний угол
        normX, normY + normH, 0.0f,         0.0f, 1.0f   // Левый верхний угол
    };

    unsigned int indices[] = {
        0, 1, 2, // Первый треугольник
        2, 3, 0  // Второй треугольник
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image);

    item.shader->Use();
    item.shader->SetInt("diffuseTexture", 0);
    item.shader->SetVec4("diffuseColor", color.r, color.g, color.b, color.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glUseProgram(0);
}

Image ImagesController::LoadImg(const char* path, const char* title)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
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
        path,
        textureID,
        Size(
            width,
            height
        ),
        new Shader(
            title,
            "Dodge/shaders/Image/imageVertex.vs",
            "Dodge/shaders/Image/imageFragment.frag"
        ));
}

void ImagesController::SetDefaultImage(std::unique_ptr<Image> image)
{
    defaultImage = std::move(image);
}

std::weak_ptr<Image> ImagesController::GetDafaultImage()
{
    return defaultImage;
}

void ImagesController::Load(const char* path, const char* title, Shader* shader)
{
    Image image = ImagesController::LoadImg(path, title);
    if (shader != nullptr) {
        image.shader = shader;
    }

    ChangeIfExist(image);
}

void ImagesController::LoadAndDrawImage(
    const char* path, const char* title, 
    Shader* shader, Coord position, 
    Size size, Size windowSize
)
{
    Image image_obj = ImagesController::LoadImg(path, title);
    if (!image_obj.image) {
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image_obj.image);


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glad_glOrtho(0, windowSize.GetWidth(), windowSize.GetHeight(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    shader->Use();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(position.X, position.Y); // Левый нижний угол
    glTexCoord2f(1.0f, 0.0f); glVertex2f(position.X + size.width, position.Y); // Правый нижний угол
    glTexCoord2f(1.0f, 1.0f); glVertex2f(position.X + size.width, position.Y + size.height); // Правый верхний угол
    glTexCoord2f(0.0f, 1.0f); glVertex2f(position.X, position.Y + size.height); // Левый верхний угол
    glEnd();


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);

    ChangeIfExist(image_obj);
}

void ImagesController::DrawImage(const char* title, Coord position, Size size, Size windowSize, Color color, bool reverse)
{
    const int index = GetIndexByTitle((char*)title);
    if (index < 0) {
        return;
    }

    Draw(images[index], position, color, windowSize, size, reverse);
}

std::vector<Image> ImagesController::GetImages()
{
    return images;
}

void ImagesController::SetImages(std::vector<Image> images)
{
    Clear();
    for (Image& image : images) {
        this->images.push_back(image);
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
    return &images[index];
}

Image* ImagesController::operator[](const char* title)
{
    for (Image& image : images) {
        if (!strcmp(title, image.title)) {
            return &image;
        }
    }
    return nullptr;
}
