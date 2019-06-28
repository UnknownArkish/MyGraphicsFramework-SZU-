#version 330 core

layout (location = 0) in vec3 vPos;
out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(){
	TexCoords = vPos;
	// ���۲����ά��mat3���װ��mat4����ȥ��λ����Ϣ
	vec4 pos = projMatrix * mat4(mat3(viewMatrix)) * vec4(vPos, 1.0f);
	gl_Position = pos.xyww;
}