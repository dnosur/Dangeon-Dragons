#include "BaseFigureMaterial.h"

BaseFigureMaterial::BaseFigureMaterial(Color ambient, Color diffuse, Color specular, Color emissive, float shininess, float metalic, float roughness, float specularIntensity, float emissiveIntensity, Shader* shader, Image* diffuseMap, Image* normalMap, Image* specularMap, Image* emissiveMap)
	: Material(ambient, diffuse, specular, emissive, shininess, metalic, roughness, specularIntensity, emissiveIntensity, shader, diffuseMap, normalMap, specularMap, emissiveMap)
{
}

BaseFigureMaterial::~BaseFigureMaterial()
{
}

void BaseFigureMaterial::Use(IGameObject* gameObject)
{
	if (shader == nullptr) {
		glUseProgram(0);
		return;
	}

	shader->Use();

	if (diffuseMap != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap->image);
		shader->SetInt("material.diffuseMap", 0);
	}

	if (normalMap != nullptr) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap->image);
		shader->SetInt("material.normalMap", 1);
	}

	if (specularMap != nullptr) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specularMap->image);
		shader->SetInt("material.specularMap", 2);
	}

	if (emissiveMap != nullptr) {
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, emissiveMap->image);
		shader->SetInt("material.emissiveMap", 3);
	}

	shader->SetFloat("material.shininess", shininess);
	shader->SetFloat("material.specularIntensity", specularIntensity);
	shader->SetFloat("material.emissiveIntensity", emissiveIntensity);

	shader->SetColor("material.ambient", ambient);
	shader->SetColor("material.diffuse", diffuse);
	shader->SetColor("material.specular", specular);
	shader->SetColor("material.emissive", emissive);

	shader->SetFloat("material.metalic", metalic);
	shader->SetFloat("material.roughness", roughness);
}

void BaseFigureMaterial::Disable(IGameObject* gameObject)
{
	if (diffuseMap != nullptr) {
		shader->SetInt("material.diffuseMap", -1);
	}

	if (normalMap != nullptr) {
		shader->SetInt("material.normalMap", -1);
	}

	if (specularMap != nullptr) {
		shader->SetInt("material.normalMap", -1);
	}

	if (emissiveMap != nullptr) {
		shader->SetInt("material.normalMap", -1);
	}

	glUseProgram(0);
}
