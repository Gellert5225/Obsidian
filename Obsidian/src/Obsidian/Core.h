#pragma once

#ifdef OBSD_PLATFORM_WINDOWS
#if OBSD_DYNAMIC_LINK
	#ifdef OBSD_BUILD_DLL
		#define OBSIDIAN_API __declspec(dllexport)
	#else
		#define OBSIDIAN_API __declspec(dllimport)	
	#endif
#else
	#define OBSIDIAN_API
#endif
#else
	#error Obsidian only supports Windows!
#endif

#ifdef OBSD_DEBUG
	#define OBSD_ENABLE_ASSERTS
#endif

#ifdef OBSD_ENABLE_ASSERTS
	#define OBSD_ASSERT(x, ...) { if(!(x)) { OBSD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define OBSD_CORE_ASSERT(x, ...) { if(!(x)) { OBSD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define OBSD_ASSERT(x, ...)
	#define OBSD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define OBSD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)