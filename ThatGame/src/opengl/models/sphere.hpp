#pragma once
#include "glpch.h"

#include "opengl/model.h"

class sphere : public model {
public:
	sphere(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& size = glm::vec3(1.0f))
		: model(pos, size, true) {}

	void init()
	{
		load_model("assets/models/sphere/scene.gltf");
	}
};