#include "triangle_rasterization.h"

int main(int argc, char* argv[])
{
    TriangleRasterization* render = new TriangleRasterization(1920, 1080, "models/cube.obj");
    render->Clear();
    render->DrawScene();
    int result = render->Save("results/triangle_rasterization.png");
    return result;
}