#include <vector>
#include <string>

class Image2Ascii
{
    private:
        std::vector<unsigned char> image;
        int width;
        int height;

        std::string asciiImage;
        const std::string characters = "@#&?!=*+-_,.        ";

        int getPixelBrightness(int r, int g, int b);
        float mapToCharactersLength(int value, int min, int max, int minMapTo, int maxMapTo);
        void convertPicture();
        void loadCharacters();

    public:
        Image2Ascii(int width, int height, std::vector<unsigned char>& image);
        ~Image2Ascii();

        std::string getAsciiImage();
};