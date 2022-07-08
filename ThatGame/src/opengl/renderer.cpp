#include "glpch.h"
#include "renderer.h"

#include "core/application.h"

#include <glm/gtc/matrix_transform.hpp>

void render::render_mesh(mesh& mesh_instc, shader& shader)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	view = APP_INSTC->game_instc->game_player->get_camera()->get_view_matrix();
	projection = glm::perspective(glm::radians(APP_INSTC->game_instc->game_player->get_camera()->get_fov()),
		((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), 0.1f, 1000.0f);


	shader.set_mat4("u_Projection", projection);
	shader.set_mat4("u_View", view);
	shader.set_mat4("u_Model", model);
	
	mesh_instc.render(shader);
}
