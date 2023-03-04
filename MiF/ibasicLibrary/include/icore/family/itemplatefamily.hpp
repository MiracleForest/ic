
/****
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：itemplatefamily.h
 * @创建时间：2023.1.3.11:56
 * @创建者：Lovelylavender4
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/
#pragma once
#include <icore/family/imacrofamily.h>

SPACE(i)
{
    SPACE(core)
    {

        template<class T>
        short __PAIR__(char  high, T low)
        {
            return (((short)high) << sizeof(high) * 8) | uint8_t(low);
        }

        template<class T>
        int __PAIR__(short high, T low)
        {
            return (((int)high) << sizeof(high) * 8) | uint16_t(low);
        }

        template<class T>
        int64 __PAIR__(int high, T low)
        {
            return (((int64)high) << sizeof(high) * 8) | uint32_t(low);
        }

        template<class T>
        uint16_t __PAIR__(uint8_t  high, T low)
        {
            return (((uint16_t)high) << sizeof(high) * 8) | uint8_t(low);
        }

        template<class T>
        uint32_t __PAIR__(uint16_t high, T low)
        {
            return (((uint32_t)high) << sizeof(high) * 8) | uint16_t(low);
        }

        template<class T>
        uint64 __PAIR__(uint32_t high, T low)
        {
            return (((uint64)high) << sizeof(high) * 8) | uint32_t(low);
        }

        template<class T>
        T __ROL__(T value, uint count)
        {
            const uint nbits = sizeof(T) * 8;
            count %= nbits;

            T high = value >> (nbits - count);
            value <<= count;
            value |= high;
            return value;
        }

        template<class T>
        T __ROR__(T value, uint count)
        {
            const uint nbits = sizeof(T) * 8;
            count %= nbits;

            T low = value << (nbits - count);
            value >>= count;
            value |= low;
            return value;
        }

        template<class T>
        char __MKCSHL__(T value, uint count)
        {
            const uint nbits = sizeof(T) * 8;
            count %= nbits;

            return (value >> (nbits - count)) & 1;
        }

        template<class T>
        char __MKCSHR__(T value, uint count)
        {
            return (value >> (count - 1)) & 1;
        }

        template<class T>
        char __SETS__(T x)
        {
            if (sizeof(T) == 1)
                return int8_t(x) < 0;
            if (sizeof(T) == 2)
                return int16_t(x) < 0;
            if (sizeof(T) == 4)
                return int32_t(x) < 0;
            return int64(x) < 0;
        }

        template<class T, class U>
        char __OFSUB__(T x, U y)
        {
            if (sizeof(T) < sizeof(U))
            {
                U x2 = x;
                int8_t sx = __SETS__(x2);
                return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
            }
            else
            {
                T y2 = y;
                int8_t sx = __SETS__(x);
                return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
            }
        }

        template<class T, class U>
        char __OFADD__(T x, U y)
        {
            if (sizeof(T) < sizeof(U))
            {
                U x2 = x;
                int8_t sx = __SETS__(x2);
                return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
            }
            else
            {
                T y2 = y;
                int8_t sx = __SETS__(x);
                return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
            }
        }

        template<class T, class U>
        char __CFSUB__(T x, U y)
        {
            int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
            if (size == 1)
                return uint8_t(x) < uint8_t(y);
            if (size == 2)
                return uint16_t(x) < uint16_t(y);
            if (size == 4)
                return uint32_t(x) < uint32_t(y);
            return uint64(x) < uint64(y);
        }

        template<class T, class U>
        char __CFADD__(T x, U y)
        {
            int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
            if (size == 1)
                return uint8_t(x) > uint8_t(x + y);
            if (size == 2)
                return uint16_t(x) > uint16_t(x + y);
            if (size == 4)
                return uint32_t(x) > uint32_t(x + y);
            return uint64(x) > uint64(x + y);
        }

    }//SPACE(core)
}//SPACE(i)
