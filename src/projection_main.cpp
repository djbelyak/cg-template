#include "projection.h"

int main(int argc, char* argv[])
{
    Projection* render = new Projection(1920, 1080, "models/cube.obj");
    render->Clear();
    render->DrawScene();
    int result = render->Save("results/projection.png");
    return result;
}