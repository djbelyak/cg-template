#include "black_image.h"

int main(int argc, char* argv[])
{
    BlackImage* render = new BlackImage(1920, 1080);
    render->Clear();
    int result = render->Save("results/black_image.png");
    return result;
}