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

}

void TriangleRasterization::DrawTriangle(float4 triangle[3])
{
	
}

float TriangleRasterization::EdgeFunction(float2 a, float2 b, float2 c)
{
}


