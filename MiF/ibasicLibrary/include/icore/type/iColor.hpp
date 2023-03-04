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
#include <icore/file/iFilePos.hpp>
#include <icore/data/text/istring.hpp>
#include <icore/type/iVector.hpp>

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

                static inline iRGB makeiRGB(ushort r, ushort g, ushort b)
                {
                    iRGB rgb{ r, g, b };
                    return rgb;
                }

            };//struct iRGB

            struct iRGBA
            {
                iRGBA(CRef<iRGB>) = delete;

                iRGBA() = default;

                iRGB rgb = {};
                ushort a = 255;

                static inline iRGBA makeiRGBA(ushort r, ushort g, ushort b, ushort a = 255)
                {
                    iRGBA rgba{};
                    rgba.rgb = { r, g, b };
                    rgba.a = a;
                    return rgba;
                }

            };//struct iRGBA

            class iColor
                :public i::core::basic::iBasic<iColor>
            {
                using istring = data::text::istring;
                iObject(iColor);
            public:

                enum Colors
                    : ulong
                {
                    black = 0x000000,//0,0,0
                    white = 0xFFFFFF,//255,255,255
                    blue = 0x0000FF,//0,0,255
                    green = 0x00FF00,//0,0,255
                    red = 0xFF0000,//255,0,0
                    yellow = 0xFFFF00//255,255,0
                };// enum Colors

                enum class ConsoleTargetType
                    : int
                {
                    text,
                    background
                };//enum class ConsoleTargetType

            public:

                iColor() :_rgb({})
                { }

                iColor(iRGB rgb) :_rgb(rgb)
                { }

                iColor(iRGBA rgba) :_rgb(rgba.rgb)
                { }

                iColor(ushort r, ushort g, ushort b) :_rgb({ r, g, b })
                { }

                iColor(ulong hex)
                    :_rgb(iRGB::makeiRGB(((hex >> 16) & 0xFF), ((hex >> 8) & 0xFF), (hex & 0xFF)))
                { }

                iColor(Colors Color)
                    : _rgb(iRGB::makeiRGB(((Color >> 16) & 0xFF), ((Color >> 8) & 0xFF), (Color & 0xFF)))
                { }

                ~iColor()
                { }

            public:

                ulong toHex()const
                {
                    return
                        ((_rgb.r & 0xff) << 16) +
                        ((_rgb.g & 0xff) << 8) +
                        (_rgb.b & 0xff);
                }

                /**
                 * @brief 将 RGB 颜色分量转换为易语言的颜色值
                 * @param r R 颜色分量
                 * @param g G 颜色分量
                 * @param b B 颜色分量
                 * @return 转换后的颜色值
                 */
                constexpr std::uint32_t makeColor(std::uint8_t r, std::uint8_t g, std::uint8_t b)
                {
                    return r + (g << 8) + (b << 16);
                }

            public:

                iRGB data()const
                {
                    return _rgb;
                }

                void setData(iRGB rgb)
                {
                    _rgb = rgb;
                }

                void reset()
                {
                    _rgb = {};
                }

                iRGBA getiRGBA()const
                {
                    return iRGBA::makeiRGBA(_rgb.r, _rgb.g, _rgb.b);
                }

                iRGB getiRGB()const
                {
                    return _rgb;
                }

                void setiRGB(iRGB rgb)
                {
                    _rgb = rgb;
                }

                ushort getR()const
                {
                    return _rgb.r;
                }

                void setR(ushort r)
                {
                    _rgb.r = r;
                }

                ushort getG()const
                {
                    return _rgb.g;
                }

                void setG(ushort g)
                {
                    _rgb.g = g;
                }

                ushort getB()const
                {
                    return _rgb.b;
                }

                void setB(ushort b)
                {
                    _rgb.b = b;
                }

            public:

                static ulong toHex(iRGBA rgba)
                {
                    return ((rgba.rgb.r & 0xff) << 24) +
                        ((rgba.rgb.g & 0xff) << 16) +
                        ((rgba.rgb.b & 0xff) << 8)
                        + (rgba.a & 0xff);
                }

                static ulong toHex(ushort _r, ushort _g, ushort _b, ushort _a)
                {
                    return ((_r & 0xff) << 24) +
                        ((_g & 0xff) << 16) +
                        ((_b & 0xff) << 8)
                        + (_a & 0xff);
                }

                static ulong toHex(ushort _r, ushort _g, ushort _b)
                {
                    return ((_r & 0xff) << 16) +
                        ((_g & 0xff) << 8) +
                        (_b & 0xff);
                }

                static ulong toHex(iRGB rgb)
                {
                    return ((rgb.r & 0xff) << 16) +
                        ((rgb.g & 0xff) << 8) +
                        (rgb.b & 0xff);
                }

                static istring getConsoleColoriString(CRef<iColor> _color)
                {
                    auto c = _color.getiRGB();
                    return istring("\033[38;2;" +
                        std::to_string(c.r) +
                        ";" +
                        std::to_string(c.g) +
                        ";" +
                        std::to_string(c.b) +
                        "m");
                }

                static double sRGBFromLinear(double l)
                {
                    if (l <= 0.0031308)
                        l *= 12.92;

                    else
                        l = 1.055 * pow(l, 1 / 2.4) - 0.055;

                    return l;
                }

                static double linearFromSRGB(double s)
                {
                    if (s <= 0.04045)
                        return s / 12.92;

                    else
                        return pow((s + 0.055) / 1.055, 2.4);
                }

                static double yfromRGB(double r, double g, double b)
                {
                    return 0.2126 * r + 0.7152 * g + 0.0722 * b;
                }


            public:

            public:

                class Gradient
                {

                };//class Gradient

            protected:
            private:
                iRGB _rgb;
            };//class iColor 


        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)

