#include "glpch.h"
#include "window.h"

#include <glad/glad.h>

#include "io/keyboard.h"
#include "io/mouse.h"

#include "core/application.h"

#include "core/logging.h"


#include "core/asserts.h"


u32 window::s_width = 0;
u32 window::s_height = 0;

window::window(const char* title, u32 width, u32 height)
	: m_GLFW_instance(nullptr), m_title(title)
{
	s_width = width;
	s_height = height;
	init();
}

window::~window()
{
	shutdown();
}

void window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_GLFW_instance);
}

void window::shutdown()
{
	glfwDestroyWindow(m_GLFW_instance);
	glfwTerminate();
}

void window::init()
{

	ASSERT_MSG(glfwInit(), "Failed to initialize GLFW!");

	m_GLFW_instance = glfwCreateWindow(s_width, s_height, m_title, nullptr, nullptr);

	ASSERT_MSG(m_GLFW_instance, "Failed to create GLFW window!");

	glfwMakeContextCurrent(m_GLFW_instance);

	ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to intitialize Glad!");

	
	glfwSetKeyCallback(m_GLFW_instance, keyboard::glfw_key_callback);
	glfwSetMouseButtonCallback(m_GLFW_instance, mouse::glfw_button_callback);
	glfwSetCursorPosCallback(m_GLFW_instance, mouse::glfw_cursor_pos_callback);
	glfwSetScrollCallback(m_GLFW_instance, mouse::glfw_scroll_callback);
	glfwSetFramebufferSizeCallback(m_GLFW_instance, resize_callback);

	glfwSwapInterval(1);

	glfwSetInputMode(m_GLFW_instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void window::resize_callback(GLFWwindow* window, int xpos, int ypos)
{
	glViewport(0, 0, xpos, ypos);
	
	application::get_instance()->set_width(xpos);
	application::get_instance()->set_height(ypos);
}
