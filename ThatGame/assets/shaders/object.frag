#version 460 core

#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 5

struct Material {
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform sampler2D diffuse0;
uniform sampler2D specular0;

struct PointLight {
	vec3 position;

	float k0, k1, k2;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct DirLight {
	vec3 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	float k0, k1, k2;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};
out vec4 o_Color;

in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform Material u_Material;


uniform int u_NPointLights;
uniform int u_NSpotLights;
uniform int u_NoTex;

uniform DirLight u_DirLight;
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];

uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;

vec4 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);
vec4 calcDirLight(vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);
vec4 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);

void main() {
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec4 diffMap;
	vec4 specMap;

	if(u_NoTex == 1) {
		diffMap = u_Material.diffuse;
		specMap = u_Material.specular;
	}
	else {
		diffMap = texture(diffuse0, v_TexCoord);
		specMap = texture(specular0, v_TexCoord);
	}

	vec4 result;

	result = calcDirLight(norm, viewDir, diffMap, specMap);

	for(int i = 0; i < u_NPointLights; i++) {
		result += calcPointLight(i, norm, viewDir, diffMap, specMap);
	}

	for(int i = 0; i < u_NSpotLights; i++) {
		result += calcSpotLight(i, norm, viewDir, diffMap, specMap);
	}

	o_Color = result;
}

vec4 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap) 
{
	vec4 ambient = u_PointLights[idx].ambient * diffMap;

	vec3 lightDir = normalize(u_PointLights[idx].position - v_FragPos);
	float diffuseValue = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = u_PointLights[idx].diffuse * (diffuseValue * diffMap);

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess * 64);
	vec4 specular = u_PointLights[idx].specular * (specularValue * specMap);

	float dist = length(u_PointLights[idx].position - v_FragPos);
	float attenuation = 1.0 / (u_PointLights[idx].k0 + u_PointLights[idx].k1 * dist + u_PointLights[idx].k2 * (dist * dist));

	return vec4(ambient + diffuse + specular) * attenuation;
}

vec4 calcDirLight(vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap) {
	vec4 ambient = u_DirLight.ambient * diffMap;
	vec3 lightDir = normalize(-u_DirLight.direction);

	float diffuseValue = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = u_DirLight.diffuse * (diffuseValue * diffMap);

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess * 64);
	vec4 specular = u_DirLight.specular * (specularValue * specMap);

	return vec4(ambient + diffuse + specular);
}

vec4 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap) {
	vec3 lightDir = normalize(u_SpotLights[idx].position - v_FragPos);
	float fov = dot(lightDir, normalize(-u_SpotLights[idx].direction));

	vec4 ambient = u_SpotLights[idx].ambient * diffMap;

	if(fov > u_SpotLights[idx].outerCutOff) {
		float diffuseValue = max(dot(norm, lightDir), 0.0);
		vec4 diffuse = u_SpotLights[idx].diffuse * (diffuseValue * diffMap);

		vec3 reflectDir = reflect(-lightDir, norm);
		float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess * 64);
		vec4 specular = u_SpotLights[idx].specular * (specularValue * specMap);

		float intensity = (fov - u_SpotLights[idx].outerCutOff) / (u_SpotLights[idx].cutOff  - u_SpotLights[idx].outerCutOff);
		intensity = clamp(intensity, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;

		float dist = length(u_SpotLights[idx].position - v_FragPos);
		float attenuation = 1.0 / (u_SpotLights[idx].k0 + u_SpotLights[idx].k1 * dist + u_SpotLights[idx].k2 * (dist * dist));

	return vec4(ambient + diffuse + specular) * attenuation;
	}
	else {
		return ambient;
	}
}