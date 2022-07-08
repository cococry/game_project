#include "glpch.h"
#include "mouse.h"

bool mouse::s_active_buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool mouse::s_changed_buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
double mouse::s_xpos = 0;
double mouse::s_ypos = 0;
double mouse::s_scroll_delta_x = 0;
double mouse::s_scroll_delta_y = 0;
double mouse::s_d_xpos = 0;
double mouse::s_d_ypos = 0;
double mouse::s_last_xpos = 0;
double mouse::s_last_ypos = 0;
bool mouse::s_first_mouse = true;


void mouse::glfw_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!s_active_buttons[button])
		{
			s_active_buttons[button] = true;
		}
	}
	else
	{
		s_active_buttons[button] = false;
	}

	s_changed_buttons[button] = (action != GLFW_REPEAT);
}

void mouse::glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffest)
{
	s_scroll_delta_x = xoffset;
	s_scroll_delta_y = yoffest;
}

void mouse::glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	s_xpos = xpos;
	s_ypos = ypos;

	if (s_first_mouse)
	{
		s_last_xpos = s_xpos;
		s_last_ypos = s_ypos;
		s_first_mouse = false;
	}

	s_d_xpos = s_xpos - s_last_xpos;
	s_d_ypos = s_ypos - s_last_ypos;
	s_last_xpos = s_xpos;
	s_last_ypos = s_ypos;
}

bool mouse::button_pressed(int button)
{
	return s_active_buttons[button];
}

bool mouse::button_released(int button)
{
	return !s_active_buttons[button] && button_changed(button);
}

bool mouse::button_changed(int button)
{
	bool ret = s_changed_buttons[button];
	s_changed_buttons[button] = false;
	return ret;
}

bool mouse::button_went_down(int button)
{
	return s_active_buttons[button] && button_changed(button);
}
