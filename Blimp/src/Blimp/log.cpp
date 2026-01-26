#include "Log.h"

namespace Blimp {
	std::shared_ptr<spdlog::logger> Log::s_CoreLog;
	std::shared_ptr<spdlog::logger> Log::s_ClientLog;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLog = spdlog::stdout_color_mt("[Blimp_Engine]");
		s_CoreLog->set_level(spdlog::level::trace);

		s_ClientLog = spdlog::stdout_color_mt("[App]");
		s_ClientLog->set_level(spdlog::level::trace);
	}
}
