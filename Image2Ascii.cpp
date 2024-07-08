#include "Image2Ascii.h"
#include <iostream>

Image2Ascii::Image2Ascii(int width, int height, std::vector<unsigned char>& image)
{
    this->width = width;
    this->height = height;
    this->image = image;
    this->asciiImage = "";
    this->convertPicture();
}
Image2Ascii::~Image2Ascii() {}

std::string Image2Ascii::getAsciiImage()
{
    return this->asciiImage;
}

int Image2Ascii::getPixelBrightness(int r, int g, int b)
{
    return (r + g + b)/3;
}

float Image2Ascii::mapToCharactersLength(int value, int min, int max, int minMapTo, int maxMapTo)
{
    int interval    = max - min;
    int toInterval  = maxMapTo - minMapTo;
    float steps     = (float) toInterval / interval;
    return value * steps;
}

void Image2Ascii::convertPicture()
{
    const size_t RGBA = 4;
    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            int pixelIndex = RGBA * (y * this->width + x);
            int r = static_cast<int>(this->image[pixelIndex + 0]);
            int g = static_cast<int>(this->image[pixelIndex + 1]);
            int b = static_cast<int>(this->image[pixelIndex + 2]);
            int brightness  = this->getPixelBrightness(r, g, b);
            int mapped      = this->mapToCharactersLength(brightness, 0, 255, 0, this->characters.length());
            this->asciiImage += this->characters[mapped];
            this->asciiImage += " ";
        }
        this->asciiImage += '\n';
    }
}