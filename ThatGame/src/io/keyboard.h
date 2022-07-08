#pragma once

#include <GLFW/glfw3.h>

class keyboard
{
public:
	static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool key_pressed(int key);

	static bool key_relased(int key);

	static bool key_changed(int key);

	static bool key_went_down(int key);

private:
	static bool s_active_keys[];
	static bool s_changed_keys[];
};