#pragma once
#include "glpch.h"

#include "opengl/model.h"
#include "model_list.h"

class sphere : public model {
public:
	sphere(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f))
		: model(pos, size, true) {

	}

	void init()
	{
		load_model("assets/models/sphere/scene.gltf");
	}
};

class sphere_list : public model_list<sphere>
{
public:
	void init() 
	{
		model = sphere(glm::vec3(0.0f), glm::vec3(1.0f));
		model.init();
	}
};