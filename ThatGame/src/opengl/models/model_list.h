#pragma once

#include "physics\rigidbody.h"
#include "opengl\shader.h"

template<typename T>
class model_list
{
public:
	std::vector<rigid_body> instances;

	void init()
	{
		model.init();
	}

	void render(shader& shader, float dt)
	{
		for (rigid_body& rb : instances)
		{
			rb.update(dt);
			model.rb.pos = rb.pos;
			model.render(shader, true, dt);
		}
	}

	void set_scale(const glm::vec3& scale)
	{
		model.size = scale;
	}
protected:
	T model;
private:
	
};