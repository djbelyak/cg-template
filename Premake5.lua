workspace "Computer Graphics"
   configurations { "Debug", "Release" }
   language "C++"
   architecture "x64"
   systemversion "latest"
   toolset "v142"
   optimize "Speed"
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

   targetdir ("bin/%{prj.name}/%{cfg.longname}")
   objdir ("obj/%{prj.name}/%{cfg.longname}")


group "01. Black image"
   project "Black image lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp" }
   
   project "Black image app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Black image lib"
      files { "src/black_image_main.cpp" }
   
   project "Black image tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/black_image_tests.cpp" }
      links "Black image lib"
      debugargs { "--benchmark-samples", "25" }
--[[
group "02. Color space"
   project "Color space lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp" }
   
   project "Color space app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Color space lib"
      files { "src/color_space_main.cpp" }
   
   project "Color space tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/color_space_tests.cpp" }
      links "Color space lib"
      debugargs { "--benchmark-samples", "25" }

group "03. Draw line"
   project "Draw line lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp" }

   project "Draw line app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Draw line lib"
      files { "src/draw_line_main.cpp" }

   project "Draw line tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/draw_line_tests.cpp" }
      links "Draw line lib"
      debugargs { "--benchmark-samples", "25" }

group "04. Read obj"
   project "Read obj lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp" }

   project "Read obj app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Read obj lib"
      files { "src/read_obj_main.cpp" }

   project "Read obj tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/read_obj_tests.cpp" }
      links "Read obj lib"
      debugargs { "--benchmark-samples", "25" }

group "05. Projection"
   project "Projection lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp", "src/projection.h", "src/projection.cpp" }
      
   project "Projection app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Projection lib"
      files { "src/projection_main.cpp" }

   project "Projection tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/projection_tests.cpp" }
      links "Projection lib"
      debugargs { "--benchmark-samples", "25" }

group "06. Triangle rasterization"
   project "Triangle rasterization lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp", "src/projection.h", "src/projection.cpp", "src/triangle_rasterization.h", "src/triangle_rasterization.cpp" }
      
   project "Triangle rasterization app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Triangle rasterization lib"
      files { "src/triangle_rasterization_main.cpp" }

   project "Triangle rasterization tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/triangle_rasterization_tests.cpp" }
      links "Triangle rasterization lib"
      debugargs { "--benchmark-samples", "25" }

group "07. Z-buffer culling"
   project "Z buffer culling lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp", "src/projection.h", "src/projection.cpp", "src/triangle_rasterization.h", "src/triangle_rasterization.cpp", "src/z_buffer_culling.h", "src/z_buffer_culling.cpp"  }
      
   project "Z buffer culling app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Z buffer culling lib"
      files { "src/z_buffer_culling_main.cpp" }

   project "Z buffer culling tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/z_buffer_culling_tests.cpp" }
      links "Z buffer culling lib"
      debugargs { "--benchmark-samples", "25" }

group "08. Phong model"
   project "Phong model lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp", "src/projection.h", "src/projection.cpp", "src/triangle_rasterization.h", "src/triangle_rasterization.cpp", "src/z_buffer_culling.h", "src/z_buffer_culling.cpp", "src/phong_model.h", "src/phong_model.cpp"   }
      
   project "Phong model app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Phong model lib"
      files { "src/phong_model_main.cpp" }

   project "Phong model tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/phong_model_tests.cpp" }
      links "Phong model lib"
      debugargs { "--benchmark-samples", "25" }

group "09. Texturing"
   project "Texturing lib"
      kind "StaticLib"
      includedirs { "src/" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp", "src/projection.h", "src/projection.cpp", "src/triangle_rasterization.h", "src/triangle_rasterization.cpp", "src/z_buffer_culling.h", "src/z_buffer_culling.cpp", "src/phong_model.h", "src/phong_model.cpp", "src/texturing.h", "src/texturing.cpp"      }
      
   project "Texturing app"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/linalg"}
      links "Texturing lib"
      files { "src/texturing_main.cpp" }

   project "Texturing tests"
      kind "ConsoleApp"
      includedirs { "src" }
      includedirs { "lib/stb" }
      includedirs { "lib/linalg"}
      includedirs { "lib/catch2/single_include/catch2" }
      files { "lib/stb/stb_image.h", "tests/utils.h", "tests/texturing_tests.cpp" }
      links "Texturing lib"
      debugargs { "--benchmark-samples", "25" }

group "10. Shadow mapping"
      project "Shadow mapping lib"
         kind "StaticLib"
         includedirs { "src/" }
         includedirs { "lib/stb" }
         includedirs { "lib/linalg"}
         files { "lib/stb/stb_image_write.h", "lib/linalg/linalg.h",  "src/structs.h", "src/black_image.h", "src/black_image.cpp", "src/color_space.h", "src/color_space.cpp", "src/draw_line.h", "src/draw_line.cpp", "src/read_obj.h", "src/read_obj.cpp", "src/projection.h", "src/projection.cpp", "src/triangle_rasterization.h", "src/triangle_rasterization.cpp", "src/z_buffer_culling.h", "src/z_buffer_culling.cpp", "src/phong_model.h", "src/phong_model.cpp", "src/texturing.h", "src/texturing.cpp", "src/shadow_mapping.h", "src/shadow_mapping.cpp" }
         
      project "Shadow mapping app"
         kind "ConsoleApp"
         includedirs { "src" }
         includedirs { "lib/linalg"}
         links "Shadow mapping lib"
         files { "src/shadow_mapping_main.cpp" }
   
      project "Shadow mapping tests"
         kind "ConsoleApp"
         includedirs { "src" }
         includedirs { "lib/stb" }
         includedirs { "lib/linalg"}
         includedirs { "lib/catch2/single_include/catch2" }
         files { "lib/stb/stb_image.h", "tests/utils.h", "tests/shadow_mapping_tests.cpp" }
         links "Shadow mapping lib"
         debugargs { "--benchmark-samples", "25" }
--]]