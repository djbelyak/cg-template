#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "structs.h"

bool validate_framebuffer(std::string reference_file, std::vector<color> frame_buffer)
{
    // Load a reference image
    int width, height, channels;
    unsigned char* img = stbi_load(reference_file.c_str(), &width, &height, &channels, 0);

    if (!img)
        return false;

    // Convert the reference to vector of colors
    std::vector<color> reference;
    for (int i = 0; i < width * height; i++)
    {
        color pixel;
        pixel.r = img[channels * i];
        pixel.g = img[channels * i + 1];
        pixel.b = img[channels * i + 2];
        reference.push_back(pixel);
    }

    // Compare with a frame buffer
    bool result = (reference.size() == frame_buffer.size());
    for (unsigned int i = 0; i < 1920 * 1080; i++)
    {
        result &= (reference[i] == frame_buffer[i]);
    }

    return result;

}