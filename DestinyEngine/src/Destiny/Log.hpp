/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 15/04/22.
//

#pragma once

#include "spdlog/logger.h"

namespace Destiny {
	class Log {
	public:
		static void init();
		inline static const auto getCoreLogger() { return s_CoreLogger; }
		inline static const auto getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define DT_CORE_TRACE(...)		::Destiny::Log::getCoreLogger()->trace(__VA_ARGS__)
#define DT_CORE_INFO(...)		::Destiny::Log::getCoreLogger()->info(__VA_ARGS__)
#define DT_CORE_WARN(...)		::Destiny::Log::getCoreLogger()->warn(__VA_ARGS__)
#define DT_CORE_ERROR(...)		::Destiny::Log::getCoreLogger()->error(__VA_ARGS__)
#define DT_CORE_CRITICAL(...)	::Destiny::Log::getCoreLogger()->critical(__VA_ARGS__)

#define DT_TRACE(...)		::Destiny::Log::getClientLogger()->trace(__VA_ARGS__)
#define DT_INFO(...)		::Destiny::Log::getClientLogger()->info(__VA_ARGS__)
#define DT_WARN(...)		::Destiny::Log::getClientLogger()->warn(__VA_ARGS__)
#define DT_ERROR(...)		::Destiny::Log::getClientLogger()->error(__VA_ARGS__)
#define DT_CRITICAL(...)	::Destiny::Log::getClientLogger()->critical(__VA_ARGS__)
