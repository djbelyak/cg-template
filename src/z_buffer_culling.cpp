#include "z_buffer_culling.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


ZCulling::ZCulling(unsigned short width, unsigned short height, std::string obj_file) : TriangleRasterization(width, height, obj_file)
{
}

ZCulling::~ZCulling()
{
}

void ZCulling::DrawScene()
{

}

void ZCulling::Clear()
{

}

void ZCulling::DrawTriangle(float4 triangle[3])
{



}

void ZCulling::SetDepth(unsigned short x, unsigned short y, float depth)
{
}

