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
IncludeDir["stb_image"] = "Obsidian/vendor/stb_image"

group "Dependencies"
	include "Obsidian/vendor/GLFW"
	include "Obsidian/vendor/GLAD"
	include "Obsidian/vendor/imgui"

project "Obsidian"
	location "Obsidian"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "obsdpch.h"
	pchsource "Obsidian/src/obsdpch.cpp"
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"OBSD_PLATFORM_WINDOWS",
			"OBSD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OBSD_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Obsidian"
	}

	filter "system:windows"
		systemversion "10.0.17134.0"

		defines
		{
			"OBSD_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OBSD_Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		runtime "Release"
		optimize "on"