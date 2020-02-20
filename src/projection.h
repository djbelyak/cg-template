#pragma once


#include "read_obj.h"


class Projection: public ReadObj
{
public:
	Projection(unsigned short width, unsigned short height, std::string obj_file);
	virtual ~Projection();

	void DrawScene();

protected:
    virtual float4x4 getWorld();
    virtual float4x4 getView(float3 eye, float3 at, float3 up);
    virtual float4x4 getProjection();
    virtual std::vector<face> project(std::vector<face> &faces, float4x4 world, float4x4 view, float4x4 projection);

private:
    void DrawTriangle(face f);
};
