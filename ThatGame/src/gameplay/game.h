#pragma once

#include <memory>

#include "core/defines.h"

#include "player.h"

class game
{
public:
	game();
	~game();

	void update();
	void shutdown();

	std::shared_ptr<player> game_player;
private:
	void init();
	
};