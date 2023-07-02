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

            class IAPI iColor
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

            protected:
            private:
                iRGB _rgb;
            };//class iColor 


        }//SPACE(type)
    }//SPACE(core)
}//SPACE(i)

