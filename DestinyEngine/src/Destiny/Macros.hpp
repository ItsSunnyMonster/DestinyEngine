#pragma once

#include <memory.h>

#ifdef DT_PLATFORM_WINDOWS
#include <wrl.h>
#endif

#define BIT(x) 1 << x

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Destiny
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> makeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> makeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

#ifdef DT_PLATFORM_WINDOWS

	template<typename T>
	using ComRef = Microsoft::WRL::ComPtr<T>;
#endif
}