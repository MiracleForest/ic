/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：icolor.hpp
* @创建时间：2022.9.6.20:10
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i颜色类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/file/iFilePos.h>
#include <icore/data/text/istring.h>
#include <icore/type/iVector.h>

#include <cmath>


SPACE(i)
{
    SPACE(core)
    {
        SPACE(type)
        {

            struct iRGB
            {
                ushort r = 0;
                ushort g = 0;
                ushort b = 0;

                static iRGB makeiRGB(ushort r, ushort g, ushort b)
                {
                    iRGB rgb{ r, g, b };
                    return rgb;
                }

            };//struct iRGB

            struct iHSL
            {
                float h = 0;
                float s = 0;
                float l = 0;
            };

            struct iRGBA
            {
                iRGBA(CRef<iRGB>) = delete;

                iRGBA() = default;

                iRGB rgb{};
                ushort a = 255;

                static iRGBA makeiRGBA(ushort r, ushort g, ushort b, ushort a = 255)
                {
                    iRGBA rgba;
                    rgba.rgb = { r, g, b };
                    rgba.a = a;
                    return rgba;
                }

                static iRGBA makeiRGBA(iRGB rgb, ushort a = 255)
                {
                    iRGBA rgba;
                    rgba.rgb = rgb;
                    rgba.a = a;
                    return rgba;
                }

            };//struct iRGBA

            struct iHSLA
            {
                iHSLA(CRef<iHSL>) = delete;
                iHSLA() = default;
                iHSL hsl{};
                ushort a = 255;

                static iHSLA makeiHSLA(float h, float s, float l, ushort a = 255)
                {
                    iHSLA hsla;
                    hsla.hsl = { h,s,l };
                    hsla.a = a;
                    return hsla;
                }
                static iHSLA makeiHSLA(iHSL hsl, ushort a = 255)
                {
                    iHSLA hsla;
                    hsla.hsl = hsl;
                    hsla.a = a;
                    return hsla;
                }

            };// struct iHSLA

            class IAPI iColor
                :public i::core::basic::iBasic<iColor>
            {
                using istring = data::text::istring;
                iObject(iColor)
            public:

                enum Colors
                    : ulong
                {
                    black = 0x000000,//0,0,0
                    white = 0xFFFFFF,//255,255,255
                    blue = 0x0000FF,//0,0,255
                    green = 0x00FF00,//0,0,255
                    red = 0xFF0000,//255,0,0
                    yellow = 0xFFFF00,//255,255,0

                    aliceBlue = 0xF0F8FF,
                    antiqueWhite = 0xFAEBD7,
                    aqua = 0x00FFFF,
                    aquamarine = 0x7FFFD4,
                    azure = 0xF0FFFF,
                    aeige = 0xF5F5DC,
                    aisque = 0xFFE4C4,
                    blanchedAlmond = 0xFFEBCD,
                    blueViolet = 0x8A2BE2,
                    brown = 0xA52A2A,
                    burlyWood = 0xDEB887,
                    cadetBlue = 0x5F9EA0,
                    chartreuse = 0x7FFF00,
                    chocolate = 0xD2691E,
                    coral = 0xFF7F50,
                    cornflowerBlue = 0x6495ED,
                    cornsilk = 0xFFF8DC,
                    crimson = 0xDC143C,
                    cyan = 0x00FFFF,
                    darkBlue = 0x00008B,
                    darkCyan = 0x008B8B,
                    darkGoldenRod = 0xB8860B,
                    darkGray = 0xA9A9A9,
                    darkGreen = 0x006400,
                    darkKhaki = 0xBDB76B,
                    darkMagenta = 0x8B008B,
                    darkOliveGreen = 0x556B2F,
                    darkOrange = 0xFF8C00,
                    darkOrchid = 0x9932CC,
                    darkRed = 0x8B0000,
                    darkSalmon = 0xE9967A,
                    darkSeaGreen = 0x8FBC8F,
                    darkSlateBlue = 0x483D8B,
                    darkSlateGray = 0x2F4F4F,
                    darkTurquoise = 0x00CED1,
                    darkViolet = 0x9400D3,
                    deepPink = 0xFF1493,
                    deepSkyBlue = 0x00BFFF,
                    dimGray = 0x696969,
                    dodgerBlue = 0x1E90FF,
                    fireBrick = 0xB22222,
                    floralWhite = 0xFFFAF0,
                    forestGreen = 0x228B22,
                    fuchsia = 0xFF00FF,
                    gainsboro = 0xDCDCDC,
                    ghostWhite = 0xF8F8FF,
                    gold = 0xFFD700,
                    goldenRod = 0xDAA520,
                    gray = 0x808080,
                    greenYellow = 0xADFF2F,
                    honeyDew = 0xF0FFF0,
                    hotPink = 0xFF69B4,
                    indianRed = 0xCD5C5C,
                    indigo = 0x4B0082,
                    ivory = 0xFFFFF0,
                    khaki = 0xF0E68C,
                    lavender = 0xE6E6FA,
                    lavenderBlush = 0xFFF0F5,
                    lawnGreen = 0x7CFC00,
                    lemonChiffon = 0xFFFACD,
                    lightBlue = 0xADD8E6,
                    lightCoral = 0xF08080,
                    lightCyan = 0xE0FFFF,
                    lightGoldenRodYellow = 0xFAFAD2,
                    lightGray = 0xD3D3D3,
                    lightGreen = 0x90EE90,
                    lightPink = 0xFFB6C1,
                    lightSalmon = 0xFFA07A,
                    lightSeaGreen = 0x20B2AA,
                    lightSkyBlue = 0x87CEFA,
                    lightSlateGray = 0x778899,
                    lightSteelBlue = 0xB0C4DE,
                    lightYellow = 0xFFFFE0,
                    lime = 0x00FF00,
                    limeGreen = 0x32CD32,
                    linen = 0xFAF0E6,
                    magenta = 0xFF00FF,
                    maroon = 0x800000,
                    mediumAquaMarine = 0x66CDAA,
                    mediumBlue = 0x0000CD,
                    mediumOrchid = 0xBA55D3,
                    mediumPurple = 0x9370DB,
                    mediumSeaGreen = 0x3CB371,
                    mediumSlateBlue = 0x7B68EE,
                    mediumSpringGreen = 0x00FA9A,
                    mediumTurquoise = 0x48D1CC,
                    mediumVioletRed = 0xC71585,
                    midnightBlue = 0x191970,
                    mintCream = 0xF5FFFA,
                    mistyRose = 0xFFE4E1,
                    moccasin = 0xFFE4B5,
                    navajoWhite = 0xFFDEAD,
                    navy = 0x000080,
                    oldLace = 0xFDF5E6,
                    olive = 0x808000,
                    oliveDrab = 0x6B8E23,
                    orange = 0xFFA500,
                    orangeRed = 0xFF4500,
                    orchid = 0xDA70D6,
                    paleGoldenRod = 0xEEE8AA,
                    paleGreen = 0x98FB98,
                    paleTurquoise = 0xAFEEEE,
                    paleVioletRed = 0xDB7093,
                    papayaWhip = 0xFFEFD5,
                    peachPuff = 0xFFDAB9,
                    peru = 0xCD853F,
                    pink = 0xFFC0CB,
                    plum = 0xDDA0DD,
                    powderBlue = 0xB0E0E6,
                    purple = 0x800080,
                    rosyBrown = 0xBC8F8F,
                    royalBlue = 0x4169E1,
                    raddleBrown = 0x8B4513,
                    salmon = 0xFA8072,
                    sandyBrown = 0xF4A460,
                    seaGreen = 0x2E8B57,
                    seaShell = 0xFFF5EE,
                    sienna = 0xA0522D,
                    silver = 0xC0C0C0,
                    skyBlue = 0x87CEEB,
                    slateBlue = 0x6A5ACD,
                    slateGray = 0x708090,
                    snow = 0xFFFAFA,
                    springGreen = 0x00FF7F,
                    steelBlue = 0x4682B4,
                    tan = 0xD2B48C,
                    teal = 0x008080,
                    thistle = 0xD8BFD8,
                    tomato = 0xFF6347,
                    turquoise = 0x40E0D0,
                    violet = 0xEE82EE,
                    wheat = 0xF5DEB3,
                    whiteSmoke = 0xF5F5F5,
                    yellowGreen = 0x9ACD32
                };// enum Colors

                enum class ConsoleTargetType
                    : int
                {
                    text,
                    background
                };//enum class ConsoleTargetType

            public:

                iColor();

                iColor(iRGB rgb);

                iColor(iRGBA rgba);

                iColor(ushort r, ushort g, ushort b);

                iColor(ulong hex);

                iColor(Colors Color);

                ~iColor();

            public:

                ulong toHex()const;

                /**
                 * @brief 将 RGB 颜色分量转换为易语言的颜色值
                 * @param r R 颜色分量
                 * @param g G 颜色分量
                 * @param b B 颜色分量
                 * @return 转换后的颜色值
                 */
                constexpr std::uint32_t makeColor(std::uint8_t r, std::uint8_t g, std::uint8_t b);

            public:

                iRGB data()const;

                void setData(iRGB rgb);

                void reset();

                iRGBA getiRGBA()const;

                iRGB getiRGB()const;

                void setiRGB(iRGB rgb);

                ushort getR()const;

                void setR(ushort r);

                ushort getG()const;

                void setG(ushort g);

                ushort getB()const;

                void setB(ushort b);

            public:

                static ulong toHex(iRGBA rgba);

                static ulong toHex(ushort _r, ushort _g, ushort _b, ushort _a);

                static ulong toHex(ushort _r, ushort _g, ushort _b);

                static ulong toHex(iRGB rgb);

                static std::wstring getConsoleColoriString(CRef<iColor> _color);

                static double sRGBFromLinear(double l);

                static double linearFromSRGB(double s);

                static double yfromRGB(double r, double g, double b);

            public:
                static iHSL iRGB2iSHL(iRGB rgb);

                static iHSLA iRGBA2iHSLA(iRGBA rgba);

            protected:
            private:
                iRGB _rgb;
            };//class iColor 


        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)
