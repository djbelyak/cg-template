#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "utils.h"

#include "black_image.h"

TEST_CASE("Black image test") {
    BlackImage* image = new BlackImage(1920, 1080);
    
    BENCHMARK("Clear") 
    {
        image->Clear();
    };
    
    REQUIRE(validate_framebuffer("references/black_image.png", image->GetFrameBuffer()));
}