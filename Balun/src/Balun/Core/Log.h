#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Balun {

	class BALUN_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

#define BL_CORE_TRACE(...)    ::Balun::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BL_CORE_INFO(...)     ::Balun::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BL_CORE_WARN(...)     ::Balun::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BL_CORE_ERROR(...)    ::Balun::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BL_CORE_FATAL(...)    ::Balun::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define BL_TRACE(...)    ::Balun::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BL_INFO(...)     ::Balun::Log::GetClientLogger()->info(__VA_ARGS__)
#define BL_WARN(...)     ::Balun::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BL_ERROR(...)    ::Balun::Log::GetClientLogger()->error(__VA_ARGS__)
#define BL_FATAL(...)    ::Balun::Log::GetClientLogger()->fatal(__VA_ARGS__)
}

