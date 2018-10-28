#pragma once

#ifdef OBSD_PLATFORM_WINDOWS
	#ifdef OBSD_BUILD_DLL
		#define OBSIDIAN_API __declspec(dllexport)
	#else
		#define OBSIDIAN_API __declspec(dllimport)	
	#endif
#else
	#error Obsidian only supports Windows!
#endif