// Credit to the Hazel Engine by TheCherno on Github
// https://github.com/TheCherno/Hazel

#pragma once

#ifdef DT_PLATFORM_WINDOWS

#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif // !NOMINMAX

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <d3d11.h>
#include <CommCtrl.h>
#include <wrl.h>

#endif // DT_PLATFORM_WINDOWS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <exception>
#include <format>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <utf8.h>

#include "Destiny/Log.hpp"
#include "Destiny/Macros.hpp"