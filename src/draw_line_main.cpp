#include "draw_line.h"

int main(int argc, char* argv[])
{
    LineDrawing* render = new LineDrawing(1920, 1080);
    render->Clear();
    render->DrawScene();
    int result = render->Save("results/draw_line.png");
    return result;
}