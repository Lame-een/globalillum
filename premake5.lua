workspace "bacc_GIrt"
   architecture "x64"
   systemversion "latest"
   configurations { "Release", "Debug" }

project "GIrt"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   location "./GIrt/"
   pchheader("pch.h")
   pchsource("./GIrt/src/pch.cpp")

   targetdir "bin/x64/%{cfg.buildcfg}"
   objdir "bin/intermediates/%{cfg.buildcfg}"

   files { "./GIrt/src/**.h", "./GIrt/src/**.cpp" }
   includedirs {"GIrt/vendor", "GIrt/src", "GIrt/vendor/glm", "GIrt/vendor/nanoflann-1.4.3", }

   filter "configurations:Debug"
      defines { "_DEBUG", "PRINT_NORMALS", "GLM_ENABLE_EXPERIMENTAL" , "_CRT_SECURE_NO_WARNINGS" , "_USE_MATH_DEFINES" , "NDEBUG" , "_CONSOLE" }
      runtime "Debug"
      symbols "On"
      openmp "Off"

   filter "configurations:Release"
      defines { "GLM_ENABLE_EXPERIMENTAL" , "_CRT_SECURE_NO_WARNINGS" , "_USE_MATH_DEFINES" , "NDEBUG" , "_CONSOLE" }
      runtime "Release"
      optimize "On"
      openmp "On"
      filter {"action:gmake"}
         linkoptions {"-fopenmp"}