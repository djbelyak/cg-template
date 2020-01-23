#include "black_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


BlackImage::BlackImage(unsigned short width, unsigned short height):
    width(width),
    height(height)
{
    frame_buffer.reserve(width * height);
}

BlackImage::~BlackImage()
{
    frame_buffer.clear();
}

void BlackImage::Clear()
{
    frame_buffer.resize(width * height);
}

int BlackImage::Save(std::string filename) const
{
    int result = stbi_write_png(filename.c_str(), width, height, 3, frame_buffer.data(), width * sizeof(color));

    return (result - 1); //STD returns 1 if everything is ok, convering to OS return code
}

std::vector<color> BlackImage::GetFrameBuffer() const
{
    return frame_buffer;
}
