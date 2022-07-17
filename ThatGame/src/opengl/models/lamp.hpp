#pragma once

#include "cube.hpp"
#include "opengl/light.h"

class lamp : public cube {
public:
	glm::vec3 LightColor;

	point_light pointLight;

	lamp() = default;
	lamp(
		const glm::vec3& lightColor,
		const glm::vec4& ambient,
		const glm::vec4& diffuse,
		const glm::vec4& specular,
		const glm::vec3& pos,
		const glm::vec3& size,
		float k0,
		float k1,
		float k2)	
			:	
		LightColor(lightColor), pointLight({k0, k1, k2, pos, ambient, diffuse, specular}),
		cube(pos, size) {}

	void render(shader& shader, float dt) override
	{
		shader.set_vec3("u_LightColor", LightColor);

		cube::render(shader, dt);
	}
};