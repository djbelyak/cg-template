#include "projection.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


Projection::Projection(unsigned short width, unsigned short height, std::string obj_file) : ReadObj(width, height, obj_file)
{
}

Projection::~Projection()
{
}

void Projection::DrawScene() {
    parser->Parse();
    auto faces = parser->GetFaces();


    float3 eye = {0, 0, 2};
    float3 at{0, 0, 0};
    float3 up{0, 1, 0};

    for (auto &f: project(faces, getWorld(), getView(eye, at, up), getProjection())) {
        DrawTriangle(f);
    }
}

float4x4 Projection::getProjection() {
    float radius = static_cast<float>(std::min(width, height) / 2);
    float zf = 100;
    float zn = 1;
    float fov_coef = 1 / 0.8;

    return {
            {radius / fov_coef,      0,            0,                     0},
            {0,           radius / fov_coef,       0,                     0},
            {0,           0,            (zf + zn) / (zf - zn), zf * zn / (zn - zf)},
            {0, 0, -1,                    0}
    };
}

float4x4 Projection::getView(float3 eye, float3 at, float3 up) {
    float3 z = linalg::normalize(eye - at);
    float3 x = linalg::normalize(linalg::cross(up, z));
    float3 y = linalg::cross(z, x);

    return linalg::transpose(float4x4{
            {x, -linalg::dot(x, eye)},
            {y, -linalg::dot(y, eye)},
            {z, -linalg::dot(z, eye)},
            {0, 0, 0, 1}
    });
}

float4x4 Projection::getWorld() {
    return linalg::identity_t(4);
}

std::vector<face> Projection::project(std::vector<face> &faces, float4x4 world, float4x4 view, float4x4 projection) {
    std::vector<face> proj;

    auto transform = mul(projection, view, world);
    for (auto f: faces) {
        float4 v[3];

        for (int i = 0; i < 3; i++) {
            v[i] = mul(transform, f.vertexes[i]);
        }
        proj.emplace_back();
        std::copy_n(v, 3, proj.back().vertexes);
    }

    return proj;
}

void Projection::DrawTriangle(face f) {
    linalg::vec<unsigned short, 2> center{static_cast<uint16_t>(width/2), static_cast<uint16_t>(height/2)};


    DrawLine(center.x + f.vertexes[0].x / f.vertexes[0].w,
             center.y + f.vertexes[0].y / f.vertexes[0].w,
             center.x + f.vertexes[1].x / f.vertexes[1].w,
             center.y + f.vertexes[1].y / f.vertexes[1].w,
             color{255, 0, 0});

    DrawLine(center.x + f.vertexes[1].x / f.vertexes[1].w,
             center.y + f.vertexes[1].y / f.vertexes[1].w,
             center.x + f.vertexes[2].x / f.vertexes[2].w,
             center.y + f.vertexes[2].y / f.vertexes[2].w,
             color{0, 255, 0});

    DrawLine(center.x + f.vertexes[2].x / f.vertexes[2].w,
             center.y + f.vertexes[2].y / f.vertexes[2].w,
             center.x + f.vertexes[0].x / f.vertexes[0].w,
             center.y + f.vertexes[0].y / f.vertexes[0].w,
             color{0, 0, 255});

}
