#version 330 core
out vec4 color;

in vec2 diffuseTexCoord;
in vec2 normalTexCoord;
in vec2 specularTexCoord;
in vec2 emissiveTexCoord;

uniform sampler2D diffuseTexture;
uniform vec4 diffuseColor;

uniform sampler2D normalTexture;
uniform vec4 normalColor;

uniform sampler2D specularTexture;
uniform vec4 specularColor;

uniform sampler2D emissiveTexture;
uniform vec4 emissiveColor;

void main()
{
    // Получение цвета текстуры и умножение на заданный цвет
    color = texture(diffuseTexture, diffuseTexCoord) * diffuseColor;
}
