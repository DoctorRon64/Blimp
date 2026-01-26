#pragma once

#include <memory>

#include "Core.h"
//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/stdout_color_sinks.h"

namespace Blimp {
	//TODO class BLIMP_API Log {
	class Log {
	public:
		static void Init();

		//inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLog; }
		//inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLog; }

	private:
		//static std::shared_ptr<spdlog::logger> s_CoreLog;
		//static std::shared_ptr<spdlog::logger> s_ClientLog;
	};
}

//core log macros
//#define BLIMP_CORE_TRACE(...)   ::Blimp::Log::GetCoreLogger()->trace(__VA_ARGS_)
//#define BLIMP_CORE_INFO(...)    ::Blimp::Log::GetCoreLogger()->info(__VA_ARGS_)
//#define BLIMP_CORE_WARN(...)    ::Blimp::Log::GetCoreLogger()->warn(__VA_ARGS_)
//#define BLIMP_CORE_ERROR(...)   ::Blimp::Log::GetCoreLogger()->error(__VA_ARGS_)
//#define BLIMP_CORE_FATAL(...)   ::Blimp::Log::GetCoreLogger()->fatal(__VA_ARGS_)
//
////client log macros
//#define BLIMP_TRACE(...)   ::Blimp::Log::GetClientLogger()->trace(__VA_ARGS_)
//#define BLIMP_INFO(...)    ::Blimp::Log::GetClientLogger()->info(__VA_ARGS_)
//#define BLIMP_WARN(...)    ::Blimp::Log::GetClientLogger()->warn(__VA_ARGS_)
//#define BLIMP_ERROR(...)   ::Blimp::Log::GetClientLogger()->error(__VA_ARGS_)
//#define BLIMP_FATAL(...)   ::Blimp::Log::GetClientLogger()->fatal(__VA_ARGS_)