#include "glpch.h"
#include "light.h"

void point_light::render(int i, shader& shader)
{
	std::string name = "u_PointLights[" + std::to_string(i) + "]";

	shader.set_float(name + ".k0", k0);
	shader.set_float(name + ".k1", k1);
	shader.set_float(name + ".k2", k2);

	shader.set_vec3(name + ".position", position);
	shader.set_vec4(name + ".ambient", ambient);
	shader.set_vec4(name + ".diffuse", diffuse);
	shader.set_vec4(name + ".specular", specular);
}

void dir_light::render(shader& shader)
{
	std::string name = "u_DirLight";

	shader.set_vec3(name + ".direction", direction);
	shader.set_vec4(name + ".ambient", ambient);
	shader.set_vec4(name + ".diffuse", diffuse);
	shader.set_vec4(name + ".specular", specular);
}

void spot_light::render(int i, shader& shader)
{
	std::string name = "u_SpotLights[" + std::to_string(i) + "]";

	shader.set_float(name + ".k0", k0);
	shader.set_float(name + ".k1", k1);
	shader.set_float(name + ".k2", k2);

	shader.set_vec3(name + ".position", position);
	shader.set_vec3(name + ".direction", direction);

	shader.set_float(name + ".cutOff", cutOff);
	shader.set_float(name + ".outerCutOff", outerCutOff);

	shader.set_vec3(name + ".direction", direction);
	shader.set_vec4(name + ".ambient", ambient);
	shader.set_vec4(name + ".diffuse", diffuse);
	shader.set_vec4(name + ".specular", specular);
}
