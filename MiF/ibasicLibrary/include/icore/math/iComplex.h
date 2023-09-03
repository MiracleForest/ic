/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iComplex.hpp
* @创建时间：2023.1.10.20:20
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 复数类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

#pragma once
#pragma warning(disable:4305)

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.h>
#include <icore/data/text/istring.h>
#include <icore/math/iFraction.h>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            class IAPI iComplex
                : public basic::iBasicDataType<iComplex, std::pair<double, double>>
            {
                iObject(iComplex)

            public:
                double re, im;

                iComplex();

                iComplex(double a);

                iComplex(double a, double b);

                iComplex(CRef<iComplex> c);

            public:
                [[nodiscard]] virtual std::pair<double, double> data() const;

                Ref<iComplex> operator =(CRef<iComplex> c);

                void operator +=(CRef<iComplex> c);
                void operator -=(CRef<iComplex> c);

            public:
                [[nodiscard]] double mod()const;

                [[nodiscard]] bool isConjugate(CRef<iComplex> c)const;
                using istring = data::text::istring;
                [[nodiscard]] istring toiString() const;

            };

            class IAPI iFractionComplex
                :public basic::iBasicDataType<iFractionComplex, std::pair<iFraction, iFraction>>
            {
                iFraction re, im;

                iFractionComplex()
                    :re{}, im{}
                {}

                iFractionComplex(iFraction a)
                    : re{ a }, im{}
                {}

                iFractionComplex(iFraction a, iFraction b)
                    :re{ a }, im{ b }
                {}
            };

            inline IAPI Ref<std::ostream> operator<<(Ref<std::ostream> stream, Ref<iComplex> c);

            inline IAPI Ref<std::ostream> operator<<(Ref<std::ostream> stream, RRef<iComplex> c);

            inline IAPI iComplex operator +(CRef<iComplex> l, CRef<iComplex> r);

            inline IAPI iComplex operator -(CRef<iComplex> l, CRef<iComplex> r);

            inline IAPI iComplex operator *(CRef<iComplex> l, double r);

            inline IAPI iComplex operator *(double l, CRef<iComplex> r);

            inline IAPI iComplex operator *(CRef<iComplex> l, CRef<iComplex> r);

            inline IAPI iComplex operator /(CRef<iComplex> l, double r);

            inline IAPI iComplex operator /(CRef<iComplex> l, CRef<iComplex> r);

            inline IAPI iComplex operator /(double l, CRef<iComplex> r);

            inline IAPI iComplex operator !(CRef<iComplex> c);

            inline IAPI Ref<iComplex> operator +=(Ref<iComplex> l, CRef<iComplex> r);

            inline IAPI Ref<iComplex> operator -=(Ref<iComplex> l, CRef<iComplex> r);

            inline IAPI Ref<iComplex> operator *=(Ref<iComplex> l, CRef<iComplex> r);

            inline IAPI Ref<iComplex> operator /=(Ref<iComplex> l, CRef<iComplex> r);
        }
    }
}
