#version 330 core
layout (location = 0) in vec3 position;

layout(location = 1) in vec2 dTexCoord;
layout(location = 2) in vec2 nTexCoord;
layout(location = 3) in vec2 sTexCoord;
layout(location = 4) in vec2 eTexCoord;

struct Camera {
	mat4 projection;
	mat4 view;
};

uniform Camera camera;

uniform bool useCamera;

out vec2 diffuseTexCoord;
out vec2 normalTexCoord;
out vec2 specularTexCoord;
out vec2 emissiveTexCoord;

void main()
{
	vec4 pos = vec4(position, 1.0);
	gl_Position = camera.projection * camera.view * pos;

	diffuseTexCoord = dTexCoord;
	normalTexCoord = nTexCoord;
	specularTexCoord = sTexCoord;
	emissiveTexCoord = eTexCoord;
} 