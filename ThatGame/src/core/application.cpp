#include "glpch.h"
#include "application.h"

#include <glm/gtc/matrix_transform.hpp>

#include "asserts.h"
#include "logging.h"

#include "opengl/render_commands.h"
#include "opengl/renderer.h"

#include "io/mouse.h"

#include "physics\physics_world.h"

#include <stack>
#include <vector>

application* application::s_instance = nullptr;

application::application(const std::string& title, u32 width, u32 height)
	: m_title(title.c_str()), m_width(width), m_height(height)
{
	ASSERT_MSG(!s_instance, "Tried to instantiate application multiple times!");
	init();
}

application::~application()
{
	shutdown();
}

void application::run()
{
	while (m_running)
	{
		double current_frame_time = glfwGetTime();
		m_delta_time = current_frame_time - m_last_frame_time;
		m_last_frame_time = current_frame_time;

		if (!m_window->is_running())
		{
			stop();
		}

		if (!m_suspened)
		{

			glfwPollEvents();

			m_shader->bind();
			m_shader->set_vec3("u_ViewPos", game_instc->game_player->get_camera()->get_position());

			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			view = game_instc->game_player->get_camera()->get_view_matrix();
			projection = glm::perspective(glm::radians(APP_INSTC->game_instc->game_player->get_camera()->get_fov()),
				((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), 0.1f, 1000.0f);

			m_shader->set_mat4("u_View", view);
			m_shader->set_mat4("u_Projection", projection);

			std::stack<int> objects_to_remove;
			
			for (u32 i = 0; i < m_spheres.instances.size(); i++)
			{
				if (glm::length(game_instc->game_player->get_camera()->get_position() - m_spheres.instances[i].pos) > 250.0f)
				{
					objects_to_remove.push(i);
					continue;
				}
			}

			for (u32 i = 0; i < objects_to_remove.size(); i++)
			{
				m_spheres.instances.erase(m_spheres.instances.begin() + objects_to_remove.top());
				objects_to_remove.pop();
			}
			if (m_spheres.instances.size())
			{
				m_spheres.render(*m_shader, m_delta_time);
			}

			m_dir_light.direction = glm::vec3(
				glm::rotate(glm::mat4(1.0f), glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::vec4(m_dir_light.direction, 1.0f));

			m_dir_light.render(*m_shader);

			for (u32 i = 0; i < 4; i++)
			{
				m_lamps.lights[i].render(i, *m_shader);
			}

			m_shader->set_int("u_NPointLights", 4);
			if (m_flash_light_on) {
				m_spot_light.position = game_instc->game_player->get_camera()->get_position();;
				m_spot_light.direction = game_instc->game_player->get_camera()->get_front();
				m_spot_light.render(0, *m_shader);
				m_shader->set_int("u_NSpotLights", 1);
			}
			else {
				m_shader->set_int("u_NSpotLights", 0);
			}

			m_lamp_shader->bind();
			m_lamp_shader->set_mat4("u_View", view);
			m_lamp_shader->set_mat4("u_Projection", projection);

			m_lamps.render(*m_lamp_shader, m_delta_time);
	

			glfwSwapBuffers(m_window->get_glfw_instance());
			render_command::clear_buffer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render_command::clear_color(0.2f, 0.3f, 0.8f, 1.0f);

			game_instc->update();

			// testing

			if (mouse::button_went_down(GLFW_MOUSE_BUTTON_RIGHT)) {
				m_flash_light_on = !m_flash_light_on;
			}

			if (mouse::button_went_down(GLFW_MOUSE_BUTTON_LEFT)) {
				throw_sphere();
			}
		}
	}
}

void application::stop()
{
	m_running = false;
}

void application::init()
{
	s_instance = this;
	m_running = true;

	log::init();

	m_window = std::make_shared<window>(m_title, m_width, m_height);


	game_instc = std::make_shared<game>();

	m_shader = new shader("assets/shaders/object.vert", "assets/shaders/object.frag");
	m_lamp_shader = new shader("assets/shaders/object.vert", "assets/shaders/lamp.frag");


	glm::vec4 ambinet = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
	glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	glm::vec4 specular = glm::vec4(1.0f);

	float k0 = 1.0f;
	float k1 = 0.09f;
	float k2 = 0.032f;



	for (u32 i = 0; i < 4; i++)
	{
		m_lamps.lights.push_back({
			k0, k1, k2,
			m_point_light_positions[i],
			ambinet, diffuse,
			specular
			});
	}

	m_spot_light = {
		1.0f, 0.07f, 0.32f,
		game_instc->game_player->get_camera()->get_position(),
		game_instc->game_player->get_camera()->get_front(),
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(20.0f)),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f),
		glm::vec4(1.0f)
	};

	m_spheres.init();

	m_spheres.set_scale(glm::vec3(0.025f));


	m_lamps.init();

}

void application::shutdown()
{
	m_running = false;

	delete m_shader;
	delete m_lamp_shader;
}

void application::throw_sphere()
{
	rigid_body rb(1.0f, game_instc->game_player->get_camera()->get_position());
	
	rb.apply_impulse(game_instc->game_player->get_camera()->get_front(), 1000.0f, m_delta_time);
	rb.apply_acceleration(physics_world::gravity_vector);
	m_spheres.instances.push_back(rb);
}
