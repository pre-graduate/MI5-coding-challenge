
#include "../lib/FreeImage.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(const string& string, char seperator)
{
    vector<std::string> output;
    auto prev = 0, pos = 0;

    while ((pos = string.find(seperator, pos)) != string::npos)
    {
        output.push_back(string.substr(prev, pos - prev));
        prev = ++pos;
    }

    output.push_back(string.substr(prev, pos - prev));
    return output;
}

string decipher(FIBITMAP* bitmap)
{
    RGBQUAD colour, pixel;
    FreeImage_FlipVertical(bitmap);
    FreeImage_GetPixelColor(bitmap, 0, 0, &colour);

    auto height = FreeImage_GetHeight(bitmap);
    auto width = FreeImage_GetWidth(bitmap);
    auto occurances = 0;

    stringstream hex, text;
    for (auto y = 0; y < height; ++y)
    {
        for (auto x = 0; x < width; ++x)
        {
            FreeImage_GetPixelColor(bitmap, x, y, &pixel);

            if (memcmp(&pixel, &colour, sizeof(RGBQUAD)) == 0)
            {
                ++occurances;
            }
            else
            {
                FreeImage_GetPixelColor(bitmap, x, y, &colour);
                hex << static_cast<char>(occurances);
                occurances = 1;
            }
        }
    }

    for (auto& value : split(hex.str(), '-'))
    {
        if (value.length() == 2)
        {
            auto ascii = 0;
            istringstream iss(value);
            iss >> std::hex >> ascii;
            text << static_cast<char>(ascii);
        }
    }

    return text.str();
}

int main(int argc, char* argv[])
{
    FreeImage_Initialise();

    const auto image = FreeImage_Load(FIF_PNG, "../img/puzzle.png");
    const auto text = decipher(image);

    cout << text << endl;
    cin.get();

    FreeImage_Unload(image);
    FreeImage_DeInitialise();
}
