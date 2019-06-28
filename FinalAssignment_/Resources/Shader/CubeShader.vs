#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBitangent;

out vec3 FragPos;
out vec3 Normal;
out vec3 TexCoords;
out vec3 Tangent;
out vec3 Bitangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform bool isHaveCubeMap;

void main(){
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(vPosition,1.0f);

	FragPos = vec3(modelMatrix * vec4(vPosition, 1.0f));
	Normal = mat3(transpose(inverse(modelMatrix))) * vNormal;

	if( isHaveCubeMap ){
		TexCoords = vPosition;
	}else{
		TexCoords = vec3(vTexCoords,1.0f);
	}

	Tangent = vTangent;
	Bitangent = vBitangent;
}
