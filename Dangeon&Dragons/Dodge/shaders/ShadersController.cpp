#include "ShadersController.h"
#include <glm/gtc/type_ptr.hpp>

std::unique_ptr<
	std::unordered_map<GLuint, std::unique_ptr<Shader>>
> ShadersController::shaders = std::make_unique<std::unordered_map<GLuint, std::unique_ptr<Shader>>>();

void ShadersController::LoadShader(std::unique_ptr<Shader> shader)
{
	shaders->operator[](shader->GetID()) = std::move(shader);
}

void ShadersController::LoadShader(std::string title, std::string vertexPath, std::string fragmentPath)
{
	std::unique_ptr<Shader> shader = std::make_unique<Shader>(title, vertexPath, fragmentPath);
	shaders->operator[](shader->GetID()) = std::move(shader);
}

Shader* ShadersController::GetShader(GLuint id)
{
	auto it = shaders->find(id);
	if (it != shaders->end())
		return it->second.get();
	return nullptr;
}

const GLuint& ShadersController::GetShaderID(std::string_view title)
{
	for (auto& shader : *shaders)
		if (shader.second->GetTitle() == title)
			return shader.first;
	return -1;
}

void ShadersController::Use(GLuint id)
{
	glUseProgram(id);
}

void ShadersController::SetBool(const GLuint& id, const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void ShadersController::SetInt(const GLuint& id, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(id, name), value);
}

void ShadersController::SetFloat(const GLuint& id, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(id, name), value);
}

void ShadersController::SetVec2(const GLuint& id, const char* name, float x, float y)
{
	glUniform2f(glGetUniformLocation(id, name), x, y);
}

void ShadersController::SetVec3(const GLuint& id, const char* name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void ShadersController::SetVec4(const GLuint& id, const char* name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void ShadersController::SetMat4(const GLuint& id, const char* name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShadersController::SetColor(const GLuint& id, const char* name, Color color)
{
	SetVec4(id, name, color.r, color.g, color.b, color.a);
}
