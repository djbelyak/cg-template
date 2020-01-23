#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "utils.h"

#include "color_space.h"

TEST_CASE("Color space test") {
    ColorSpace* render = new ColorSpace(1920, 1080);

    render->Clear();

    BENCHMARK("Draw scene") 
    {
        render->DrawScene();
    };
    
    REQUIRE(validate_framebuffer("references/color_space.png", render->GetFrameBuffer()));
}