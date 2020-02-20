#include "draw_line.h"


#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>


LineDrawing::LineDrawing(unsigned short width, unsigned short height): ColorSpace(width, height)
{

}

LineDrawing::~LineDrawing() {
}

template<typename T>
int sign(T x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

void LineDrawing::DrawLine(unsigned short x_begin, unsigned short y_begin, unsigned short x_end, unsigned short y_end,
                           color color) {
    bool rotate = abs(x_end - x_begin) < abs(y_begin - y_end);

    if (rotate) {
        std::swap(x_begin, y_begin);
        std::swap(x_end, y_end);
    }

    if (x_end < x_begin) {
        std::swap(x_begin, x_end);
        std::swap(y_begin, y_end);
    }


    auto deltax = static_cast<float>(x_end - x_begin);
    auto deltay = static_cast<float>(y_end - y_begin);
    float deltaerr = abs(deltay / deltax);
    float error = 0.0;
    int y = y_begin;
    for (auto x = x_begin; x <= x_end; x++) {
        if (rotate)
            SetPixel(y, x, color);
        else
            SetPixel(x, y, color);
        error += deltaerr;
        if (error >= 0.5) {
            y += sign(deltay);
            error -= 1.f;
        }
    }
}

void LineDrawing::DrawScene() {

    for (auto angle = 0; angle < 360; angle += 5) {
        int radius = std::min(width, height) / 2 - 40;

        int x_center = width / 2;
        int y_center = height / 2;

        auto x_end = static_cast<int>(cos(angle * M_PI / 180.) * radius + x_center);
        auto y_end = static_cast<int>(sin(angle * M_PI / 180.) * radius + y_center);

        DrawLine(static_cast<unsigned short>(x_center),
                 static_cast<unsigned short>(y_center),
                 static_cast<unsigned short>(x_end),
                 static_cast<unsigned short>(y_end),
                 color{
                         static_cast<unsigned char>(255 * sin(angle * M_PI / 180.0)),
                         static_cast<unsigned char>(255 * cos(angle * M_PI / 180.0)),
                         255
                 });
    }
}

