#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Color.h"

#include "math/Mat4.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class Shader
{
	unsigned int id;

	char* vertexPath;
	char* fragmentPath;

	char* title;

	void Load();
	void CheckCompileErrors(unsigned int shader, std::string type);
public:
	Shader();
	Shader(std::string title, std::string vertexPath, std::string fragmentPath);
	~Shader();

	unsigned int GetID();
	char* GetTitle();

	char* GetVertexPath();
	char* GetFragmentPath();

	void Use();

	bool Undefined();

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetVec2(const char* name, float x, float y) const;
	void SetVec3(const char* name, float x, float y, float z) const;
	void SetVec4(const char* name, float x, float y, float z, float w) const;

	void SetMat4(const char* name, glm::mat4& matrix) const;

	void SetColor(const char* name, Color color);

	bool operator==(const Shader& other) const;
	bool operator!=(const Shader& other) const;
};
#endif