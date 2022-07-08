#pragma once

#include "gl_base_element.h"

class vertex_buffer : public gl_base_element
{
public:
	vertex_buffer() = default;
	vertex_buffer(const void* vertices, u32 size);
	vertex_buffer(u32 size);
	~vertex_buffer();

	virtual void bind() override;
	virtual void unbind() override;
	virtual void delete_id() override;

	void set_vertex_data(float* vertices, u32 size);

private:
};

class index_buffer : public gl_base_element 
{
public:
	index_buffer(const void* indices, u32 count);
	index_buffer() = default;
	~index_buffer();

	virtual void bind() override;
	virtual void unbind() override;
	virtual void delete_id() override;

	inline u32 get_count() const { return m_count; }
private:
	u32 m_count; 
};