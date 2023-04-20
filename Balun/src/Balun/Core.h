#pragma once
#ifdef BL_PLATFORM_WINDOWS
	#ifdef BL_BUILD_DLL
		#define BALUN_API  __declspec(dllexport)
	#else
		#define BALUN_API  __declspec(dllimport)
	#endif // BL_BUILD_DLL
#else
	#error Balun is only support Windows
#endif

#ifdef BL_DEBUG
	#define BL_ENABLE_ASSERTS
#endif

#ifdef BL_ENABLE_ASSERTS
	#define BL_ASSERT(x, ...) {if(!(x)) {BL_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define BL_CORE_ASSERT(x, ...){if(!(x)) {BL_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define BL_ASSERT(x, ...)
	#define BL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define BL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)