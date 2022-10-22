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

#include <dtpch.hpp>

#define BIT(x) 1 << x

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define DT_PWSTR(x) (wchar_t *)utf8::utf8to16(x).c_str()
#define DT_U8STR(x) utf8::utf16to8((char16_t *)x)
#define DT_U8(x) (char *)u8##x

namespace Destiny {
template <typename T> using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> makeScope(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T> using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> makeRef(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

#ifdef DT_PLATFORM_WINDOWS

template <typename T> using ComRef = Microsoft::WRL::ComPtr<T>;
#endif
} // namespace Destiny