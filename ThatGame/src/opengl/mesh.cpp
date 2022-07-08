#include "glpch.h"
#include "mesh.h"

#include "render_commands.h"

std::vector<vertex> vertex::gen_list(f32* vertices, i32 nVertices)
{
	std::vector<vertex> returning(nVertices);

	i32 stride = sizeof(vertex) / sizeof(float);

	for (u32 i = 0; i < nVertices; i++) {
		returning[i].position = glm::vec3(
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);

		returning[i].normal = glm::vec3(
			vertices[i * stride + 3],
			vertices[i * stride + 4],
			vertices[i * stride + 5]
		);
		returning[i].tex_coord = glm::vec2(
			vertices[i * stride + 6],
			vertices[i * stride + 7]
		);
	}
	return returning;
}

mesh::mesh(const std::vector<vertex>& vertices, const std::vector<u32>& indices, const std::vector<texture_2d>& textures)
	: vertices(vertices), indices(indices), textures(textures), m_NoTextures(false)
{
	init();
}

mesh::mesh(const std::vector<vertex>& vertices, const std::vector<u32>& indices, const aiColor4D& diffuse, const aiColor4D& specular)
	: vertices(vertices), indices(indices), diffuse(diffuse), specular(specular), m_NoTextures(true)
{
	init();
}

void mesh::render(shader& shader)
{
	if (m_NoTextures) {
		shader.set_vec4("u_Material.diffuse", diffuse);
		shader.set_vec4("u_Material.specular", specular);
		shader.set_int("u_NoTex", 1);
	}
	else {
		u32 diffuseI = 0;
		u32 specularI = 0;

		for (u32 i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);

			std::string name;
			switch (textures[i].type) {
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuseI++);
				break;
			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specularI++);
				break;
			}

			std::cout << name << "\n";
			shader.set_int(name, i);
			textures[i].bind();
		}
	}
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void mesh::clean_up()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &m_vb);
	glDeleteBuffers(1, &m_ib);
}

void mesh::init()
{
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &m_vb);
	glBindBuffer(GL_ARRAY_BUFFER, m_vb);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glCreateBuffers(1, &m_ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tex_coord));

	glBindVertexArray(0);
}
