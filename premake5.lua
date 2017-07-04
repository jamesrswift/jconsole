-- jConsole premake

local function boilerplate( DLL )

	includedirs "source"
	
	--defines { "SFML_STATIC" }

if ( DLL ) then
	links {	
		"opengl32.lib",
		"freetype.lib",
		"jpeg.lib",
		"winmm.lib",
		"gdi32.lib"
	}
end
	
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
			"sfml-graphics-d.lib",
			"sfml-window-d.lib",
			"sfml-system-d.lib",
		}

		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"

		links
		{ 	
			"sfml-graphics.lib",
			"sfml-window.lib",
			"sfml-system.lib",
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
	targetdir "bin/%{cfg.buildcfg}"
	
	defines { "JCON_EXPORTS" }
	files {"source/**.cpp", "source/**.hpp", "source/**.h"}
	
	boilerplate( true )
	
	
project "example"
	location "build/example"
	kind "ConsoleApp"
	dependson "jconsole"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	
	files {"example/main.cpp"}
	
	libdirs "bin/%{cfg.buildcfg}"
	links{ "jconsole.lib" }
	
	boilerplate( false )
	
