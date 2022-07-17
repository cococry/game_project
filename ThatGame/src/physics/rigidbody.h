#pragma once

#include <glm/glm.hpp>

class rigid_body
{
public:
	float mass;
	
	glm::vec3 pos, velocity, acceleration;

	rigid_body(float mass = 1.0f, const glm::vec3& pos = glm::vec3(0.0f), 
		const glm::vec3& velocity = glm::vec3(0.0f), const glm::vec3& acceleration = glm::vec3(0.0f));

	void update(float dt);
};