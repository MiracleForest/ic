/****
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：iBigInteger.hpp
 * @创建时间：2023.1.11.15:47
 * @创建者：Minsecrus
 * -----------------------------------------------------------------------------
 * iBasicLibrary 高精度整数
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/

// ReSharper disable CppClangTidyClangDiagnosticSignCompare
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>
#include <icore/data/text/istring.hpp>

#include <deque>
#include <algorithm>

#include "iComplex.hpp"

SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            class iBigInteger
                : public basic::iBasicDataType<iBigInteger, data::text::istring>
            {
                using istring = data::text::istring;
                iObject(iBigInteger)

            public:
                static iBigInteger from(CRef<istring> str)
                {
                    return iBigInteger({str});
                }

                static bool intPredicate(const char c)
                {
                    if (c > '9' || c < '0')
                    {
                        return true;
                    }
                    return false;
                }

            public:
                iBigInteger()
                    :
                    _flag(true)
                {
                    _num.push_back(0);
                }

                iBigInteger(int n)
                    :
                    _flag(true)
                {
                    _num.push_back(n);
                }

                iBigInteger(istring str)
                {
                    if (str.charAt(0) == '-')
                        _flag = false;
                    else
                        _flag = true;

                    str.erase(std::ranges::remove_if(str, intPredicate).begin(), str.end());

                    const ullong length = str.length();
                    int index = 0;
                    ullong num = 0;
                    int power = 0;
                    for (int i = 0; i * 1ULL < length % 19; i++)
                    {
                        num *= 10;
                        num += str.charAt(i) - '0';
                        index++;
                    }
                    _num.push_back(num);

                    for (int i = index; i < length; i++)
                    {
                        if (power == 0)
                            num = 0;

                        num *= 10;
                        num += str.charAt(i) - '0';
                        index++;
                        power++;
                        if (power == 19)
                        {
                            power = 0;
                            _num.push_back(num);
                        }
                    }
                }

            public:
                static istring toBinaryString(uint num)
                {
                    istring str;
                    for (int i = 31; i >= 0; i--)
                    {
                        str.append((num >> i) & 0x00000001 ? '1' : '0');
                    }
                    return str;
                }

            public:
                [[nodiscard]] virtual istring data() const
                {
                    istring str;
                    if (this->_flag == false)
                    {
                        str.append('-');
                    }
                    for (auto i = _num.cbegin(); i != _num.cend(); ++i)
                    {
                        if (*i != 0)
                        {
                            str.append(*i);
                        }
                    }
                    if (this->_flag == false && str.length() == 1 || this->_flag && str.length() == 0)
                    {
                        str.append('0');
                    }
                    return str;
                }

            public:
                iBigInteger absoluteValue() const
                {
                    if (this->_flag)
                        return *this;
                    return !(*this);
                }

                friend iBigInteger operator!(iBigInteger bi)
                {
                    bi._flag = !bi._flag;
                    return bi;
                }

                iBigInteger operator+(CRef<iBigInteger> bi)
                {
                    const bool flag1 = this->_flag;
                    const bool flag2 = bi._flag;
                    if (flag1 != flag2)
                    {
                        return *this - !bi;
                    }

                    std::string stdStr1 = istring::toStdString(this->data());
                    std::ranges::reverse(stdStr1);
                    istring str1 = stdStr1;

                    std::string stdStr2 = istring::toStdString(bi.data());
                    std::ranges::reverse(stdStr2);
                    istring str2 = stdStr2;

                    str2.erase(std::ranges::remove_if(str2, intPredicate).begin(), str2.end());
                    str1.erase(std::ranges::remove_if(str1, intPredicate).begin(), str1.end());

                    const ullong len1 = str1.length();
                    const ullong len2 = str2.length();

                    istring str3;

                    bool carrying = false;
                    for (ullong i = 0; i < (len1 > len2 ? len1 : len2); i++)
                    {
                        const ullong upper = (i < len1) ? (str1.charAt(i) - '0') : 0;
                        const ullong downer = (i < len2) ? (str2.charAt(i) - '0') : 0;
                        ullong num = upper + downer + (carrying ? 1 : 0);
                        carrying = false;
                        if (num > 9)
                        {
                            num -= 10;
                            carrying = true;
                        }
                        str3.append(num);
                    }
                    if (carrying == true)
                    {
                        str3.append(1);
                    }
                    if (flag1 == false)
                    {
                        str3.append('-');
                    }

                    if (len1 == len2 && len1 == 0)
                    {
                        str3.append(0);
                    }

                    std::ranges::reverse(str3);
                    return iBigInteger({str3});
                }

                iBigInteger operator-(CRef<iBigInteger> bi)
                {
                    const bool flag1 = this->_flag;
                    const bool flag2 = bi._flag;
                    if (flag1 != flag2)
                    {
                        return *this + !bi;
                    }

                    std::string stdStr1 = istring::toStdString(this->data());
                    std::ranges::reverse(stdStr1);
                    istring str1 = stdStr1;

                    std::string stdStr2 = istring::toStdString(bi.data());
                    std::ranges::reverse(stdStr2);
                    istring str2 = stdStr2;

                    istring str3;
                    str2.erase(std::ranges::remove_if(str2, intPredicate).begin(), str2.end());
                    str1.erase(std::ranges::remove_if(str1, intPredicate).begin(), str1.end());

                    const ullong len1 = str1.length();
                    const ullong len2 = str2.length();

                    bool carrying = false;
                    for (ullong i = 0; i < (len1 > len2 ? len1 : len2); i++)
                    {
                        const ullong upper = (i < len1) ? (str1.charAt(i) - '0') : 0;
                        const ullong downer = (i < len2) ? (str2.charAt(i) - '0') : 0;

                        llong num = static_cast<llong>(upper) - downer - (carrying ? 1 : 0);
                        carrying = false;
                        if (num < 0)
                        {
                            num += 10;
                            carrying = true;
                        }
                        str3.append(num);
                    }
                    if (carrying)
                    {
                        istring str4 = str3;
                        const ullong len = str4.length();
                        str3.clear();
                        for (ullong i = 0; i < (len1 > len2 ? len1 : len2); i++)
                        {
                            if (i == 0)
                                str3.append(10 - (i < len ? str4.charAt(i) - '0' : 0));
                            else
                                str3.append(9 - (i < len ? str4.charAt(i) - '0' : 0));
                        }
                    }
                    if (!flag1 ^ carrying)
                    {
                        str3.append('-');
                    }
                    std::ranges::reverse(str3);
                    if (str3.length() == 0)
                        str3.append('0');

                    return iBigInteger({str3});
                }

                iBigInteger operator*(CRef<iBigInteger> bi) const
                {
                    bool flag = !this->_flag ^ bi._flag;
                    istring str1 = this->absoluteValue().data();
                    istring str2 = bi.absoluteValue().data();
                    const ullong m = str1.length() - 1;
                    const ullong n = str2.length() - 1;
                    ullong lim = 1, dig = 0;
                    while (lim <= m + n)
                    {
                        lim <<= 1;
                        dig++;
                    }
                    std::vector<iComplex> a;
                    std::vector<iComplex> b;
                    std::vector<int> resort;
                    for (ullong i = 0; i <= lim; ++i)
                    {
                        a.emplace_back(0, 0);
                        b.emplace_back(0, 0);
                        resort.emplace_back(0);
                    }
                    for (ullong i = 0; i <= m; ++i)
                    {
                        a[i] = iComplex(str1.charAt(i) - '0', 0);
                    }
                    for (ullong i = 0; i <= n; ++i)
                    {
                        b[i] = iComplex(str2.charAt(i) - '0', 0);
                    }
                    for (int i = 0; i < lim; i++)
                        resort[i] = (resort[i >> 1] >> 1) | ((i & 1) << (dig - 1));
                    FFT(a, 1, lim, resort);
                    FFT(b, 1, lim, resort);
                    for (ullong i = 0; i < lim; i++)
                        a[i] = a[i] * b[i];
                    FFT(a, -1, lim, resort);

                    iBigInteger result(0);
                    for (ullong i = 0; i <= n + m; i++)
                    {
                        result = result + lround(a[i].re / lim);
                        if (i != n + m)
                            result = result << 1;
                    }
                    result._flag = flag;
                    return result;
                }

                friend iBigInteger operator<<(CRef<iBigInteger> bi, int cnt);

            private:
                void FFT(Ref<std::vector<iComplex>> c, int state, ullong lim, Ref<std::vector<int>> resort) const
                {
                    for (ullong i = 0; i < lim; i++)
                        if (i < resort[i])
                            std::swap(c[i], c[resort[i]]);
                    for (int i = 1; i < lim; i <<= 1)
                    {
                        iComplex W1n(cos(_ISTDMATH MATH_PI / i), state * sin(_ISTDMATH MATH_PI / i)); //-
                        for (int size = i << 1, j = 0; j < lim; j += size)
                        {
                            iComplex W(1.00, 0.00);
                            for (int k = 0; k < i; k++, W = W * W1n)
                            {
                                iComplex x = c[j + k], y = W * c[j + i + k];
                                c[j + k] = x + y;
                                c[j + i + k] = x - y;
                            }
                        }
                    }
                }

            private:
                bool _flag;
                std::deque<ullong> _num;
            };

            inline Ref<std::ostream> operator<<(Ref<std::ostream> stream, Ref<iBigInteger> integer)
            {
                stream << integer.data();
                return stream;
            }

            inline Ref<std::ostream> operator<<(Ref<std::ostream> stream, RRef<iBigInteger> integer)
            {
                stream << integer.data();
                return stream;
            }

            inline iBigInteger operator<<(CRef<iBigInteger> bi, int cnt)
            {
                data::text::istring s = bi.data();
                for (int i = 0; i < cnt; ++i)
                {
                    s.append('0');
                }
                return iBigInteger({s});
            }
        }
    }
}

inline _ISTDMATH iBigInteger operator""_bi(_ISTD CPtr<char> str)
{
    return _ISTDMATH iBigInteger(_ISTDTEXT istring(str));
}
