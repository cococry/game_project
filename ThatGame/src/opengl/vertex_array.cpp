#include "glpch.h"
#include "vertex_array.h"

vertex_array::vertex_array()
{
	glCreateVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
}

vertex_array::~vertex_array()
{
	delete_id();
}

void vertex_array::bind()
{
	glBindVertexArray(m_id);
}

void vertex_array::unbind()
{
	glBindVertexArray(0);
}

void vertex_array::delete_id()
{
	glDeleteVertexArrays(1, &m_id);
}

void vertex_array::set_vertex_layout_attrib(u32 index, u32 size, u64 stride, const void* offset, bool normalized, GLenum type)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void vertex_array::remove_vertex_buffer(const std::shared_ptr<vertex_buffer>& buffer)
{
	auto it = std::find(m_vertex_buffers.begin(), m_vertex_buffers.end(), buffer);
	
	if (it != m_vertex_buffers.end())
	{
		m_vertex_buffers.erase(it);
	}
}
