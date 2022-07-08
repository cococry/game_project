#pragma once

#include "core/defines.h"

#include "shader.h"
#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h>

#include "vertex_array.h"
#include "gl_buffer.h"

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coord;

	static std::vector<vertex> gen_list(f32* vertices, i32 nVertices);
};

class mesh
{
public:
	std::vector<vertex> vertices;
	std::vector<u32> indices;
	u32 vao;

	std::vector<texture_2d> textures;
	aiColor4D diffuse, specular;

	mesh() = default;
	mesh(const std::vector<vertex>& vertices, const std::vector<u32>& indices, const std::vector<texture_2d>& textures = {});
	mesh(const std::vector<vertex>& vertices, const std::vector<u32>& indices, const aiColor4D& diffuse, const aiColor4D& specular);
	void render(shader& shader);

	void clean_up();
private:
	bool m_NoTextures;
	u32 m_vb;
	u32 m_ib;

	void init();
};