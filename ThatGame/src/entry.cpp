#include "glpch.h"
#include "core/application.h"

int main(){
	application* app;

	app = new application("ThatGame", 1920, 1080);
	app->run();

	delete app;
	return 0;
}

