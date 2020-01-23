#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "utils.h"

#include "z_buffer_culling.h"


TEST_CASE("Triangle rasterization test") {
    ZCulling* image = new ZCulling(1920, 1080, "models/cube.obj");
    image->Clear();

    BENCHMARK("Draw scene")
    {
        image->DrawScene();
    };

    REQUIRE(validate_framebuffer("references/z_buffer_cuilling.png", image->GetFrameBuffer()));
}