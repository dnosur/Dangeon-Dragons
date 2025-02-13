#pragma once
#include "../Shader.h"

#include <unordered_map>
#include <memory>

class ShadersController
{
	static std::unique_ptr<
		std::unordered_map<GLuint, std::unique_ptr<Shader>>
	> shaders;

public:
	static void LoadShader(std::unique_ptr<Shader> shader);
	static void LoadShader(std::string title, std::string vertexPath, std::string fragmentPath);

	static Shader* GetShader(GLuint id);

	static const GLuint& GetShaderID(std::string_view title);

	static void Use(GLuint id);

	static void SetBool(const GLuint& id, const char* name, bool value);
	static void SetInt(const GLuint& id, const char* name, int value);
	static void SetFloat(const GLuint& id, const char* name, float value);
	static void SetVec2(const GLuint& id, const char* name, float x, float y);
	static void SetVec3(const GLuint& id, const char* name, float x, float y, float z);
	static void SetVec4(const GLuint& id, const char* name, float x, float y, float z, float w);

	static void SetMat4(const GLuint& id, const char* name, glm::mat4& matrix);

	static void SetColor(const GLuint& id, const char* name, Color color);
};