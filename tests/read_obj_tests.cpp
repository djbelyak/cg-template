#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "utils.h"

#include "read_obj.h"

TEST_CASE("OBJ parser test") {
    ObjParser* parser = new ObjParser("models/cube.obj");
    int return_code = parser->Parse();
    REQUIRE(return_code == 0);
    REQUIRE(parser->GetFaces().size() == 12);

    REQUIRE(parser->GetFaces()[0].vertexes[0].x == -0.5);
    REQUIRE(parser->GetFaces()[0].vertexes[1].x == -0.5);
    REQUIRE(parser->GetFaces()[0].vertexes[2].x == 0.5);

    REQUIRE(parser->GetFaces()[0].vertexes[0].y == 0.5);
    REQUIRE(parser->GetFaces()[0].vertexes[1].y == 0.5);
    REQUIRE(parser->GetFaces()[0].vertexes[2].y == 0.5);

    REQUIRE(parser->GetFaces()[0].vertexes[0].z == -0.5);
    REQUIRE(parser->GetFaces()[0].vertexes[1].z == 0.5);
    REQUIRE(parser->GetFaces()[0].vertexes[2].z == 0.5);

}

TEST_CASE("Read OBJ test") {
    ReadObj* image = new ReadObj(1920, 1080, "models/cube.obj");
    image->Clear();

    BENCHMARK("Draw scene")
    {
        image->DrawScene();
    };

    REQUIRE(validate_framebuffer("references/read_obj.png", image->GetFrameBuffer()));
}