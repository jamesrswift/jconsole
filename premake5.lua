-- jConsole premake

local function boilerplate( )

	includedirs "source"
	
	defines { "SFML_STATIC" }

	links {	
		"opengl32.lib",
		"freetype.lib",
		"jpeg.lib",
		"winmm.lib",
		"gdi32.lib"
	}
	
	includedirs "dependencies/variant"
  
	filter "platforms:Win32"
		system "Windows"
		architecture "x32"
		libdirs "dependencies/x86/SFML/lib"
		includedirs "dependencies/x86/SFML/include"
		defines { "WIN32" }
	
	filter "platforms:Win64"
		system "Windows"
		architecture "x64"
		libdirs "dependencies/x64/SFML/lib"
		includedirs "dependencies/x64/SFML/include"
		defines { "WIN64" }
		
	filter "configurations:Debug"
		links
		{ 	
			"sfml-graphics-s-d.lib",
			"sfml-window-s-d.lib",
			"sfml-system-s-d.lib",
		}
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		links
		{ 	
			"sfml-graphics-s.lib",
			"sfml-window-s.lib",
			"sfml-system-s.lib",
		}
		defines { "RELEASE" }
		optimize "On"
		
end

platforms { "Win32", "Win64" }

workspace "jconsole"
	configurations { "Debug", "Release" }
	location "build"
	startproject "example"
	
project "jconsole"
	location "build/jconsole"
	kind "SharedLib"
	language "C++"
	targetdir "bin/jconsole/%{cfg.buildcfg}"
	
	defines { "JCON_EXPORTS" }
	files {"source/**.cpp", "source/**.hpp", "source/**.h"}
	files {"resources/fonts/consolas.ttf"}
	boilerplate( )
	
project "example"
	location "build/example"
	kind "ConsoleApp"
	dependson "jconsole"
	language "C++"
	targetdir "bin/example/%{cfg.buildcfg}"
	
	defines { "JCON_EXPORTS" }
	files {"source/**.cpp", "source/**.hpp", "source/**.h"}
	files {"example/main.cpp"}
	files {"resources/fonts/consolas.ttf"}
	
	--libdirs "bin/jconsole/%{cfg.buildcfg}"
	--links{ "jconsole.lib" }
	boilerplate( )
	
