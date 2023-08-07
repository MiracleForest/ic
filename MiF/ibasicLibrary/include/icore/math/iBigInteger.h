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
#include <icore/basic/iBasicDataType.h>
#include <icore/data/text/istring.h>

#include <vector>
#include <string>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {

            using istring = _ISTDTEXT istring;

            class IAPI

                iBigInteger
            {
                std::vector<unsigned> v;
                bool _flag;
            public:

                iBigInteger();

                iBigInteger(int i);

                iBigInteger(unsigned i);

                iBigInteger(long long i);

                iBigInteger(unsigned long long i);

                iBigInteger(CRef<iBigInteger> i);

                iBigInteger(CRef<std::string> s, int radix = 10);

                iBigInteger operator+(CRef<iBigInteger> b) const;

                iBigInteger operator-(CRef<iBigInteger> b) const;

                iBigInteger operator*(CRef<iBigInteger> i);

                iBigInteger operator%(CRef<iBigInteger> i);

                iBigInteger operator-() const;

                iBigInteger operator<<(int n);

                iBigInteger operator>>(int n);

                iBigInteger pupilMultiply(CRef<iBigInteger> i);

                iBigInteger karatsubaMultiply(CRef<iBigInteger> i);

                iBigInteger NTTMultiply(CRef<iBigInteger> i);


                void printEachNumber() const;

                [[nodiscard]] size_t size() const;

            private:

                friend auto operator<=>(CRef<iBigInteger> lhs, CRef<iBigInteger> rhs);

                friend bool operator==(CRef<iBigInteger> lhs, CRef<iBigInteger> rhs);

                void setFlag(bool flag);

                static bool accordWithRadix(int c, int radix);

                void delete0();

                iBigInteger moveLeft(int n) const;

                iBigInteger moveRight(int n) const;

                static bool check0(CPtr<char> str, int length);

                static bool getEvenOrOdd(CPtr<char> str);

                static void divideBy2(Ptr<char> str, int radix);

                static iBigInteger negative(CRef<iBigInteger> i);

                iBigInteger absoluteValue() const;

                static iBigInteger from1MovingLeft(int n);

                static iBigInteger fillBits(long long n);


                [[nodiscard]] bool isZero() const;

                [[nodiscard]] std::vector<bool> toVector() const;

                [[nodiscard]] std::string toStdString() const;


                static void add1(Ptr<char>);

                static void multiplyBy2(Ptr<char>);

                friend IAPI Ref<std::ostream> operator<<(Ref<std::ostream> stream, CRef<iBigInteger> i);
            };

            void operator+=(Ref<iBigInteger> lhs, RRef<iBigInteger> rhs);

            void operator+=(Ref<iBigInteger> lhs, CRef<iBigInteger> rhs);

            void operator-=(Ref<iBigInteger> lhs, RRef<iBigInteger> rhs);

            void operator-=(Ref<iBigInteger> lhs, CRef<iBigInteger> rhs);

            void operator++(Ref<iBigInteger> lhs);

            void operator--(Ref<iBigInteger> lhs);

        }
    }
}

inline _ISTDMATH iBigInteger operator ""_bi(_ISTD CPtr<char> str)
{
    return _ISTDMATH iBigInteger(std::string(str));
}

