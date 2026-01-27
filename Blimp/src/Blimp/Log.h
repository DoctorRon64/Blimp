#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Events/EventFormatter.h"

namespace Blimp {
	class BLIMP_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLog; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLog; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLog;
		static std::shared_ptr<spdlog::logger> s_ClientLog;
	};
}

//core log macros
#define BLIMP_CORE_TRACE(...)   ::Blimp::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BLIMP_CORE_INFO(...)    ::Blimp::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BLIMP_CORE_WARN(...)    ::Blimp::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BLIMP_CORE_ERROR(...)   ::Blimp::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BLIMP_CORE_FATAL(...)   ::Blimp::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define BLIMP_TRACE(...)   ::Blimp::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BLIMP_INFO(...)    ::Blimp::Log::GetClientLogger()->info(__VA_ARGS__)
#define BLIMP_WARN(...)    ::Blimp::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BLIMP_ERROR(...)   ::Blimp::Log::GetClientLogger()->error(__VA_ARGS__)
#define BLIMP_FATAL(...)   ::Blimp::Log::GetClientLogger()->fatal(__VA_ARGS__)
