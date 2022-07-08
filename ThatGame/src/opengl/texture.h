#pragma once
#include "core/defines.h"

#include <glad/glad.h>
#include <string>
#include <assimp/scene.h>

#include "gl_base_element.h"

class texture_2d : public gl_base_element
{
public:
	texture_2d() = default;
	texture_2d(const std::string& dir, const std::string& path, aiTextureType type, bool flipped = true);

	void activate(i32 slot = 0);

	virtual void bind() override;
	virtual void unbind() override;
	virtual void delete_id() override;

	inline i32 get_width() const { return m_width; }
	inline i32 get_height() const { return m_height; }
	inline i32 get_channels() const { return m_n_channels; }

	aiTextureType type;
	std::string dir, path;

private:
	i32 m_width, m_height, m_n_channels;
};