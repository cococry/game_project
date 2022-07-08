#pragma once

#include "core/defines.h"
#include "mesh.h"
#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class model
{
public:
	glm::vec3 position;
	glm::vec3 size;

	model(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& size = glm::vec3(1.0f), bool noTextures = false);

	virtual void init() {};
	void load_model(const std::string& filepath);
	virtual void render(shader& shader);
	void clean_up();
protected:
	bool p_no_textures;
	std::vector<mesh> p_meshes;
	std::string p_directory;
	std::vector<texture_2d> p_textures_loaded;

	void process_node(aiNode* node, const aiScene* scene);
	mesh process_mesh(aiMesh* ai_mesh, const aiScene* scene);
	std::vector<texture_2d> load_textures(aiMaterial* mat, aiTextureType type);
};