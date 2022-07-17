#pragma once

#include <string>
#include <memory>

#include "defines.h"
#include "core/window.h"

#include "opengl/shader.h"

#include "gameplay/game.h"

#include "opengl/mesh.h"
#include "opengl/light.h"
#include "opengl/models/lamp.hpp"
#include "opengl/models/sphere.hpp"

class application {
public:
	application(const std::string& title, u32 width, u32 height);
	~application();

	void run();
	void stop();

	inline static application* get_instance() { return s_instance; }

	inline u32 get_width() const { return m_width; }
	inline u32 get_height() const { return m_height; }

	inline void set_width(u32 width) { m_width = width; }
	inline void set_height(u32 height) { m_height = height; }

	inline std::shared_ptr<window> get_window() const { return m_window; }

	inline double get_delta_time() const { return m_delta_time; }

	std::shared_ptr<game> game_instc;
private:

	void init();
	void shutdown();

	u32 m_width, m_height;
	const char* m_title;

	bool m_running = false;
	bool m_suspened = false;

	static application* s_instance;

	std::shared_ptr<window> m_window;

	std::shared_ptr<mesh> m_mesh;

	double m_delta_time = 0.0f;
	double m_last_frame_time = 0.0f;

	dir_light m_dir_light = {
		glm::vec3(-0.2f, -1.0f, -0.3f),
		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4(0.4f, 0.4f, 0.4f, 1.0f),
		glm::vec4(0.75f, 0.75f, 0.75f, 1.0f)
	};

	glm::vec3 m_point_light_positions[4] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
	};

	lamp m_lamps[4];

	spot_light m_spot_light;

	std::shared_ptr<model> m_model;

	sphere m_sphere;


	shader* m_shader;

	shader* m_lamp_shader;

	// testing

	bool m_flash_light_on = false;
};

#define DELTA_TIME application::get_instance()->get_delta_time()
#define WINDOW_WIDTH application::get_instance()->get_width()
#define WINDOW_HEIGHT application::get_instance()->get_height()
#define APP_INSTC application::get_instance()