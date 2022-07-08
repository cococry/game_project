#pragma once

#include <glm/glm.hpp>

#include "core/defines.h"

enum class camera_dir
{
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class camera
{
public:
	camera(const glm::vec3& position);

	void update_direction(double dx, double dy);

	void update_position(camera_dir dir);

	glm::mat4 get_view_matrix() const;

	inline glm::vec3 get_position() const { return m_pos; }

	inline float get_speed() const { return m_speed; }

	inline float get_fov() const { return m_fov; }

	inline glm::vec3 get_front() const { return m_camera_front; }
private:

	void update_camera_vectors();

	glm::vec3 m_pos;
	glm::vec3 m_camera_front;
	glm::vec3 m_camera_up;
	glm::vec3 m_camera_right;

	glm::vec3 m_world_up;
	
	float m_speed, m_fov;

	float m_yaw, m_pitch;
};