#pragma once


#include "color_space.h"



class LineDrawing: public ColorSpace
{
public:
	LineDrawing(unsigned short width, unsigned short height);
	virtual ~LineDrawing();

	void DrawLine(unsigned short x_begin, unsigned short y_begin, unsigned short x_end, unsigned short y_end, color color);

	void DrawScene();

};
