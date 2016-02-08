-- A solution contains projects, and defines the available configurations
solution "sdl2template"
	configurations { "Debug", "Release"}

	flags { "Unicode" , "NoPCH"}

	projectName = "sdl2template"
	sourcePath = "src"
	binPath = "bin"

	-- A project defines one build target
	project (projectName)
		kind "ConsoleApp"
		language "C++"
		targetdir ( binPath )

		configuration { "windows" }
			buildoptions ""
			linkoptions { "/NODEFAULTLIB:msvcrt" } -- https://github.com/yuriks/robotic/blob/master/premake5.lua
		configuration { "linux" }
			buildoptions "-std=c++11" --http://industriousone.com/topic/xcode4-c11-build-option
			toolset "gcc"
		configuration {}

		files { path.join(sourcePath, "**.h"), path.join(sourcePath, "**.cpp") } -- build all .h and .cpp files recursively
		excludes { "./graphics_dependencies/**" }  -- don't build files in graphics_dependencies/


		-- where are header files?
		configuration "windows"
		includedirs {
							"./graphics_dependencies/SDL2/include",
							"./graphics_dependencies/SDL2/include/SDL2",
							"./graphics_dependencies/glew/include",
							"./graphics_dependencies/glm",
							"./graphics_dependencies/SDL2_image/include",
							"./graphics_dependencies/SDL2_ttf/include",
							"./graphics_dependencies/SDL2_mixer/include",
						 }
		configuration { "linux" }
		includedirs {
					 -- should be installed as in ./graphics_dependencies/README.asciidoc
						 }
		configuration {}


		-- what libraries need linking to
		configuration "windows"
			links { "SDL2", "SDL2main", "opengl32", "glew32", "SDL2_image", "SDL2_ttf", "SDL2_mixer" }
		configuration "linux"
			links { "SDL2", "SDL2main", "GL", "GLEW", "SDL2_image", "SDL2_ttf", "SDL2_mixer" }
		configuration {}

		-- where are libraries?
		configuration "windows"
		libdirs {
					"./graphics_dependencies/glew/lib/Release/Win32",
					"./graphics_dependencies/SDL2/lib/win32",
					"./graphics_dependencies/SDL2_image/lib/x86/",
					"./graphics_dependencies/SDL2_ttf/lib/x86/",
					"./graphics_dependencies/SDL2_mixer/lib/x86/",
					}
		configuration "linux"
					 -- should be installed as in ./graphics_dependencies/README.asciidoc
		configuration {}


		configuration "*Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			optimize "Off"
			targetsuffix "-debug"


		configuration "*Release"
			defines { "NDEBUG" }
			optimize "On"
			targetsuffix "-release"


		-- copy dlls on windows
		print("OS is:", os.get())
		if os.get() == "windows" then
			print("Copying binaries for Windows ...")
			os.mkdir(binPath)

			-- SDL2
			print("  ... SDL2")
			os.copyfile("./graphics_dependencies/SDL2/lib/win32/SDL2.dll", path.join(binPath, "SDL2.dll"))

			-- SDL2_image
			print("  ... SDL2_image")
			os.copyfile("./graphics_dependencies/SDL2_image/lib/x86/SDL2_image.dll", path.join(binPath, "SDL2_image.dll"))
			os.copyfile("./graphics_dependencies/SDL2_image/lib/x86/libjpeg-9.dll", path.join(binPath, "libjpeg-9.dll"))
			os.copyfile("./graphics_dependencies/SDL2_image/lib/x86/libpng16-16.dll", path.join(binPath, "libpng16-16.dll"))
			os.copyfile("./graphics_dependencies/SDL2_image/lib/x86/libtiff-5.dll", path.join(binPath, "libtiff-5.dll"))
			os.copyfile("./graphics_dependencies/SDL2_image/lib/x86/libwebp-4.dll", path.join(binPath, "libwebp-4.dll"))
			os.copyfile("./graphics_dependencies/SDL2_image/lib/x86/zlib1.dll", path.join(binPath, "zlib1.dll"))

			-- SDL2_ttf
			print("  ... SDL2_ttf")
			os.copyfile("./graphics_dependencies/SDL2_ttf/lib/x86/SDL2_ttf.dll", path.join(binPath, "SDL2_ttf.dll"))
			os.copyfile("./graphics_dependencies/SDL2_ttf/lib/x86/libfreetype-6.dll", path.join(binPath, "libfreetype-6.dll"))
				-- also requires zlib1, but copied already

			-- SDL2_mixer
			print("  ... SDL2_mixer")
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/SDL2_mixer.dll", path.join(binPath, "SDL2_mixer.dll"))
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/libFLAC-8.dll", path.join(binPath, "libFLAC-8.dll"))
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/libmodplug-1.dll", path.join(binPath, "libmodplug-1.dll"))
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/libogg-0.dll", path.join(binPath, "libogg-0.dll"))
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/libvorbis-0.dll", path.join(binPath, "libvorbis-0.dll"))
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/libvorbisfile-3.dll", path.join(binPath, "libvorbisfile-3.dll"))
			os.copyfile("./graphics_dependencies/SDL2_mixer/lib/x86/smpeg2.dll", path.join(binPath, "smpeg2.dll"))

			-- glew
			print("  ... glew")
			os.copyfile("./graphics_dependencies/glew/bin/Release/Win32/glew32.dll", path.join(binPath, "glew32.dll"))
		end
