#pragma once
#include <vector>

class RenderInstance
{
protected:
	unsigned int VBO, VAO, EBO;
	std::vector<float> vertices;
private:
	virtual void GenerateVertices() = 0;
public:
	RenderInstance();
	RenderInstance(unsigned int VBO, unsigned int VAO, unsigned int EBO);
	~RenderInstance() = default;

	virtual void Initialize() = 0;

	void UpdateVertices();
	void UpdateVertices(std::vector<float> vertices);

	void SetVBO(unsigned int& VBO);
	void SetVAO(unsigned int& VAO);
	void SetEBO(unsigned int& EBO);

	const unsigned int& GetVBO();
	const unsigned int& GetVAO();
	const unsigned int& GetEBO();

	const std::vector<float>& GetVertices();
	void SetVertices(std::vector<float> vertices);

	virtual void Render() = 0;

	bool IsInitialized();

	bool operator == (RenderInstance& other);
};