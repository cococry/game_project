#pragma once

#include <glad/glad.h>
#include <vector>
#include <memory>

#include "gl_base_element.h"
#include "gl_buffer.h"

class vertex_array : public gl_base_element
{
public:
	vertex_array();
	~vertex_array();
	
	virtual void bind() override;
	virtual void unbind() override;
	virtual void delete_id() override;

	void set_vertex_layout_attrib(u32 index, u32 size, u64 stride, const void* offset, bool normalized = false, GLenum type = GL_FLOAT);
	
	inline void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& buffer) { m_vertex_buffers.push_back(buffer); }
	
	inline std::shared_ptr<index_buffer> get_index_buffer() const { return m_index_buffer; }

	void remove_vertex_buffer(const std::shared_ptr<vertex_buffer>& buffer);

	inline void set_index_buffer(const std::shared_ptr<index_buffer>& buffer) { m_index_buffer = buffer; }

private:
	std::vector<std::shared_ptr<vertex_buffer>> m_vertex_buffers;
	std::shared_ptr<index_buffer> m_index_buffer;
};