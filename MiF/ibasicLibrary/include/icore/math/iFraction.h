/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iFraction.hpp
* @创建时间：2023.1.10.22:29
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 分数类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

// ReSharper disable All
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.h>
#include <icore/data/text/istring.h>
#include <icore/math/iMath.hpp>


SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            class IAPI iFraction
                :public basic::iBasicDataType<iFraction, double>
            {

                using istring = data::text::istring;
                iObject(iFraction)

            public:

                iFraction();

                iFraction(int i);


                iFraction(int a, int b);

                iFraction(CRef<iFraction> f);

                iFraction(istring str);
            public:

                int getNumerator() const;

                int getDenominator() const;

                void setNumerator(int numerator);

                void setDenominator(int denominator);

                bool isZero() const;

                bool isNegative() const;

            public:

                virtual double data() const;


                iFraction operator+(CRef<iFraction> f) const;

                iFraction operator-(CRef<iFraction> f) const;

                iFraction operator*(CRef<iFraction> f) const;

                iFraction operator/(CRef<iFraction> f) const;

                iFraction operator+(int n) const;

                iFraction operator-(int n) const;

                iFraction operator-() const;

                static llong exponentiationBySquaring4Int(int a, int b);

                iFraction operator^(int n) const;

                auto operator<=>(CRef<iFraction> c)const;

                bool operator==(CRef<iFraction> c) const;

                std::string toStdString() const;

                std::string toStdStringWithOperator()const;

                friend IAPI Ref<std::ostream> operator<<(Ref<std::ostream> stream, CRef<iFraction> f);

            private:
                int _numerator;
                int _denominator;
            };

            inline IAPI iFraction operator+(int n, iFraction f);

            inline IAPI iFraction operator-(int n, iFraction f);

            inline IAPI iFraction operator*(int n, iFraction f);

            inline IAPI iFraction operator/(int n, iFraction f);

            inline IAPI Ref<iFraction> operator+=(Ref<iFraction> l, CRef<iFraction> r);

            inline IAPI Ref<iFraction> operator-=(Ref<iFraction> l, CRef<iFraction> r);

            inline IAPI Ref<iFraction> operator*=(Ref<iFraction> l, CRef<iFraction> r);

            inline IAPI Ref<iFraction> operator/=(Ref<iFraction> l, CRef<iFraction> r);
            
        }
    }
}