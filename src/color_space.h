#pragma once

#include "black_image.h"


class ColorSpace : public BlackImage
{
public:
	ColorSpace(unsigned short width, unsigned short height);
	virtual ~ColorSpace();

	void DrawScene();

protected:
	void SetPixel(unsigned short x, unsigned short y, color color);
};
