#version 330 core
out vec4 color;

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;

    float shininess;
    float metalic;
    float roughness;
    float specularIntensity;
    float emissiveIntensity;

    sampler2D diffuseMap;
    sampler2D normalMap;
    sampler2D specularMap;
    sampler2D emissiveMap;
};

uniform Material material;

in vec2 diffuseTexCoord;
in vec2 normalTexCoord;
in vec2 specularTexCoord;
in vec2 emissiveTexCoord;

void main()
{
    vec4 diffuseColor;

    // Проверяем, есть ли текстура
    if (textureSize(material.diffuseMap, 0).x > 0) {
        // Если текстура существует, используем её
        diffuseColor = texture(material.diffuseMap, diffuseTexCoord) * material.diffuse;
    }
    else {
        // Если текстуры нет, используем только цвет материала
        diffuseColor = material.diffuse;
    }

    // Устанавливаем итоговый цвет
    color = diffuseColor;
}
