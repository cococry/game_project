#pragma once

#include <glad/glad.h>

#include "core/defines.h"
#include "vertex_array.h"

class render_command
{
public:
	inline static void draw_indexed(u32 count) { glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr); }

	inline static void draw_indexed(const std::shared_ptr<vertex_array>& va) 
	{ 
		glDrawElements(GL_TRIANGLES, va->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
	}

	inline static void resize_viewport(u32 width, u32 height) { glViewport(0, 0, width, height); }

	inline static void clear_buffer(GLbitfield flags = GL_COLOR_BUFFER_BIT) { glClear(flags); }

	inline static void clear_color(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
private:
};