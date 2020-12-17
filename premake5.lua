workspace "Obsidian"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["ImGui"] = "Obsidian/vendor/imgui"
IncludeDir["glm"] = "Obsidian/vendor/glm"

include "Obsidian/vendor/GLFW"
include "Obsidian/vendor/GLAD"
include "Obsidian/vendor/imgui"

project "Obsidian"
	location "Obsidian"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "obsdpch.h"
	pchsource "Obsidian/src/obsdpch.cpp"
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"OBSD_PLATFORM_WINDOWS",
			"OBSD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "OBSD_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	staticruntime "off"

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
		"Obsidian/src",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Obsidian"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.17134.0"

		defines
		{
			"OBSD_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "OBSD_Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		runtime "Release"
		optimize "On"