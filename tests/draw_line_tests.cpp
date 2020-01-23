#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "utils.h"

#include "draw_line.h"

TEST_CASE("Draw line test") {
    LineDrawing* image = new LineDrawing(1920, 1080);
    image->Clear();
    
    BENCHMARK("Draw scene") 
    {
        image->DrawScene();
    };
    
    REQUIRE(validate_framebuffer("references/draw_line.png", image->GetFrameBuffer()));
}