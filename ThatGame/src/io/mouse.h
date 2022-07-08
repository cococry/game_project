#pragma once

#include <GLFW/glfw3.h>

class mouse
{
public:
	static void glfw_button_callback(GLFWwindow* window, int button, int action, int mods);

	static void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffest);

	static void glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

	static bool button_pressed(int button);

	static bool button_released(int button);

	static bool button_changed(int button);

	static bool button_went_down(int button);

	inline static double get_x_pos() { return s_xpos; }

	inline static double get_y_pos() { return s_ypos; }

	inline static double get_scroll_delta_x() { return s_scroll_delta_x; }

	inline static double get_scroll_delta_y() { return s_scroll_delta_y; }

	inline static double get_delta_x() { double ret = s_d_xpos; s_d_xpos = 0.0f; return ret; }

	inline static double get_delta_y() { double ret = s_d_ypos; s_d_ypos = 0.0f; return ret; }
private:
	static bool s_active_buttons[];
	static bool s_changed_buttons[];
	
	static double s_ypos, s_xpos;
	static double s_scroll_delta_x, s_scroll_delta_y;
	static double s_last_xpos, s_last_ypos;
	static double s_d_xpos, s_d_ypos;

	static bool s_first_mouse;
};