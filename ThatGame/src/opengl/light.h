#pragma once

#include "core/defines.h"
#include <glm/glm.hpp>

#include "shader.h"

struct point_light 
{
	float k0, k1, k2;

	glm::vec3 position;

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	void render(int i, shader& shader);
};

struct dir_light
{
	glm::vec3 direction;

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	void render(shader& shader);
};

struct spot_light
{
	float k0, k1, k2;

	glm::vec3 position;
	glm::vec3 direction;

	f32 cutOff;
	f32 outerCutOff;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	void render(int i, shader& shader);
};