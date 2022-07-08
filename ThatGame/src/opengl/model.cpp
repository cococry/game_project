#include "glpch.h"
#include "model.h"

model::model(const glm::vec3& position, const glm::vec3& size, bool noTextures)
	: position(position), size(size), p_no_textures(noTextures)
{

}

void model::load_model(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "[IMPORT]: ERROR: Could not load model at location '" << filepath << "'.\n" << importer.GetErrorString() << "\n";
		return;
	}

	p_directory = filepath.substr(0, filepath.find_last_of("/"));
	process_node(scene->mRootNode, scene);
}

void model::render(shader& shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, size);
	shader.set_mat4("u_Model", model);

	shader.set_float("u_Material.shininess", 0.5f);
	for (mesh& mesh : p_meshes) {
		mesh.render(shader);
	}
}

void model::clean_up()
{
	for (mesh& mesh : p_meshes) {
		mesh.clean_up();
	}
}

void model::process_node(aiNode* node, const aiScene* scene)
{
	// process meshes
	for (u32 i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		p_meshes.push_back(process_mesh(mesh, scene));
	}

	// process child nodes
	for (u32 i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene);
	}
}

mesh model::process_mesh(aiMesh* ai_mesh, const aiScene* scene)
{
	std::vector<vertex> vertices;
	std::vector<u32> indices;
	std::vector<texture_2d> textures;

	// vertices
	for (u32 i = 0; i < ai_mesh->mNumVertices; i++) {
		vertex vertex;

		vertex.position = glm::vec3(
			ai_mesh->mVertices[i].x,
			ai_mesh->mVertices[i].y,
			ai_mesh->mVertices[i].z
		);
		vertex.normal = glm::vec3(
			ai_mesh->mNormals[i].x,
			ai_mesh->mNormals[i].y,
			ai_mesh->mNormals[i].z
		);

		if (ai_mesh->mTextureCoords[0]) {
			vertex.tex_coord = glm::vec2(
				ai_mesh->mTextureCoords[0][i].x,
				ai_mesh->mTextureCoords[0][i].y
			);
		}
		else {
			vertex.tex_coord = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	// indices
	for (u32 i = 0; i < ai_mesh->mNumFaces; i++) {
		aiFace face = ai_mesh->mFaces[i];
		for (u32 j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// material
	if (ai_mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];

		if (p_no_textures) {
			aiColor4D diff(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diff);

			aiColor4D spec(1.0f);
			aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &spec);

			return mesh(vertices, indices, diff, spec);
		}

		std::vector<texture_2d> diffuseMaps = load_textures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<texture_2d> specularMaps = load_textures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return mesh(vertices, indices, textures);
}

std::vector<texture_2d> model::load_textures(aiMaterial* mat, aiTextureType type)
{
	std::vector<texture_2d> textures;

	for (u32 i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		std::cout << str.C_Str() << "\n";

		bool skip = false;
		for (u32 j = 0; j < p_textures_loaded.size(); j++) {
			if (std::strcmp(p_textures_loaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(p_textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			texture_2d tex(p_directory, str.C_Str(), type, false);
			textures.push_back(tex);
			p_textures_loaded.push_back(tex);
		}
	}

	return textures;
}
