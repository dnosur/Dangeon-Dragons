#include "BaseFigureMaterial.h"
#include "../../shaders/ShadersController.h"

BaseFigureMaterial::BaseFigureMaterial(
	Color ambient, Color diffuse, Color specular, Color emissive, 
	float shininess, float metalic, float roughness, float specularIntensity, 
	float emissiveIntensity, 

	GLuint shader,
	std::shared_ptr<Image> diffuseMap, 
	std::shared_ptr<Image> normalMap, 
	std::shared_ptr<Image> specularMap, 
	std::shared_ptr<Image> emissiveMap
) : Material(ambient, diffuse, specular, emissive, shininess, metalic, roughness, specularIntensity, emissiveIntensity, shader, diffuseMap, normalMap, specularMap, emissiveMap)
{
}

void BaseFigureMaterial::Use(IGameObject* gameObject)
{
	if (shader <= 0) {
		glUseProgram(0);
		return;
	}

	ShadersController::Use(shader);

	if (diffuseMap != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap->GetImage());
		ShadersController::SetInt(shader, "material.diffuseMap", 0);
	}

	if (normalMap != nullptr) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap->GetImage());
		ShadersController::SetInt(shader, "material.normalMap", 1);
	}

	if (specularMap != nullptr) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specularMap->GetImage());
		ShadersController::SetInt(shader, "material.specularMap", 2);
	}

	if (emissiveMap != nullptr) {
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, emissiveMap->GetImage());
		ShadersController::SetInt(shader, "material.emissiveMap", 3);
	}

	ShadersController::SetFloat(shader, "material.shininess", shininess);
	ShadersController::SetFloat(shader, "material.specularIntensity", specularIntensity);
	ShadersController::SetFloat(shader, "material.emissiveIntensity", emissiveIntensity);

	ShadersController::SetColor(shader, "material.ambient", ambient);
	ShadersController::SetColor(shader, "material.diffuse", diffuse);
	ShadersController::SetColor(shader, "material.specular", specular);
	ShadersController::SetColor(shader, "material.emissive", emissive);

	ShadersController::SetFloat(shader, "material.metalic", metalic);
	ShadersController::SetFloat(shader, "material.roughness", roughness);

	//Camera 
	if (camera) {
		ShadersController::SetBool(shader, "useCamera", false);

		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = camera->GetProjectionMatrix();

		ShadersController::SetMat4(shader, "camera.view", view);
		ShadersController::SetMat4(shader, "camera.projection", projection);
	}
}

void BaseFigureMaterial::Disable(IGameObject* gameObject)
{
	if (diffuseMap != nullptr) {
		ShadersController::SetInt(shader, "material.diffuseMap", -1);
	}

	if (normalMap != nullptr) {
		ShadersController::SetInt(shader, "material.normalMap", -1);
	}

	if (specularMap != nullptr) {
		ShadersController::SetInt(shader, "material.normalMap", -1);
	}

	if (emissiveMap != nullptr) {
		ShadersController::SetInt(shader, "material.normalMap", -1);
	}

	glUseProgram(0);
}
