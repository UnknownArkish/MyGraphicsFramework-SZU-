#version 330 core

#define MAXIMUM_TEXTURE_NUM 4

// 模型片段着色器下的材质结构体
struct Material{
	vec3 ambient;		// 环境光分量
	vec3 diffuse;		// 漫反射分量
	vec3 specular;		// 镜面反射分量
	// 贴图数组
	sampler2D texture_ambient[MAXIMUM_TEXTURE_NUM];
	sampler2D texture_diffuse[MAXIMUM_TEXTURE_NUM];
	sampler2D texture_specular[MAXIMUM_TEXTURE_NUM];
	float shiness;		// 高光系数
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

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec4 ShadowColor;


uniform vec3 color;

// 光源有关
uniform vec3 viewPos;
uniform DirectionLight directionLights[MAXIMUM_LIGHT_NUM];
uniform int directionLightNum;

uniform PointLight pointLights[MAXIMUM_LIGHT_NUM];
uniform int pointLightNum;

uniform SpotLight spotLights[MAXIMUM_LIGHT_NUM];
uniform int spotLightNum;

// 贴图、材质有关
uniform Material material;
uniform bool isHaveTexture;
uniform int ambientNr;
uniform int diffuseNr;
uniform int specularNr;

// 阴影有关
uniform bool isShadow;					// 是否为阴影

// 计算指定方向光对该面片坐标贡献的光照效果
vec3 CalculateDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
// 计算指定点光源对该面片坐标贡献的光照效果
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
// 计算指定聚光灯对该面片坐标贡献的光照效果
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main(){
	
	if( isShadow ){
		FragColor = vec4(color, 1.0f);
		//FragColor = CalculateShadow(objectPosition, FragPos, color, shadow);
		//FragColor = ShadowColor;
	}else{
		vec3 norm = normalize(Normal);							// 法向量
		vec3 viewDir = normalize(viewPos - FragPos);			// 观察向量

		vec3 result = color;									// 基本颜色
		for( int i = 0 ; i < directionLightNum ; i++ ){
			result += CalculateDirectionLight( directionLights[i], norm, viewDir );
		}
		for( int i = 0 ; i < pointLightNum ; i++ ){
			result += CalculatePointLight( pointLights[i], norm, FragPos, viewDir );
		}
		for( int i = 0 ; i < spotLightNum ; i++ ){
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

	if( isHaveTexture ){
		for( int i = 0 ; i < ambientNr ; i++ ){
			ambient += light.ambient * vec3(texture( material.texture_ambient[i], TexCoords ));
		}
		for( int i = 0 ; i < diffuseNr ; i++ ){
			diffuse += light.diffuse * diff * vec3(texture( material.texture_diffuse[i], TexCoords ));
		}
		for( int i = 0 ; i < specularNr ; i++ ){
			specular += light.specular * spec * vec3(texture( material.texture_specular[i], TexCoords ));
		}
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

	if( isHaveTexture ){
		for( int i = 0 ; i < ambientNr ; i++ ){
			ambient += light.ambient * vec3(texture( material.texture_ambient[i], TexCoords ));
		}
		for( int i = 0 ; i < diffuseNr ; i++ ){
			diffuse += light.diffuse * diff * vec3(texture( material.texture_diffuse[i], TexCoords ));
		}
		for( int i = 0 ; i < specularNr ; i++ ){
			specular += light.specular * spec * vec3(texture( material.texture_specular[i], TexCoords ));
		}
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
	if( isHaveTexture ){
		for( int i = 0 ; i < ambientNr ; i++ ){
			ambient += light.ambient * vec3(texture( material.texture_ambient[i], TexCoords ));
		}
		for( int i = 0 ; i < diffuseNr ; i++ ){
			diffuse += light.diffuse * diff * vec3(texture( material.texture_diffuse[i], TexCoords ));
		}
		for( int i = 0 ; i < specularNr ; i++ ){
			specular += light.specular * spec * vec3(texture( material.texture_specular[i], TexCoords ));
		}
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