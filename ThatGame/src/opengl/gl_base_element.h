#pragma once

#include "core/defines.h"

class gl_base_element
{
public:
	virtual void bind() {}
	virtual void unbind() {}
	virtual void delete_id() {}

	inline gl_id get_id() const { return m_id; }
protected:
	
	gl_id m_id;
};