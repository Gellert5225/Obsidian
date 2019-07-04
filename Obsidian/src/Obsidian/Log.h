#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Obsidian {
	class OBSIDIAN_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// core log macro
#define OBSD_CORE_FATAL(...) ::Obsidian::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define OBSD_CORE_ERROR(...) ::Obsidian::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OBSD_CORE_WARN(...)  ::Obsidian::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OBSD_CORE_INFO(...)  ::Obsidian::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OBSD_CORE_TRACE(...) ::Obsidian::Log::GetCoreLogger()->trace(__VA_ARGS__)

// client log macro
#define OBSD_FATAL(...) ::Obsidian::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define OBSD_ERROR(...) ::Obsidian::Log::GetClientLogger()->error(__VA_ARGS__)
#define OBSD_WARN(...)  ::Obsidian::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OBSD_INFO(...)  ::Obsidian::Log::GetClientLogger()->info(__VA_ARGS__)
#define OBSD_TRACE(...) ::Obsidian::Log::GetClientLogger()->trace(__VA_ARGS__)