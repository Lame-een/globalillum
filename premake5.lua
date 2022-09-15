workspace "BACC_Global_Illumination"
   architecture "x64"
   systemversion "latest"
   configurations { "Release", "Debug" }

project "GlobalIllumination"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   location "./LiVHY/"
   pchheader("pch.h")
   pchsource("./LiVHY/src/pch.cpp")

   targetdir "bin/x64/%{cfg.buildcfg}"
   objdir "bin/intermediates/%{cfg.buildcfg}"

   files { "./LiVHY/src/**.h", "./LiVHY/src/**.cpp" }
   includedirs {"LiVHY/vendor", "LiVHY/src", "LiVHY/vendor/glm", "LiVHY/vendor/nanoflann-1.4.3", }

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