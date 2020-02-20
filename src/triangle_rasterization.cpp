#include "triangle_rasterization.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


TriangleRasterization::TriangleRasterization(unsigned short width, unsigned short height, std::string obj_file) : Projection(width, height, obj_file)
{
}

TriangleRasterization::~TriangleRasterization()
{
}

void TriangleRasterization::DrawScene()
{
    parser->Parse();
    auto faces = parser->GetFaces();

    float2 center = {float(width) / 2, float(height) / 2};

    float3 eye = {0, 0, 2};
    float3 at{0, 0, 0};
    float3 up{0, 1, 0};
    auto proj = project(faces, getWorld(), getView(eye, at, up), getProjection());

    for (auto &f: proj) {

        float2 triangle[3];
        for (int i = 0; i < 3; i++) {
            triangle[i] = f.vertexes[i].xy() / f.vertexes[i].w + center;
        }

        DrawTriangle(triangle);
    }

    for (auto &f: proj) {

        float2 triangle[3];
        for (int i = 0; i < 3; i++) {
            triangle[i] = f.vertexes[i].xy() / f.vertexes[i].w + center;
        }
        DrawLine(triangle[0].x, triangle[0].y, triangle[1].x, triangle[1].y, color{255, 255, 255});
        DrawLine(triangle[1].x, triangle[1].y, triangle[2].x, triangle[2].y, color{255, 255, 255});
        DrawLine(triangle[2].x, triangle[2].y, triangle[0].x, triangle[0].y, color{255, 255, 255});
    }
}

void TriangleRasterization::DrawTriangle(float2 triangle[3]) {
    float2 begin{
            std::min(triangle[0].x, std::min(triangle[1].x, triangle[2].x)),
            std::min(triangle[0].y, std::min(triangle[1].y, triangle[2].y))
    };
    float2 end{
            std::max(triangle[0].x, std::max(triangle[1].x, triangle[2].x)),
            std::max(triangle[0].y, std::max(triangle[1].y, triangle[2].y))
    };

    auto ef = EdgeFunction(triangle[0], triangle[1], triangle[2]);

    for (int x = begin.x; x < int(ceil(end.x)); x++) {
        for (int y = begin.y; y < int(ceil(end.y)); y++) {
            auto ef01 = EdgeFunction({ static_cast<float>(x), static_cast<float>(y)}, triangle[0], triangle[1]);
            auto ef12 = EdgeFunction({static_cast<float>(x), static_cast<float>(y)}, triangle[1], triangle[2]);
            auto ef20 = EdgeFunction({ static_cast<float>(x), static_cast<float>(y)}, triangle[2], triangle[0]);

            auto w0 = std::abs(ef12 / ef);
            auto w1 = std::abs(ef20 / ef);
            auto w2 = std::abs(ef01 / ef);

            if ((ef01 >= 0 && ef12 >= 0 && ef20 >= 0) || (ef01 <= 0 && ef12 <= 0 && ef20 <= 0)) {
                SetPixel(x, y, color{
                        255, 0, 0
                });
            }
        }
    }
}

float TriangleRasterization::EdgeFunction(float2 a, float2 b, float2 c)
{
    return (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
}


