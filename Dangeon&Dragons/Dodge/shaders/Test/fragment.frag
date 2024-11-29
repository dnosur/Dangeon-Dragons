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
    // Получение цвета текстуры и умножение на заданный цвет
    color = texture(material.diffuseMap, diffuseTexCoord) * material.diffuse;
}
