#pragma once

#include "core/defines.h"

#include <GLFW/glfw3.h>

class window 
{
public:
	window() = default;
	window(const char* title, u32 width, u32 height);
	~window();

	void update();

	inline GLFWwindow* get_glfw_instance() const { return m_GLFW_instance; }

	inline bool is_running() const { return !glfwWindowShouldClose(m_GLFW_instance); }

	inline void set_running(bool running) { glfwSetWindowShouldClose(m_GLFW_instance, running); }

	inline static u32 get_width() { return s_width; }

	inline static u32 get_height() { return s_height; }

	inline const char* get_title() const { return m_title; }

	inline void set_title(const char* title) { glfwSetWindowTitle(m_GLFW_instance, title); }

	void shutdown();


private:
	void init();

	static void resize_callback(GLFWwindow* window, int xpos, int ypos );

	GLFWwindow* m_GLFW_instance;

	static u32 s_width, s_height;
	const char* m_title;
};