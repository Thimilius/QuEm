output_directory_format = "%{cfg.system}-%{cfg.architecture}"

workspace "quem"
	startproject "quem"

	targetdir ("build/%{cfg.buildcfg}/bin/" .. output_directory_format)
	objdir ("build/%{cfg.buildcfg}/obj/" .. output_directory_format)

	configurations { "debug", "release" }

	filter "configurations:debug"	
		runtime "Debug"
		symbols "On"
	filter "configurations:release"
		runtime "Release"
		optimize "On"
	
	filter "system:windows"
		defines { "_CRT_SECURE_NO_WARNINGS", "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS" }
		systemversion "latest"
		linkoptions { "/IGNORE:4099" }

project "quem"
	location "quem"
	
	language "C++"
	cppdialect "C++20"
	architecture "x86_64"
	kind "ConsoleApp"

	staticruntime "On"
	exceptionhandling "Off"
	rtti "Off"
	flags { "FatalCompileWarnings" }
	
	files { "%{prj.location}/**.hpp", "%{prj.location}/**.cpp" }
	