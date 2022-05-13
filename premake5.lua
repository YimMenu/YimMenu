workspace "BigBaseV2"
	architecture "x64"
	startproject "BigBaseV2"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}"

	CppVersion = "C++17"
	MsvcToolset = "v143"
	WindowsSdkVersion = "10.0"
  
	function DeclareMSVCOptions()
		filter "system:windows"
		staticruntime "Off"
		floatingpoint "Fast"
		systemversion (WindowsSdkVersion)
		toolset (MsvcToolset)
		cppdialect (CppVersion)

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"NOMINMAX",
			"WIN32_LEAN_AND_MEAN",
			"_WIN32_WINNT=0x601" -- Support Windows 7
		}

		disablewarnings
		{
			"4100", -- C4100: unreferenced formal parameter
			"4201", -- C4201: nameless struct/union
			"4307",  -- C4307: integral constant overflow
			"4996"  -- C4996: deprecated in C++17
		}
	end
  
	function file_exists(name)
		local f=io.open(name,"r")
		if f~=nil then io.close(f) return true else return false end
	end
   
	function DeclareDebugOptions()
		filter "configurations:Debug"
		    defines { "_DEBUG" }
		    symbols "On"
		filter "not configurations:Debug"
		    defines { "NDEBUG" }
	end

	project "fmtlib"
		location "vendor/%{prj.name}"
		kind "StaticLib"
		language "C++"

		targetdir ("bin/lib/" .. outputdir)
		objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"vendor/%{prj.name}/include/**.h",
			"vendor/%{prj.name}/src/**.cc"
		}

		includedirs
		{
			"vendor/%{prj.name}/include"
		}

		DeclareMSVCOptions()
		DeclareDebugOptions()
	
	project "g3log"
		location "vendor/%{prj.name}"
		kind "StaticLib"
		language "C++"

		targetdir ("bin/lib/" .. outputdir)
		objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")
		
		includedirs
		{
		    "vendor/%{prj.name}/src"
		}

		if(file_exists("vendor\\g3log\\src\\g3log\\generated_definitions.hpp") == false) then
			file = io.open("vendor\\g3log\\src\\g3log\\generated_definitions.hpp", "w")
			if(file == nil) then
				premake.error("Failed to locate vendor directories. Try doing git pull --recurse-submodules.")
			end
			file:write("#pragma once");
		end
		
		files
		{
		    "vendor/%{prj.name}/src/**.hpp",
		    "vendor/%{prj.name}/src/**.cpp"
		}
		
		removefiles
		{
		    "vendor/%{prj.name}/src/crashhandler_unix.cpp"
		}

		DeclareMSVCOptions()
		DeclareDebugOptions()
   
	project "ImGui"
		location "vendor/%{prj.name}"
		kind "StaticLib"
		language "C++"

		targetdir ("bin/lib/" .. outputdir)
		objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")
		
		files
		{
			"vendor/%{prj.name}/imgui.cpp",
			"vendor/%{prj.name}/imgui_draw.cpp",
			"vendor/%{prj.name}/imgui_tables.cpp",
			"vendor/%{prj.name}/imgui_widgets.cpp",
			"vendor/%{prj.name}/backends/imgui_impl_dx11.cpp",
			"vendor/%{prj.name}/backends/imgui_impl_win32.cpp"
		}

		includedirs
		{
			"vendor/%{prj.name}"
		}
		
		defines {
			"IMGUI_DISABLE_DEMO_WINDOWS",
			"IMGUI_DISABLE_METRICS_WINDOW",
			"IM_ASSERT(_EXPR) ((void)(_EXPR))"
		}

		DeclareMSVCOptions()
		DeclareDebugOptions()

	project "MinHook"
		location "vendor/%{prj.name}"
		kind "StaticLib"
		language "C"

		targetdir ("bin/lib/" .. outputdir)
		objdir ("bin/lib/int/" .. outputdir .. "/%{prj.name}")

		files
		{
		    "vendor/%{prj.name}/include/**.h",
		    "vendor/%{prj.name}/src/**.h",
		    "vendor/%{prj.name}/src/**.c"
		}

		DeclareMSVCOptions()
		DeclareDebugOptions()

	project "BigBaseV2"
		location "BigBaseV2"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir)
		objdir ("bin/int/" .. outputdir .. "/%{prj.name}")
	 
		files
		{
		    "%{prj.name}/src/**.hpp",
		    "%{prj.name}/src/**.h",
		    "%{prj.name}/src/**.cpp",
		    "%{prj.name}/src/**.asm"
		}

		includedirs
		{
			"%{prj.name}/src/",
		    "vendor/fmtlib/include",
		    "vendor/g3log/src",
		    "vendor/GTAV-Classes",
		    "vendor/ImGui",
		    "vendor/json/single_include",
		    "vendor/MinHook/include"
		}

		libdirs
		{
		    "bin/lib"
		}

		links
		{
		    "fmtlib",
		    "g3log",
		    "ImGui",
		    "MinHook"
		}

		pchheader "common.hpp"
		pchsource "%{prj.name}/src/common.cpp"

		forceincludes { -- microsoft bad
		    "common.hpp"
		}

		DeclareMSVCOptions()
		DeclareDebugOptions()

		flags { "NoImportLib", "Maps", "LinkTimeOptimization", "MultiProcessorCompile" }

		filter "configurations:Debug"
		    flags {  }
		    editandcontinue "Off"
		    defines { "DEBUG" }

		filter "configurations:Release"
		    flags { "NoManifest" }
		    defines { "RELEASE" }
		    optimize "speed"
		filter "configurations:Dist"
		    flags { "FatalWarnings", "NoManifest" }
		    defines { "DIST" }
		    optimize "speed"
