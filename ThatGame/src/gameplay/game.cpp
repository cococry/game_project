#include "glpch.h"
#include "game.h"

game::game()
{
	init();
}

game::~game()
{
	shutdown();
}

void game::update()
{
	game_player->update();
}

void game::shutdown()
{
	game_player->shutdown();
}

void game::init()
{
	game_player = std::make_shared<player>(glm::vec3(0.0f, 0.0f, 3.0f));
}
