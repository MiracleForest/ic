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
#include <icore/math/iMath.hpp>
#include <icore/data/text/istring.h>
#include <icore/math/iFraction.hpp>

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

            inline Ref<std::ostream> operator<<(Ref<std::ostream> stream, Ref<iComplex> c)
            {
                stream << "(" << c.re;
                if (c.im != 0)
                {
                    std::cout << "," << c.im << "i";
                }
                std::cout << ")";
                return stream;
            }

            inline Ref<std::ostream> operator<<(Ref<std::ostream> stream, RRef<iComplex> c)
            {
                stream << "(" << c.re;
                if (c.im != 0)
                {
                    std::cout << "," << c.im << "i";
                }
                std::cout << ")";
                return stream;
            }

            inline iComplex operator +(CRef<iComplex> l, CRef<iComplex> r)
            {
                return { l.re + r.re, l.im + r.im };
            }

            inline iComplex operator -(CRef<iComplex> l, CRef<iComplex> r)
            {
                return { l.re - r.re, l.im - r.im };
            }

            inline iComplex operator *(CRef<iComplex> l, const double r)
            {
                return { l.re + r, l.im };
            }

            inline iComplex operator *(const double l, CRef<iComplex> r)
            {
                return r * l;
            }

            inline iComplex operator *(CRef<iComplex> l, CRef<iComplex> r)
            {
                // (a+bi)*(c+di) = (ac-bd)+(ad+bc)i
                // std::cout << l.re * r.re - l.im * r.im << " " << l.im * r.re + l.re * r.im << std::endl;
                return { (l.re * r.re - l.im * r.im), (l.im * r.re + l.re * r.im) };
            }

            inline iComplex operator /(CRef<iComplex> l, const double r)
            {
                return { l.re / r, l.im / r };
            }

            inline iComplex operator /(CRef<iComplex> l, CRef<iComplex> r)
            {
                // (a+bi)/(c+di) =
                return
                { (l.re * r.re + l.im * r.im), (l.im * r.re - l.re * r.im) / (r.re * r.re + r.im * r.im) };
            }

            inline iComplex operator /(const double l, CRef<iComplex> r)
            {
                return iComplex(l) / r;
            }

            inline iComplex operator !(CRef<iComplex> c)
            {
                return { -c.re, -c.im };
            }

            inline Ref<iComplex> operator +=(Ref<iComplex> l, CRef<iComplex> r)
            {
                const iComplex i = l;
                l.re = (i + r).re;
                l.im = (i + r).im;
                return l;
            }

            inline Ref<iComplex> operator -=(Ref<iComplex> l, CRef<iComplex> r)
            {
                const iComplex i = l;
                l.re = (i - r).re;
                l.im = (i - r).im;
                return l;
            }

            inline Ref<iComplex> operator *=(Ref<iComplex> l, CRef<iComplex> r)
            {
                const iComplex i = l;
                l.re = (i * r).re;
                l.im = (i * r).im;
                return l;
            }

            inline Ref<iComplex> operator /=(Ref<iComplex> l, CRef<iComplex> r)
            {
                const iComplex i = l;
                l.re = (i / r).re;
                l.im = (i / r).im;
                return l;
            }
        }
    }
}

#pragma clang diagnostic pop