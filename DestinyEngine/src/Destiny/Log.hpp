/*
 *   Copyright (c) 2022 ItsSunnyMonster

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "spdlog/logger.h"

#include "Destiny/Exception.hpp"

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

} // namespace Destiny

#define DT_CORE_TRACE(...) ::Destiny::Log::getCoreLogger()->trace(__VA_ARGS__)
#define DT_CORE_INFO(...) ::Destiny::Log::getCoreLogger()->info(__VA_ARGS__)
#define DT_CORE_WARN(...) ::Destiny::Log::getCoreLogger()->warn(__VA_ARGS__)
#define DT_CORE_ERROR(...) ::Destiny::Log::getCoreLogger()->error(__VA_ARGS__)
#define DT_CORE_CRITICAL(...)                                                  \
  ::Destiny::Log::getCoreLogger()->critical(__VA_ARGS__)

#define DT_TRACE(...) ::Destiny::Log::getClientLogger()->trace(__VA_ARGS__)
#define DT_INFO(...) ::Destiny::Log::getClientLogger()->info(__VA_ARGS__)
#define DT_WARN(...) ::Destiny::Log::getClientLogger()->warn(__VA_ARGS__)
#define DT_ERROR(...) ::Destiny::Log::getClientLogger()->error(__VA_ARGS__)
#define DT_CRITICAL(...)                                                       \
  ::Destiny::Log::getClientLogger()->critical(__VA_ARGS__)

#define DT_ASSERT_MSG(x, msg)                                                  \
  if (!(x)) {                                                                  \
    __debugbreak();                                                            \
    throw Destiny::Exception(__LINE__, __FILE__, msg);                         \
  }
#define DT_ASSERT(x)                                                           \
  if (!(x)) {                                                                  \
    __debugbreak();                                                            \
    throw Destiny::Exception(__LINE__, __FILE__);                              \
  }
