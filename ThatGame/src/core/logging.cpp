#include "glpch.h"
#include "logging.h"

std::shared_ptr<spdlog::logger> log::s_logger;

void log::init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_logger = spdlog::stdout_color_mt("GAME");
	s_logger->set_level(spdlog::level::trace);
}