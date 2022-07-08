#include "glpch.h"
#include "gl_buffer.h"

#include <glad/glad.h>

vertex_buffer::vertex_buffer(const void* vertices, u32 size)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

vertex_buffer::vertex_buffer(u32 size)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}


vertex_buffer::~vertex_buffer()
{
	delete_id();
}

void vertex_buffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void vertex_buffer::unbind()
{
	glBindBuffer(0, m_id);
}

void vertex_buffer::delete_id()
{
	glDeleteBuffers(1, &m_id);
}

void vertex_buffer::set_vertex_data(float* vertices, u32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}

index_buffer::index_buffer(const void* indices, u32 count)
	: m_count(count)
{
	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
}

index_buffer::~index_buffer()
{
	delete_id();
}

void index_buffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void index_buffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void index_buffer::delete_id()
{
	glDeleteBuffers(1, &m_id);
}
