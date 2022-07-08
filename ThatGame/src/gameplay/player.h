#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "io/camera.h"


class player
{
public:
	player(const glm::vec3& pos);

	void update();
	void shutdown();

	glm::vec3 position;

	std::shared_ptr<camera> get_camera() const { return m_camera; }

private:
	void init();

	void update_input();

	std::shared_ptr<camera> m_camera;
};