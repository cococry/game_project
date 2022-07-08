#include "glpch.h"
#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

shader::shader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
	u32 vertexShader = compile(GL_VERTEX_SHADER, vertexFilepath);
	u32 fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentFilepath);

	link(vertexShader, fragmentShader);
}

shader::~shader()
{
	glDeleteProgram(m_id);
}

void shader::bind()
{
	glUseProgram(m_id);
}

void shader::unbind()
{
	glUseProgram(0);
}

void shader::delete_id()
{
	glDeleteProgram(m_id);
}

void shader::set_mat4(const std::string& name, const glm::mat4& value)
{
	
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_mat3(const std::string& name, const glm::mat3& value)
{
	
	glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_mat2(const std::string& name, const glm::mat2& value)
{
	
	glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_vec4(const std::string& name, const glm::vec4& value)
{
	
	glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_vec4(const std::string& name, const aiColor4D& value)
{
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.r, value.g, value.b, value.a);
}

void shader::set_vec3(const std::string& name, const glm::vec3& value)
{
	
	glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_vec2(const std::string& name, const glm::vec2& value)
{
	
	glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_int(const std::string& name, i32 value)
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void shader::set_float(const std::string& name, f32 value)
{
	
	glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

i32 shader::compile(GLenum type, const std::string& filepath)
{
	int success;
	char infoLog[512];
	u32 shader;
	shader = glCreateShader(type);
	std::string shaderSource = get_file_contents(filepath);
	const char* shaderSourceCSTR = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourceCSTR, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::string shaderStr = type == GL_FRAGMENT_SHADER ? "fragment" : "vertex";
		std::cout << "[SHADER COMPILATION]: Failed to compile " << shaderStr << " shader:\n" << infoLog << "\n";
	}
	return shader;
}

void shader::link(i32 vertexShader, i32 fragmentShader)
{
	int success;
	char infoLog[512];

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << "[SHADER LINKING]: Failed to link shader program:\n " << infoLog << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::string shader::get_file_contents(const std::string& filepath)
{
	std::ifstream file;
	std::stringstream ss;
	std::string returning = "";

	file.open(filepath);

	if (file.is_open()) {
		ss << file.rdbuf();
		returning = ss.str();
	}
	else {
		std::cout << "[FILE]: Could not open file at '" << filepath << "'\n";
	}
	return returning;
}
