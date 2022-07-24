#pragma once

#include "cube.hpp"
#include "opengl/light.h"
#include "model_list.h"

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

	void render(shader& shader, bool set_model_matrix, float dt) override
	{
		shader.set_vec3("u_LightColor", LightColor);

		cube::render(shader, set_model_matrix, dt);
	}
};

class lamp_list : public model_list<lamp>
{
public:
	std::vector<point_light> lights;

	void init()
	{
		model = lamp(
			glm::vec3(1.0f),
			glm::vec4(0.05f, 0.05f, 0.05f, 1.0f),
			glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
			glm::vec4(1.0f),
			glm::vec3(0.0f),
			glm::vec3(0.25f),
			1.0f, 0.07f, 0.032f);

		model.init();
	}

	void render(shader& shader, float dt)
	{
		for (point_light& light : lights)
		{
			model.rb.pos = light.position;

			model.render(shader, true, dt);
		}
	}
};