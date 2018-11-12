workspace "Obsidian"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Obsidian"
	location "Obsidian"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17134.0"

		defines
		{
			"OBSD_PLATFORM_WINDOWS",
			"OBSD_BUILD_DLL"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "OBSD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OBSD_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		optimize "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

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
		symbols "On"

	filter "configurations:Release"
		defines "OBSD_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "OBSD_DIST"
		optimize "On"