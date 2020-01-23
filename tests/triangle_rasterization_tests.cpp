#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "utils.h"

#include "triangle_rasterization.h"


TEST_CASE("Triangle rasterization test") {
    TriangleRasterization* image = new TriangleRasterization(1920, 1080, "models/cube.obj");
    image->Clear();

    BENCHMARK("Draw scene")
    {
        image->DrawScene();
    };

    REQUIRE(validate_framebuffer("references/triangle_rasterization.png", image->GetFrameBuffer()));
}