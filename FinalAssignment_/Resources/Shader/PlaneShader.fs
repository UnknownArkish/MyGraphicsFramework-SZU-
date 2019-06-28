#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shiness;
	
	sampler2D texture;
};

// 方向光结构体
struct DirectionLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
// 点光源结构体
struct PointLight{
	vec3 position;

	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
// 聚光灯点光源
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

// 摄像机位置
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
uniform bool isAnimator;		// 是否为动画机


out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// 计算指定方向光对该面片坐标贡献的光照效果
vec3 CalculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
// 计算指定点光源对该面片坐标贡献的光照效果
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
// 计算指定聚光灯对该面片坐标贡献的光照效果
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	if( isAnimator ){
		FragColor = texture(material.texture, TexCoords);
	}else{
		vec3 norm = normalize(Normal);							// 法向量
		vec3 viewDir = normalize(viewPos - FragPos);			// 观察向量

		vec3 result = color;									// 基本颜色
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
	// 得到光线方向
	vec3 lightDir = normalize(-light.direction);
	// 漫反射分量
	float diff = max(dot(normal,lightDir),0.0f);
	// 镜面反射分量
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

	// 组合Phone光照模型
	return (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	// 计算点光源到面片顶点的光线方向
	vec3 lightDir = normalize(light.position - fragPos);
	// 漫反射分量
	float diff = max( dot( normal, lightDir ), 0.0f );

	// 镜面反射分量
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

	// 衰减因子系数
	float distance = length( light.position - fragPos );
	float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance) );
	// 乘以因为距离而造成的光照衰减系数
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);
}
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize( light.position - fragPos );

	// 漫反射分量
	float diff = max( dot(normal, lightDir), 0.0f );
	// 镜面反射分量
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

	// 衰减因子系数
	float distance = length( light.position - fragPos );
	float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance) );

	// 模糊系数
	float theta = dot( lightDir, normalize(-light.direction) );						// 计算光朝向和光线方向的夹角
	float epsilon = light.cutOff - light.outerCutOff;								// 计算外圈和内圈之间的最大范围
	float intensity = clamp( (theta - light.outerCutOff) / epsilon, 0.0f, 1.0f );	// 计算夹角占最大范围的比例

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return ( ambient + diffuse * specular );
}