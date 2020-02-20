#pragma once


#include "triangle_rasterization.h"


class ZCulling: public TriangleRasterization
{
public:
	ZCulling(unsigned short width, unsigned short height, std::string obj_file);
	virtual ~ZCulling();

	void DrawScene();
	void Clear();

protected:
	void DrawTriangle(float3 triangle[3]);
	bool TestDepth(unsigned short x, unsigned short y, float depth);
	std::vector<float> depth_buffer;

	float4x4 getWorld() override;

private:
    std::vector<face> clone(std::vector<face> &what, float dx, float dy, float dz);
};
