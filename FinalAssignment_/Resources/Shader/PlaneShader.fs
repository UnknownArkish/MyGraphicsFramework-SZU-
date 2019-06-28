#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shiness;
	
	sampler2D texture;
};

// �����ṹ��
struct DirectionLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
// ���Դ�ṹ��
struct PointLight{
	vec3 position;

	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
// �۹�Ƶ��Դ
struct SpotLight{
	vec3 position;
	vec3 direction;
	
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define MAXIMUM_LIGHT_NUM 16
#define MixLength 0.2

// �����λ��
uniform vec3 viewPos;

uniform DirectionLight directionLights[MAXIMUM_LIGHT_NUM];
uniform int directionLightNum;

uniform PointLight pointLights[MAXIMUM_LIGHT_NUM];
uniform int pointLightNum;

uniform SpotLight spotLights[MAXIMUM_LIGHT_NUM];
uniform int spotLightNum;

uniform vec3 color;
uniform Material material;
uniform bool useTexture;
uniform bool isAnimator;		// �Ƿ�Ϊ������


out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// ����ָ�������Ը���Ƭ���깱�׵Ĺ���Ч��
vec3 CalculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
// ����ָ�����Դ�Ը���Ƭ���깱�׵Ĺ���Ч��
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
// ����ָ���۹�ƶԸ���Ƭ���깱�׵Ĺ���Ч��
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	if( isAnimator ){
		FragColor = texture(material.texture, TexCoords);
	}else{
		vec3 norm = normalize(Normal);							// ������
		vec3 viewDir = normalize(viewPos - FragPos);			// �۲�����

		vec3 result = color;									// ������ɫ
		for( int i = 0 ; i < directionLightNum && i < MAXIMUM_LIGHT_NUM ; i++ ){
			result += CalculateDirectionLight( directionLights[i], norm, viewDir );
		}
		for( int i = 0 ; i < pointLightNum  && i < MAXIMUM_LIGHT_NUM; i++ ){
			result += CalculatePointLight( pointLights[i], norm, FragPos, viewDir );
		}
		for( int i = 0 ; i < spotLightNum  && i < MAXIMUM_LIGHT_NUM; i++ ){
			result += CalculateSpotLight( spotLights[i], norm, FragPos, viewDir );
		}
		FragColor = vec4(result, 1.0f);
	}
}

vec3 CalculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir){
	// �õ����߷���
	vec3 lightDir = normalize(-light.direction);
	// ���������
	float diff = max(dot(normal,lightDir),0.0f);
	// ���淴�����
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow( max(dot(viewDir,reflectDir),0.0f), material.shiness );

	vec3 ambient = vec3(0.0f, 0.0f, 0.0f);
	vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);

	if( useTexture ){
			ambient = light.ambient * mix(vec3(texture( material.texture, TexCoords )), material.ambient, MixLength);
			diffuse = light.diffuse * diff * mix(vec3(texture( material.texture, TexCoords )), material.diffuse, MixLength);
			specular = light.specular * spec * mix(vec3(texture( material.texture, TexCoords )), material.specular, MixLength);
	}else{
		ambient = light.ambient *  material.ambient;
		diffuse = light.diffuse * diff * material.diffuse;
		specular = light.specular * spec * material.specular;
	}

	// ���Phone����ģ��
	return (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	// ������Դ����Ƭ����Ĺ��߷���
	vec3 lightDir = normalize(light.position - fragPos);
	// ���������
	float diff = max( dot( normal, lightDir ), 0.0f );

	// ���淴�����
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow( max(dot( viewDir, reflectDir ),0.0f), material.shiness );

	vec3 ambient = vec3(0.0f, 0.0f, 0.0f);
	vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);

	if( useTexture ){
			ambient = light.ambient * mix(vec3(texture( material.texture, TexCoords )), material.ambient, MixLength);
			diffuse = light.diffuse * diff * mix(vec3(texture( material.texture, TexCoords )), material.diffuse, MixLength);
			specular = light.specular * spec * mix(vec3(texture( material.texture, TexCoords )), material.specular, MixLength);
	}else{
		ambient = light.ambient *  material.ambient;
		diffuse = light.diffuse * diff * material.diffuse;
		specular = light.specular * spec * material.specular;
	}

	// ˥������ϵ��
	float distance = length( light.position - fragPos );
	float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance) );
	// ������Ϊ�������ɵĹ���˥��ϵ��
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);
}
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize( light.position - fragPos );

	// ���������
	float diff = max( dot(normal, lightDir), 0.0f );
	// ���淴�����
	vec3 reflectDir = reflect( -lightDir, normal );
	float spec = pow( max( dot( viewDir, reflectDir ),0.0f ), material.shiness );
	
	vec3 ambient = vec3(0.0f, 0.0f, 0.0f);
	vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);

	if( useTexture ){
			ambient = light.ambient * mix(vec3(texture( material.texture, TexCoords )), material.ambient, MixLength);
			diffuse = light.diffuse * diff * mix(vec3(texture( material.texture, TexCoords )), material.diffuse, MixLength);
			specular = light.specular * spec * mix(vec3(texture( material.texture, TexCoords )), material.specular, MixLength);
	}else{
		ambient = light.ambient *  material.ambient;
		diffuse = light.diffuse * diff * material.diffuse;
		specular = light.specular * spec * material.specular;
	}

	// ˥������ϵ��
	float distance = length( light.position - fragPos );
	float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance) );

	// ģ��ϵ��
	float theta = dot( lightDir, normalize(-light.direction) );						// ����⳯��͹��߷���ļн�
	float epsilon = light.cutOff - light.outerCutOff;								// ������Ȧ����Ȧ֮������Χ
	float intensity = clamp( (theta - light.outerCutOff) / epsilon, 0.0f, 1.0f );	// ����н�ռ���Χ�ı���

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return ( ambient + diffuse * specular );
}