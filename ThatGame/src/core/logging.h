#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

class log 
{
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger> get_logger() { return s_logger; }
private:
	static std::shared_ptr<spdlog::logger> s_logger;
};

#define LOG_INFO(...) log::get_logger()->info(__VA_ARGS__)
#define LOG_DEBUG(...) log::get_logger()->debug(__VA_ARGS__)
#define LOG_TRACE(...) log::get_logger()->trace(__VA_ARGS__)
#define LOG_WARN(...) log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) log::get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) log::get_logger()->critical(__VA_ARGS__)

