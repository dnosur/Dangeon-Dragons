#include "RenderInstance.h"
#include <glad/glad.h>

void RenderInstance::UpdateVertices()
{
    GenerateVertices();
    if (!VBO || !VAO || !EBO) {
        return Initialize();
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr) {
        memcpy(ptr, vertices.data(), vertices.size() * sizeof(float));
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
}

void RenderInstance::UpdateVertices(std::vector<float> vertices)
{
    this->vertices = vertices;
    if (!VBO || !VAO || !EBO) {
        return Initialize();
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr) {
        memcpy(ptr, vertices.data(), vertices.size() * sizeof(float));
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
}

RenderInstance::RenderInstance()
	: VBO(0), VAO(0), EBO(0)
{
}

RenderInstance::RenderInstance(unsigned int VBO, unsigned int VAO, unsigned int EBO)
	: VBO(VBO), VAO(VAO), EBO(EBO)
{
}

void RenderInstance::SetVBO(unsigned int& VBO)
{
    this->VBO = VBO;
}

void RenderInstance::SetVAO(unsigned int& VAO)
{
    this->VAO = VAO;
}

void RenderInstance::SetEBO(unsigned int& EBO)
{
    this->EBO = EBO;
}

const unsigned int& RenderInstance::GetVBO()
{
    return VBO;
}

const unsigned int& RenderInstance::GetVAO()
{
    return VAO;
}

const unsigned int& RenderInstance::GetEBO()
{
    return EBO;
}

const std::vector<float>& RenderInstance::GetVertices()
{
    return vertices;
}

void RenderInstance::SetVertices(std::vector<float> vertices)
{
    this->vertices = vertices;
}

bool RenderInstance::IsInitialized()
{
    return VAO && VBO && EBO;
}

bool RenderInstance::operator==(RenderInstance& other)
{
    return VAO = other.VAO && VBO == other.VBO && EBO == other.EBO && 
        vertices == other.vertices;
}
