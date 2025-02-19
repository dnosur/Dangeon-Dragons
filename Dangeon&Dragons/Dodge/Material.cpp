#include "Material.h"

Material::Material(
	Color ambient, Color diffuse, Color specular, Color emissive, 
	float shininess, float metalic, float roughness, 
	float specularIntensity, float emissiveIntensity, 
	GLuint shader,

	std::shared_ptr<Image> diffuseMap, 
	std::shared_ptr<Image> normalMap, 
	std::shared_ptr<Image> specularMap, 
	std::shared_ptr<Image> emissiveMap,

	std::vector<Coord> diffuseMapVerticies, std::vector<Coord> normalMapVerticies,
	std::vector<Coord> specularMapVerticies,std::vector<Coord> emissiveMapVerticies
)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->emissive = emissive;

	this->shininess = shininess;
	this->metalic = metalic;
	this->roughness = roughness;
	this->specularIntensity = specularIntensity;
	this->emissiveIntensity = emissiveIntensity;

	this->shader = shader;

	this->diffuseMap = diffuseMap;
	this->normalMap = normalMap;
	this->specularMap = specularMap;
	this->emissiveMap = emissiveMap;

	this->diffuseMapVerticies = diffuseMapVerticies;
	this->normalMapVerticies = normalMapVerticies;
	this->specularMapVerticies = specularMapVerticies;
	this->emissiveMapVerticies = emissiveMapVerticies;
}

void Material::SetShader(const GLuint& shader)
{
	this->shader = shader;
}

void Material::SetCamera(std::shared_ptr<Camera> camera)
{
	this->camera = camera;
}

void Material::SetDiffuseMap(std::shared_ptr<Image> diffuseMap)
{
	this->diffuseMap = diffuseMap;
}

void Material::SetNormalMap(std::shared_ptr<Image> normalMap)
{
	this->normalMap = normalMap;
}

void Material::SetSpecularMap(std::shared_ptr<Image> specularMap)
{
	this->specularMap = specularMap;
}

void Material::SetEmissiveMap(std::shared_ptr<Image> emissiveMap)
{
	this->emissiveMap = emissiveMap;
}

void Material::SetAmbient(Color ambient)
{
	this->ambient = ambient;
}

void Material::SetDiffuse(Color diffuse)
{
	this->diffuse = diffuse;
}

void Material::SetSpecular(Color specular)
{
	this->specular = specular;
}

void Material::SetEmissive(Color emissive)
{
	this->emissive = emissive;
}

void Material::SetShininess(float shininess)
{
	this->shininess = shininess;
}

void Material::SetMetalic(float metalic)
{
	this->metalic = metalic;
}

void Material::SetRoughness(float roughness)
{
	this->roughness = roughness;
}

void Material::SetSpecularIntensity(float specularIntensity)
{
	this->specularIntensity = specularIntensity;
}

void Material::SetEmissiveIntensity(float emissiveIntensity)
{
	this->emissiveIntensity = emissiveIntensity;
}

void Material::SetDiffuseMapVerticies(std::vector<Coord>& diffuseMapVerticies)
{
	this->diffuseMapVerticies = diffuseMapVerticies;
	//this->diffuseMapVerticies.swap(diffuseMapVerticies);
}

void Material::SetNormalMapVerticies(std::vector<Coord> normalMapVerticies)
{
	ClearVector<Coord>(this->normalMapVerticies);
	this->normalMapVerticies = normalMapVerticies;
}

void Material::SetSpecularMapVerticies(std::vector<Coord> specularMapVerticies)
{
	ClearVector<Coord>(this->specularMapVerticies);
	this->specularMapVerticies = specularMapVerticies;
}

void Material::SetEmissiveMapVerticies(std::vector<Coord> emissiveMapVerticies)
{
	ClearVector<Coord>(this->emissiveMapVerticies);
	this->emissiveMapVerticies = emissiveMapVerticies;
}

void Material::SetDiffuseMapVerticies(std::pair<Coord, Coord> diffuseMapVerticies)
{
	ClearVector<Coord>(this->diffuseMapVerticies);
	this->diffuseMapVerticies.push_back(diffuseMapVerticies.first);
	this->diffuseMapVerticies.push_back(diffuseMapVerticies.second);
}

void Material::SetNormalMapVerticies(std::pair<Coord, Coord> normalMapVerticies)
{
	ClearVector<Coord>(this->normalMapVerticies);
	this->normalMapVerticies.push_back(normalMapVerticies.first);
	this->normalMapVerticies.push_back(normalMapVerticies.second);
}

void Material::SetSpecularMapVerticies(std::pair<Coord, Coord> specularMapVerticies)
{
	ClearVector<Coord>(this->specularMapVerticies);
	this->specularMapVerticies.push_back(specularMapVerticies.first);
	this->specularMapVerticies.push_back(specularMapVerticies.second);
}

void Material::SetEmissiveMapVerticies(std::pair<Coord, Coord> emissiveMapVerticies)
{
	ClearVector<Coord>(this->emissiveMapVerticies);
	this->emissiveMapVerticies.push_back(emissiveMapVerticies.first);
	this->emissiveMapVerticies.push_back(emissiveMapVerticies.second);
}

Color Material::GetSpecular()
{
	return specular;
}

Color Material::GetEmissive()
{
	return emissive;
}

float Material::GetShininess()
{
	return shininess;
}

float Material::GetMetalic()
{
	return metalic;
}

float Material::GetRoughness()
{
	return roughness;
}

float Material::GetSpecularIntensity()
{
	return specularIntensity;
}

float Material::GetEmissiveIntensity()
{
	return emissiveIntensity;
}


Color Material::GetAmbient()
{
	return ambient;
}

Color Material::GetDiffuse()
{
	return diffuse;
}


std::weak_ptr<Image> Material::GetDiffuseMap()
{
	return diffuseMap;
}

std::weak_ptr<Image> Material::GetNormalMap()
{
	return normalMap;
}

std::weak_ptr<Image> Material::GetSpecularMap()
{
	return specularMap;
}

std::weak_ptr<Image> Material::GetEmissiveMap()
{
	return emissiveMap;
}

std::vector<Coord> Material::GetDiffuseMapVerticies()
{
	return diffuseMapVerticies;
}

std::vector<Coord> Material::GetNormalMapVerticies()
{
	return normalMapVerticies;
}

std::vector<Coord> Material::GetSpecularMapVerticies()
{
	return specularMapVerticies;
}

std::vector<Coord> Material::GetEmissiveMapVerticies()
{
	return emissiveMapVerticies;
}

bool Material::operator==(const Material& other) const
{
	return ambient == other.ambient && diffuse == other.diffuse && specular == other.specular && 
		emissive == other.emissive && shininess == other.shininess && metalic == other.metalic && 
		roughness == other.roughness && specularIntensity == other.specularIntensity && 
		emissiveIntensity == other.emissiveIntensity && shader == other.shader && camera == other.camera &&
		*diffuseMap == *other.diffuseMap && diffuseMapVerticies == other.diffuseMapVerticies && normalMap == other.normalMap && specularMap == other.specularMap &&
		emissiveMap == other.emissiveMap;
}

bool Material::operator!=(const Material& other) const
{
	return !(*this == other);
}

Material& Material::operator=(const Material& other)
{
	if (this != &other) {
		ambient = other.ambient;
		diffuse = other.diffuse;
		specular = other.specular;
		emissive = other.emissive;
		shininess = other.shininess;

		metalic = other.metalic;
		roughness = other.roughness;
		specularIntensity = other.specularIntensity;
		emissiveIntensity = other.emissiveIntensity;

		shader = other.shader;
		camera = other.camera;

		diffuseMap = other.diffuseMap;
		normalMap = other.normalMap;
		specularMap = other.specularMap;
		emissiveMap = other.emissiveMap;
	}
	return *this;
}


const GLuint& Material::GetShader()
{
	return shader;
}

std::weak_ptr<Camera> Material::GetCamera()
{
	return camera;
}


