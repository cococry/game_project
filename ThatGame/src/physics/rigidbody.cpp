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

void rigid_body::apply_force(const glm::vec3& force)
{
	acceleration += force / mass;
}

void rigid_body::apply_force(const glm::vec3& dir, float mag)
{
	apply_force(dir * mag);
}

void rigid_body::apply_impulse(const glm::vec3& force, float dt)
{
	velocity += force / mass * dt;
}

void rigid_body::apply_impulse(const glm::vec3& dir, float mag, float dt)
{
	apply_impulse(dir * mag, dt);
}

void rigid_body::apply_acceleration(const glm::vec3& force)
{
	acceleration += force;
}

void rigid_body::apply_acceleration(const glm::vec3& dir, float mag)
{
	apply_acceleration(dir * mag);
}

void rigid_body::transfer_energy(float joules)
{
	if (joules == 0) return;

	float delta_v = sqrt(2 * abs(joules) / mass);

	velocity += joules > 0 ? delta_v : -delta_v;
}
