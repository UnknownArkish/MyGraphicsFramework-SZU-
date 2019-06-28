#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);

	FragPos = vec3(modelMatrix * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
	TexCoords = aTexCoord;
}