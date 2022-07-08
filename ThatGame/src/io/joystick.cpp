#include "glpch.h"
#include "joystick.h"

joystick::joystick(int i)
{
	id = get_id(i);

	update();
}

void joystick::update()
{
	present = glfwJoystickPresent(id);

	if (present) {
		name = glfwGetJoystickName(id);
		axes = glfwGetJoystickAxes(id, &axesCount);
		buttons = glfwGetJoystickButtons(id, &buttonCount);
	}
}

f32 joystick::axes_state(i32 axis)
{
	if (present) {
		return axes[axis];
	}
	return 0.0f;
}

u8 joystick::button_state(KeyCode button)
{
	if (present) {
		return buttons[button];
	}
	return GLFW_RELEASE;
}

i32 joystick::get_axes_count()
{
	return axesCount;
}

i32 joystick::get_button_count()
{
	return buttonCount;
}

bool joystick::is_present()
{
	return present;
}

const char* joystick::get_name()
{
	return name;
}

i32 joystick::get_id(int i)
{
	return GLFW_JOYSTICK_1 + i;
}
