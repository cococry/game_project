#include "glpch.h"
#include "keyboard.h"

bool keyboard::s_active_keys[GLFW_KEY_LAST];
bool keyboard::s_changed_keys[GLFW_KEY_LAST];

void keyboard::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!s_active_keys[key])
		{
			s_active_keys[key] = true;
		}
	}
	else
	{
		s_active_keys[key] = false;
	}

	s_changed_keys[key] = (action != GLFW_REPEAT);
}

bool keyboard::key_pressed(int key)
{
	return s_active_keys[key];
}

bool keyboard::key_relased(int key)
{
	return key_changed(key) && !s_active_keys[key];
}

bool keyboard::key_changed(int key)
{
	bool ret = s_changed_keys[key];
	s_changed_keys[key] = false;
	return ret;
}

bool keyboard::key_went_down(int key)
{
	return key_changed(key) && s_active_keys[key];
}
