#version 330 core

layout (location = 0) in vec3 vPos;
out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(){
	TexCoords = vPos;
	// 将观察矩阵降维成mat3后包装成mat4，以去除位移信息
	vec4 pos = projMatrix * mat4(mat3(viewMatrix)) * vec4(vPos, 1.0f);
	gl_Position = pos.xyww;
}