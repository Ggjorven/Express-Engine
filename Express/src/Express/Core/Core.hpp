#pragma once
#include "expch.h"

#ifdef EX_PLATFORM_WINDOWS

#else
	#error Express Engine only supports windows at the time.
#endif


#define EX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
//#define EX_FUNC(returntype, name, ...) typedef returntype (* name) (__VA_ARGS__)

#define BIT(x) (1 << x)

namespace Express
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}