#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../../../Libs/Libs.hpp"
#include "../Debug/Debug.hpp"

namespace alce
{
    class Color
    {
    public:

        Color()
        {
            color = sf::Color::White;
        }

        Color(sf::Color sfColor)
        {
            color = sfColor;
        }

        Color(int red, int green, int blue)
        {
            color = sf::Color(red, green, blue);
        }

        Color(int red, int green, int blue, int alpha)
        {
            color = sf::Color(red, green, blue, alpha);
        }

        Color(unsigned int hexValue)
        {
            color.r = (hexValue >> 16) & 0xFF;
            color.g = (hexValue >> 8) & 0xFF;
            color.b = hexValue & 0xFF;
            color.a = 255;
        }

        Color(String str)
        {
            FromString(str);
        }

        Color(const char* cstr)
        {
            String str(cstr);
            FromString(str);
        }

        void FromString(String str)
        {
            str.Trim();
            std::string strAnsi = str.ToAnsiString();

            if (strAnsi[0] == '#') 
            {
                std::string hex = "0x" + strAnsi.substr(1);

                unsigned int hexValue;
                std::istringstream(hex) >> std::hex >> hexValue;

                if(!SetHex(hexValue))
                {
                    Debug.Warning("Unable to parse Hex {}", {str});
                }
            } 
            else 
            {
                int red, green, blue, alpha;
                
                auto values = str.Split(",");

                if(values.Length() < 3) 
                {
                    Debug.Warning("Unable to parse RGB \"{}\" due to missing channels", {str});
                    return;
                }

                red = values[0].ParseInt();
                green = values[1].ParseInt();
                blue = values[2].ParseInt();
                alpha = values.Length() == 4 ? values[3].ParseInt() : 255;

                SetRGBA(red, green, blue, alpha);
            }
        }

        void SetRGB(int red, int green, int blue)
        {
            color.r = red;
            color.g = green;
            color.b = blue;
        }

        void SetRGBA(int red, int green, int blue, int alpha)
        {
            color.r = red;
            color.g = green;
            color.b = blue;
            color.a = alpha;
        }

        bool SetHex(unsigned int hexValue)
        {
            try
            {
                color.r = (hexValue >> 16) & 0xFF;
                color.g = (hexValue >> 8) & 0xFF;
                color.b = hexValue & 0xFF;
            }
            catch(const std::exception& e)
            {
                Debug.Warning("{}", {e.what()});
                return false;
            }

            return true;
        }

        void SetAlpha(int alpha)
        {
            color.a = alpha;
        }

        int GetRed()
        {
            return color.r;
        }

        int GetGreen()
        {
            return color.g;
        }

        int GetBlue()
        {
            return color.b;
        }

        int GetAlpha()
        {
            return color.a;
        }

        Color Blend(Color color)
        {
            int blendedRed = (GetRed() + color.GetRed()) / 2;
            int blendedGreen = (GetGreen() + color.GetGreen()) / 2;
            int blendedBlue = (GetBlue() + color.GetBlue()) / 2;
            int blendedAlpha = (GetAlpha() + color.GetAlpha()) / 2;

            return Color(blendedRed, blendedGreen, blendedBlue, blendedAlpha);
        }

        sf::Color ToSFMLColor() 
        {
            return color;
        }

        String ToString()
        {
            std::stringstream ss;
            ss << "#" << std::hex << std::uppercase << (static_cast<unsigned>(color.r) << 16 | static_cast<unsigned>(color.g) << 8 | static_cast<unsigned>(color.b));
            return String(ss.str());
        }

        sf::Color operator~()
        {
            return color;
        }

        void operator=(sf::Color sfColor)
        {
            color = sfColor;
        }

        void operator=(String str)
        {
            FromString(str);
        }

        void operator=(const char* cstr)
        {
            String str(cstr);
            FromString(cstr);
        }

    private:

        sf::Color color = sf::Color::White;
    };

    namespace Colors
    {
        const Color Red = Color(255, 0, 0);
        const Color Green = Color(0, 255, 0);
        const Color Blue = Color(0, 0, 255);
        const Color White = Color(255, 255, 255);
        const Color Black = Color(0, 0, 0);
        const Color Yellow = Color(255, 255, 0);
        const Color Cyan = Color(0, 255, 255);
        const Color Magenta = Color(255, 0, 255);
        const Color Orange = Color(255, 165, 0);
        const Color Purple = Color(128, 0, 128);
        const Color Pink = Color(255, 192, 203);
        const Color Transparent = Color(0, 0, 0, 0);

    };
}