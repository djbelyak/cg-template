#pragma once

#include <string>
#include <vector>

#include "structs.h"


class BlackImage
{
public:
    BlackImage(unsigned short width, unsigned short height);
    virtual ~BlackImage();

    void Clear();
    int Save(std::string filename) const;

    std::vector<color> GetFrameBuffer() const; 
protected:
    unsigned short height;
    unsigned short width;

    std::vector<color> frame_buffer;
};
