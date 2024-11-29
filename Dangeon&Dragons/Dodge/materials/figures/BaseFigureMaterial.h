#pragma once
#include "../../Material.h"

class BaseFigureMaterial
	: public Material
{
public:
	BaseFigureMaterial(
		Color ambient = Color(0.0f, 0.0f, 0.0f, 1.0f),
		Color diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f),
		Color specular = Color(0.0f, 0.0f, 0.0f, 1.0f),
		Color emissive = Color(0.0f, 0.0f, 0.0f, 1.0f),

		float shininess = 1.0f,
		float metalic = 0.0f,
		float roughness = 0.0f,
		float specularIntensity = 1.0f,
		float emissiveIntensity = 1.0f,

		Shader* shader = nullptr,

		Image* diffuseMap = nullptr,
		Image* normalMap = nullptr,
		Image* specularMap = nullptr,
		Image* emissiveMap = nullptr
	);
	~BaseFigureMaterial();

	void Use(IGameObject* gameObject) override;

	void Disable(IGameObject* gameObject) override;
};