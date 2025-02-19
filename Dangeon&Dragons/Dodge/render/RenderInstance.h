#pragma once
struct RenderInstance
{
	unsigned int VBO, VAO, EBO;

	RenderInstance();
	RenderInstance(unsigned int VBO, unsigned int VAO, unsigned int EBO);

	int GetId();

	bool operator == (RenderInstance other);
};