#pragma once

#include "core/defines.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <string>

#include "gl_base_element.h"

class shader : public gl_base_element
{
public:
	shader() = default;
	shader(const std::string& vertex_path, const std::string& fragment_path);
	~shader();

	virtual void bind() override;
	virtual void unbind() override;
	virtual void delete_id() override;


	void set_mat4(const std::string& name, const glm::mat4& value);
	void set_mat3(const std::string& name, const glm::mat3& value);
	void set_mat2(const std::string& name, const glm::mat2& value);
	void set_vec4(const std::string& name, const glm::vec4& value);
	void set_vec4(const std::string& name, const aiColor4D& value);
	void set_vec3(const std::string& name, const glm::vec3& value);
	void set_vec2(const std::string& name, const glm::vec2& value);
	void set_int(const std::string& name, i32 value);
	void set_float(const std::string& name, f32 value);

private:
	i32 compile(GLenum type, const std::string& filepath);
	void link(i32 vertexShader, i32 fragmentShader);
	std::string get_file_contents(const std::string& filepath);
};