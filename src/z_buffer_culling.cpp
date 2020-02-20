#include "z_buffer_culling.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


ZCulling::ZCulling(unsigned short width, unsigned short height, std::string obj_file)
        : TriangleRasterization(width,
                                height,
                                obj_file),
          depth_buffer(static_cast<unsigned long long>(width) * static_cast<unsigned long long>(height))
{
}

ZCulling::~ZCulling() {
}

void ZCulling::Clear() {
    BlackImage::Clear();

    for (auto &z: depth_buffer)
        z = INFINITY;
}

bool ZCulling::TestDepth(unsigned short x, unsigned short y, float depth) {
    auto ind = y * width + x;

    if (ind < 0 || ind >= depth_buffer.size())
        return false;

    if (depth_buffer[ind] > depth) {
        depth_buffer[ind] = depth;

        return true;
    }
    return false;
}

std::vector<face> ZCulling::clone(std::vector<face> &what, float dx, float dy, float dz) {
    return project(what, {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {dx, dy, dz, 1}
    }, linalg::identity_t(4), linalg::identity_t(4));
}

void ZCulling::DrawScene() {
    parser->Parse();
    auto faces = parser->GetFaces();

    float2 center = {float(width) / 2, float(height) / 2};

    std::vector<std::vector<face>> to_append;

    to_append.push_back(clone(faces, -2, -2, 0));
    to_append.push_back(clone(faces, -2, 2, 0));
    to_append.push_back(clone(faces, 2, -2, 0));
    to_append.push_back(clone(faces, 2, 2, 0));


    for (auto &append: to_append)
        for (auto f: append)
            faces.push_back(f);

    float3 eye = {5, 0, 5};
    float3 at{0, 1, 0};
    float3 up{-.75, -1, 0};

    face c_plane1{
            {{-2, -2, 0, 1},
                    {2, -2, 0, 1},
                    {2, 2, 0, 1}}
    };
    faces.push_back(c_plane1);
    face c_plane2{
            {{-2, -2, 0, 1},
                    {-2, 2, 0, 1},
                    {2, 2, 0, 1}}
    };
    faces.push_back(c_plane2);


    auto proj = project(faces, getWorld(), getView(eye, at, up), getProjection());
    for (auto &f: proj) {

        float3 triangle[3];
        for (int i = 0; i < 3; i++) {
            triangle[i] = f.vertexes[i].xyz() / f.vertexes[i].w + float3{center, 0};
        }

        DrawTriangle(triangle);
    }
}

float4x4 ZCulling::getWorld() {
    return {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
}

void ZCulling::DrawTriangle(float3 triangle[3]) {
    float2 begin{
            std::min(triangle[0].x, std::min(triangle[1].x, triangle[2].x)),
            std::min(triangle[0].y, std::min(triangle[1].y, triangle[2].y))
    };
    float2 end{
            std::max(triangle[0].x, std::max(triangle[1].x, triangle[2].x)),
            std::max(triangle[0].y, std::max(triangle[1].y, triangle[2].y))
    };

    auto ef = EdgeFunction(triangle[0].xy(), triangle[1].xy(), triangle[2].xy());

    for (int x = begin.x; x < int(ceil(end.x)); x++) {
        for (int y = begin.y; y < int(ceil(end.y)); y++) {
            auto ef01 = EdgeFunction({ static_cast<float>(x), static_cast<float>(y)}, triangle[0].xy(), triangle[1].xy());
            auto ef12 = EdgeFunction({ static_cast<float>(x), static_cast<float>(y)}, triangle[1].xy(), triangle[2].xy());
            auto ef20 = EdgeFunction({ static_cast<float>(x), static_cast<float>(y)}, triangle[2].xy(), triangle[0].xy());

            auto w0 = std::abs(ef12 / ef);
            auto w1 = std::abs(ef20 / ef);
            auto w2 = std::abs(ef01 / ef);

            if ((ef01 >= 0 && ef12 >= 0 && ef20 >= 0) || (ef01 <= 0 && ef12 <= 0 && ef20 <= 0)) {

                auto z = w0 * triangle[0].z + w1 * triangle[1].z + w2 * triangle[2].z;

                if (TestDepth(x, y, z)) {
                    SetPixel(x, y, color{
                            static_cast<unsigned char>(w0 * 255),
                            static_cast<unsigned char>(w1 * 255),
                            static_cast<unsigned char>(w2 * 255),
                    });
                }
            }
        }
    }
}
