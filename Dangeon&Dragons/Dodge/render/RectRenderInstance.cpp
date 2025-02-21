#include "RectRenderInstance.h"
#include "../Material.h"

std::vector<unsigned int> defaultIndicies1 = {
    0, 1, 2,
    2, 3, 0
};

void RectRenderInstance::GenerateVertices()
{
    const bool isHasDiffuseVertexs =
        material->GetDiffuseMapVerticies().size() >= 2 &&
        material->GetDiffuseMap().lock() != nullptr;
    const Coord& textCoord1 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[0] : Coord(0, 0);
    const Coord& textCoord2 = isHasDiffuseVertexs ? material->GetDiffuseMapVerticies()[1] : Coord(1, 1);

    SetVertices(std::vector<float>{
        // positions         // colors
         (float)vertex1.X, (float)vertex1.Y, 0.0f,  (float)textCoord1.X,(float)textCoord1.Y,
         (float)vertex2.X, (float)vertex1.Y, 0.0f, (float)textCoord2.X, (float)textCoord1.Y,
         (float)vertex2.X, (float)vertex2.Y, 0.0f,  (float)textCoord2.X,(float)textCoord2.Y,
         (float)vertex1.X, (float)vertex2.Y, 0.0f,  (float)textCoord1.X, (float)textCoord2.Y
    });
}

void RectRenderInstance::Initialize()
{
    GenerateVertices();
    InitQuads(VAO, VBO, EBO, vertices);
}

RectRenderInstance::RectRenderInstance()
    : RenderInstance()
{
    vertex1 = Coord();
	vertex2 = Coord();
}

RectRenderInstance::RectRenderInstance(Coord vertex1, Coord vertex2)
    : RenderInstance()
{
    SetVertexes(vertex1, vertex2);
    this->material = nullptr;
}

RectRenderInstance::RectRenderInstance(std::shared_ptr<Material> material)
    : RenderInstance()
{
    this->material = std::move(material);
}

RectRenderInstance::RectRenderInstance(unsigned int VAO, unsigned int VBO, unsigned int EBO)
    : RenderInstance(VBO, VAO, EBO)
{
    this->material = nullptr;
}

void RectRenderInstance::InitQuads(
    unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, 
    std::vector<float>& vertices, std::vector<unsigned int>& indices
){
    if (VAO || VBO || EBO) {
        return;
    }

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // Передаём данные вершин в OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Передаём индексы вершин в OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Определяем атрибуты вершин
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Атрибут текстурных координат
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
 
void RectRenderInstance::SetVertexes(Coord vertex1, Coord vertex2)
{
    this->vertex1 = vertex1;
	this->vertex2 = vertex2;
}

const Coord& RectRenderInstance::GetVertex1()
{
    return vertex1;
}

void RectRenderInstance::SetVertex1(Coord vertex1)
{
    this->vertex1 = vertex1;
}

const Coord& RectRenderInstance::GetVertex2()
{
    return vertex2;
}

void RectRenderInstance::SetVertex2(Coord vertex2)
{
    this->vertex2 = vertex2;
}

std::weak_ptr<Material> RectRenderInstance::GetMaterial()
{
    return material;
}

void RectRenderInstance::SetMaterial(std::shared_ptr<Material> material)
{
    this->material = material;
}

void RectRenderInstance::MoveMaterial(std::shared_ptr<Material> material)
{
    this->material = std::move(material);
}

void RectRenderInstance::Render()
{
    if (!VBO && !VAO && !EBO) {
        Initialize();
    }

    material->Use(nullptr);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glPopAttrib();

    material->Disable(nullptr);
}

bool RectRenderInstance::operator==(RectRenderInstance& other)
{
    return vertex1 == other.vertex1 && vertex2 == other.vertex2 &&
        *material == *other.material &&
        VBO == other.VBO && VAO == other.VAO && EBO == other.EBO &&
        vertices == other.vertices;
}
