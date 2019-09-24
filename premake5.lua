-- premake5.lua
workspace "HueEngine"
   configurations { "Debug", "Release" }

project "HueEngine"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   links {"m", "allegro", "allegro_ttf", "allegro_font", "allegro_color", "allegro_image", "allegro_primitives" }

   files { "**.h", "**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
