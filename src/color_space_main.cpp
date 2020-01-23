#include "color_space.h"

int main(int argc, char* argv[])
{
    ColorSpace* render = new ColorSpace(1920, 1080);
    render->Clear();
    render->DrawScene();
    int result = render->Save("results/color_space.png");
    return result;
}