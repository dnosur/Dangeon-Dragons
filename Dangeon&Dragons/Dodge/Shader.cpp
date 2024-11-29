#include "Shader.h"

void Shader::Load()
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;

    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // shader Program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        return;
    }

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

Shader::Shader()
{
    vertexPath = fragmentPath = title = (char*)"undefined";
    id = 0;
}

Shader::Shader(const char* title, const char* vertexPath, const char* fragmentPath)
{
    this->title = new char[strlen(title) + 1];
    strcpy_s(this->title, strlen(title) + 1, title);

    this->vertexPath = new char[strlen(vertexPath) + 1];
    strcpy_s(this->vertexPath, strlen(vertexPath) + 1, vertexPath);

    this->fragmentPath = new char[strlen(fragmentPath) + 1];
    strcpy_s(this->fragmentPath, strlen(fragmentPath) + 1, fragmentPath);

	Load();
}

Shader::~Shader()
{
    if (id != 0 && this != NULL)
	{
		glDeleteProgram(id);
		id = 0;
	}
}

unsigned int Shader::GetID()
{
    return id;
}

char* Shader::GetTitle()
{
    return title;
}

char* Shader::GetVertexPath()
{
    return vertexPath;
}

char* Shader::GetFragmentPath()
{
    return fragmentPath;
}

void Shader::Use()
{
    if (this == nullptr || Undefined()) {
		return glUseProgram(0);
	}
    glUseProgram(id);
}

bool Shader::Undefined()
{
    if (!strlen(vertexPath) || !strlen(fragmentPath)) {
        return true;
    }

    if (!strcmp(vertexPath, "undefined") || !strcmp(fragmentPath, "undefined")) {
        return true;
    }

	return false;
}

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::SetVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::SetVec3(const char* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::SetVec4(const char* name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void Shader::SetColor(const char* name, Color color)
{
	SetVec4(name, color.r, color.g, color.b, color.a);
}

bool Shader::operator==(const Shader& other) const
{
    return !strcmp(title, other.title) && !strcmp(vertexPath, other.vertexPath) && 
        !strcmp(fragmentPath, other.fragmentPath) && id == other.id;
}

bool Shader::operator!=(const Shader& other) const
{
    return !(*this == other);
}
