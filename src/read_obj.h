#pragma once


#include "draw_line.h"


class ObjParser
{
public:
	ObjParser(std::string filename);
	virtual ~ObjParser();

	int Parse();

	const std::vector<face>& GetFaces();

protected:
	std::string filename;

	std::vector<float4> vertexes;
	std::vector<face> faces;

	std::vector<std::string> Split(const std::string& s, char delimiter);
};


class ReadObj: public LineDrawing
{
public:
	ReadObj(unsigned short width, unsigned short height, std::string obj_file);
	virtual ~ReadObj();

	void DrawScene();

protected:
	ObjParser* parser;

    void DrawTriangle(face const &f, color c);
};
