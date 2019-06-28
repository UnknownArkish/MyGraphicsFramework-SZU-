
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#pragma once

#include<Angel.h>

struct Material {
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shiness;

	Material() {}
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shiness) :Ambient(ambient), Diffuse(diffuse), Specular(specular), Shiness(shiness) {}
	Material(float ambientX, float ambientY, float ambientZ,
		float diffuseX, float diffuseY, float diffuseZ,
		float specularX, float specularY, float specularZ,
		float shiness) {
		Ambient = vec3(ambientX, ambientY, ambientZ);
		Diffuse = vec3(diffuseX, diffuseY, diffuseZ);
		Specular = vec3(specularX, specularY, specularZ);
		Shiness = shiness;
	}
};

namespace MaterialPreSet {
	// 祖母绿
	const Material Emerald = Material(vec3(0.0215f, 0.1745f, 0.0215f), vec3(0.0757f, 0.6142f, 0.0757f), vec3(0.6330f, 0.7278f, 0.6330f), 0.6000f);
	// 翡翠绿
	const Material Jade = Material(vec3(0.1350f, 0.2225f, 0.1575f), vec3(0.5400f, 0.8900f, 0.6300f), vec3(0.3162f, 0.3162f, 0.3162f), 0.1000f);
	// 黑曜石
	const Material Obsidian = Material(vec3(0.0538f, 0.0500f, 0.0662f), vec3(0.1828f, 0.1700f, 0.2253f), vec3(0.3327f, 0.3286f, 0.3464f), 0.3000f);
	// 珍珠
	const Material Pearl = Material(vec3(0.2500f, 0.2072f, 0.2072f), vec3(1.0000f, 0.8290f, 0.8290f), vec3(0.2966f, 0.2966f, 0.2966f), 0.0880f);
	// 红宝石
	const Material Ruby = Material(vec3(0.1745f, 0.0117f, 0.0117f), vec3(0.6142f, 0.0414f, 0.0414f), vec3(0.7278f, 0.6270f, 0.6270f), 0.6000f);
	// 绿松石
	const Material Turquoise = Material(vec3(0.1000f, 0.1873f, 0.1745f), vec3(0.3960f, 0.7415f, 0.6910f), vec3(0.2973f, 0.3083f, 0.3067f), 0.1000f);
	// 黄铜
	const Material Brass = Material(vec3(0.3294f, 0.2235f, 0.0275f), vec3(0.7804f, 0.5686f, 0.1137f), vec3(0.9922f, 0.9412f, 0.8078f), 0.2179f);
	// 青铜
	const Material Bronze = Material(vec3(0.2125f, 0.1275f, 0.0540f), vec3(0.7140f, 0.4284f, 0.1814f), vec3(0.3935f, 0.2719f, 0.1667f), 0.2000f);
	// 铬
	const Material Chrome = Material(vec3(0.2500f, 0.2500f, 0.2500f), vec3(0.4000f, 0.4000f, 0.4000f), vec3(0.7746f, 0.7746f, 0.7746f), 0.6000f);
	// 铜制品
	const Material Copper = Material(vec3(0.1912f, 0.0735f, 0.0225f), vec3(0.7038f, 0.2705f, 0.0828f), vec3(0.2568f, 0.1376f, 0.0860f), 0.1000f);
	// 金制品
	const Material Gold = Material(vec3(0.2473f, 0.1995f, 0.0745f), vec3(0.7516f, 0.6065f, 0.2265f), vec3(0.6283f, 0.5558f, 0.3661f), 0.4000f);
	// 银制品
	const Material Silver = Material(vec3(0.1922f, 0.1922f, 0.1922f), vec3(0.5075f, 0.5075f, 0.5075f), vec3(0.5083f, 0.5083f, 0.5083f), 0.4000f);
	// 黑色的塑料
	const Material Black_plastic = Material(vec3(0.0000f, 0.0000f, 0.0000f), vec3(0.0100f, 0.0100f, 0.0100f), vec3(0.5000f, 0.5000f, 0.5000f), 0.2500f);
	// 蓝色的塑料
	const Material Cyan_plastic = Material(vec3(0.0000f, 0.1000f, 0.0600f), vec3(0.0000f, 0.5098f, 0.5098f), vec3(0.5020f, 0.5020f, 0.5020f), 0.2500f);
	// 绿色的塑料
	const Material Green_plastic = Material(vec3(0.0000f, 0.0000f, 0.0000f), vec3(0.1000f, 0.3500f, 0.1000f), vec3(0.4500f, 0.5500f, 0.4500f), 0.2500f);
	// 红色的塑料
	const Material Red_plastic = Material(vec3(0.0000f, 0.0000f, 0.0000f), vec3(0.5000f, 0.0000f, 0.0000f), vec3(0.7000f, 0.6000f, 0.6000f), 0.2500f);
	// 白色的塑料
	const Material White_plastic = Material(vec3(0.0000f, 0.0000f, 0.0000f), vec3(0.5500f, 0.5500f, 0.5500f), vec3(0.7000f, 0.7000f, 0.7000f), 0.2500f);
	// 黄色的塑料
	const Material Yellow_plastic = Material(vec3(0.0000f, 0.0000f, 0.0000f), vec3(0.5000f, 0.5000f, 0.0000f), vec3(0.6000f, 0.6000f, 0.5000f), 0.2500f);
	// 黑色的橡胶
	const Material Black_rubber = Material(vec3(0.0200f, 0.0200f, 0.0200f), vec3(0.0100f, 0.0100f, 0.0100f), vec3(0.4000f, 0.4000f, 0.4000f), 0.0781f);
	// 青绿色的橡胶
	const Material Cyan_rubber = Material(vec3(0.0000f, 0.0500f, 0.0500f), vec3(0.4000f, 0.5000f, 0.5000f), vec3(0.0400f, 0.7000f, 0.7000f), 0.0781f);
	// 绿色的橡胶
	const Material Green_rubber = Material(vec3(0.0000f, 0.0500f, 0.0000f), vec3(0.4000f, 0.5000f, 0.4000f), vec3(0.0400f, 0.7000f, 0.0400f), 0.0781f);
	// 红色的橡胶
	const Material Red_rubber = Material(vec3(0.0500f, 0.0000f, 0.0000f), vec3(0.5000f, 0.4000f, 0.4000f), vec3(0.7000f, 0.0400f, 0.0400f), 0.0781f);
	// 白色的橡胶
	const Material White_rubber = Material(vec3(0.0500f, 0.0500f, 0.0500f), vec3(0.5000f, 0.5000f, 0.5000f), vec3(0.7000f, 0.7000f, 0.7000f), 0.0781f);
	// 黄色的橡胶
	const Material Yellow_rubber = Material(vec3(0.0500f, 0.0500f, 0.0000f), vec3(0.5000f, 0.5000f, 0.4000f), vec3(0.7000f, 0.7000f, 0.0400f), 0.0781f);
}

#endif // !_MATERIAL_H_

