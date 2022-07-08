#include "glpch.h"
#include "texture.h"

#include <stb_image.h>

texture_2d::texture_2d(const std::string& dir, const std::string& path, aiTextureType type, bool flipped)
	: dir(dir), path(path), type(type)
{

	glCreateTextures(GL_TEXTURE_2D, 1, & m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	stbi_set_flip_vertically_on_load(flipped);

	u8* data = stbi_load((dir + "/" + path).c_str(), &m_width, &m_height, &m_n_channels, 0);

	GLenum internalFormat = GL_RGB;
	GLenum format = GL_RGB;

	if (m_n_channels == 4) {
		internalFormat = GL_RGBA;
		format = GL_RGBA;
	}

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else {
		std::cout << "[TEXTURE]: Failed to load texture\n";
	}

	stbi_image_free(data);
}

void texture_2d::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void texture_2d::activate(i32 slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
}

void texture_2d::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_2d::delete_id()
{
	glDeleteTextures(1, &m_id);
}
