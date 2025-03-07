#pragma once
#include "Shader.h"
#include "./images/Image.h"
#include "IGameObject.h"
#include "camera/Camera.h"

class Material
{
protected:
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;

	float shininess;
	float metalic;
	float roughness;
	float specularIntensity;
	float emissiveIntensity;

	GLuint shader;
	std::shared_ptr<Camera> camera;

	std::shared_ptr<Image> diffuseMap;
	std::shared_ptr<Image> normalMap;
	std::shared_ptr<Image> specularMap;
	std::shared_ptr<Image> emissiveMap;

	std::vector<Coord> diffuseMapVerticies;
	std::vector<Coord> normalMapVerticies;
	std::vector<Coord> specularMapVerticies;
	std::vector<Coord> emissiveMapVerticies;

public:
	Material(
		Color ambient = Color(0.0f, 0.0f, 0.0f, 1.0f),
		Color diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f),
		Color specular = Color(0.0f, 0.0f, 0.0f, 1.0f),
		Color emissive = Color(0.0f, 0.0f, 0.0f, 1.0f),

		float shininess = 1.0f, 
		float metalic = 0.0f, 
		float roughness = 0.0f,
		float specularIntensity = 1.0f,
		float emissiveIntensity = 1.0f,

		GLuint shader = 0,

		std::shared_ptr<Image> diffuseMap = nullptr,
		std::shared_ptr<Image> normalMap = nullptr,
		std::shared_ptr<Image> specularMap = nullptr,
		std::shared_ptr<Image> emissiveMap = nullptr,

		std::shared_ptr<Camera> camera = Window::GetCamera().lock(),

		std::vector<Coord> diffuseMapVerticies = std::vector<Coord>(),
		std::vector<Coord> normalMapVerticies = std::vector<Coord>(),
		std::vector<Coord> specularMapVerticies = std::vector<Coord>(),
		std::vector<Coord> emissiveMapVerticies = std::vector<Coord>()
	);

	void SetShader(const GLuint& shader);
	void SetCamera(std::shared_ptr<Camera> camera);
	void SetDiffuseMap(std::shared_ptr<Image> diffuseMap);
	void SetNormalMap(std::shared_ptr<Image> normalMap);
	void SetSpecularMap(std::shared_ptr<Image> specularMap);
	void SetEmissiveMap(std::shared_ptr<Image> emissiveMap);

	void SetAmbient(Color ambient);
	void SetDiffuse(Color diffuse);
	void SetSpecular(Color specular);
	void SetEmissive(Color emissive);

	void SetShininess(float shininess);
	void SetMetalic(float metalic);
	void SetRoughness(float roughness);
	void SetSpecularIntensity(float specularIntensity);
	void SetEmissiveIntensity(float emissiveIntensity);

	void SetDiffuseMapVerticies(std::vector<Coord>& diffuseMapVerticies);
	void SetNormalMapVerticies(std::vector<Coord> normalMapVerticies);
	void SetSpecularMapVerticies(std::vector<Coord> specularMapVerticies);
	void SetEmissiveMapVerticies(std::vector<Coord> emissiveMapVerticies);

	void SetDiffuseMapVerticies(std::pair<Coord, Coord> diffuseMapVerticies);
	void SetNormalMapVerticies(std::pair<Coord, Coord> normalMapVerticies);
	void SetSpecularMapVerticies(std::pair<Coord, Coord> specularMapVerticies);
	void SetEmissiveMapVerticies(std::pair<Coord, Coord> emissiveMapVerticies);

	Color GetAmbient();
	Color GetDiffuse();
	Color GetSpecular();
	Color GetEmissive();

	float GetShininess();
	float GetMetalic();
	float GetRoughness();
	float GetSpecularIntensity();
	float GetEmissiveIntensity();

	const GLuint& GetShader();
	std::weak_ptr<Camera> GetCamera();
	std::weak_ptr<Image> GetDiffuseMap();
	std::weak_ptr<Image> GetNormalMap();
	std::weak_ptr<Image> GetSpecularMap();
	std::weak_ptr<Image> GetEmissiveMap();

	std::vector<Coord> GetDiffuseMapVerticies();
	std::vector<Coord> GetNormalMapVerticies();
	std::vector<Coord> GetSpecularMapVerticies();
	std::vector<Coord> GetEmissiveMapVerticies();

	virtual void Use(IGameObject* gameObject) = 0;
	virtual void Disable(IGameObject* gameObject) = 0;

	bool operator==(const Material& other) const;
	bool operator!=(const Material& other) const;

	Material& operator=(const Material& other);
};