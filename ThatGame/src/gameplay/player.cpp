#include "glpch.h"
#include "player.h"

#include "io/keyboard.h"
#include "io/mouse.h"

#include "core/application.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


player::player(const glm::vec3& pos)
	: position(pos)
{
	init();
}

void player::update()
{
	update_input();

	
}

void player::shutdown()
{

}

void player::init()
{
	m_camera = std::make_shared<camera>(position);
}

void player::update_input()
{
	if (keyboard::key_pressed(GLFW_KEY_W))
		m_camera->update_position(camera_dir::FORWARD);
	if (keyboard::key_pressed(GLFW_KEY_S))
		m_camera->update_position(camera_dir::BACKWARD);
	if (keyboard::key_pressed(GLFW_KEY_A))
		m_camera->update_position(camera_dir::LEFT);
	if (keyboard::key_pressed(GLFW_KEY_D))
		m_camera->update_position(camera_dir::RIGHT);
	if (keyboard::key_pressed(GLFW_KEY_SPACE))
		m_camera->update_position(camera_dir::UP);
	if (keyboard::key_pressed(GLFW_KEY_LEFT_SHIFT))
		m_camera->update_position(camera_dir::DOWN);

	double delta_x_pos = mouse::get_delta_x();
	double delta_y_pos = mouse::get_delta_y();


	if (delta_x_pos != 0 || delta_y_pos != 0)
		m_camera->update_direction(delta_x_pos * DELTA_TIME * 8.0f, -delta_y_pos * DELTA_TIME * 8.0f);

}
