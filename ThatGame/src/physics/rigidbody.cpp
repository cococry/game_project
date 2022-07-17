#include "glpch.h"
#include "rigidbody.h"

rigid_body::rigid_body(float mass, const glm::vec3& pos, const glm::vec3& velocity, const glm::vec3& acceleration)
	: mass(mass), pos(pos), velocity(velocity), acceleration(acceleration)
{
}

void rigid_body::update(float dt)
{
	pos += velocity * dt + 0.5f * acceleration * (dt * dt);
	velocity += acceleration * dt;
}
