/**
 * Inspiration taken from Daniel Shiffmans "The Coding Train"
 * https://www.youtube.com/watch?v=55iwMYv8tGI&ab_channel=TheCodingTrain
 * 
 * Utilizing StbImage library to read the pixels of an image.
 */

#include <iostream>
#include <vector>
#include <filesystem>
#include <regex>
#include "Image2Ascii.h"

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "StbImage.h"
}

namespace fs = std::filesystem;

bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int&y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

int main()
{
    std::string filepath = "./img/";
    for (const auto & entry : fs::directory_iterator(filepath))
    {
        std::regex jpg_regex(".*\.jpg$");
        std::smatch match;
        std::string path(entry.path());
        if(std::regex_match(path, match, jpg_regex))
        {
            int width, height;
            std::vector<unsigned char> image;
            bool success = load_image(image, entry.path(), width, height);
            if (!success)
            {
                std::cout << "Error loading image" << std::endl;
                return 1;
            }

            if (width > 100 ||  height > 100) {
                std::cout << "Image too big (" << std::to_string(width) << "x" << std::to_string(height) << ") - continues with next image" << std::endl;
                continue;
            }

            Image2Ascii *i2a = new Image2Ascii(width, height, image);
            std::cout << i2a->getAsciiImage() << std::endl;
            delete i2a;
        }
    }
    return 0;
}