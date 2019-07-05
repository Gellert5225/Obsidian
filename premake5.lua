workspace "Obsidian"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Obsidian/vendor/GLFW/include"
IncludeDir["GLAD"] = "Obsidian/vendor/GLAD/include"

include "Obsidian/vendor/GLFW"
include "Obsidian/vendor/GLAD"

project "Obsidian"
	location "Obsidian"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "obsdpch.h"
	pchsource "Obsidian/src/obsdpch.cpp"
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OBSD_PLATFORM_WINDOWS",
			"OBSD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "OBSD_Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Obsidian/vendor/spdlog/include",
		"Obsidian/src"
	}

	links
	{
		"Obsidian"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17134.0"

		defines
		{
			"OBSD_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "OBSD_Release"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		buildoptions "/MD"
		optimize "On"