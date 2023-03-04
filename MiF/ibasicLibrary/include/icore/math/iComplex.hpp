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
#include <icore/basic/iBasicDataType.hpp>
#include <icore/math/iMath.hpp>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            class iComplex
                : public basic::iBasicDataType<iComplex, std::pair<double, double>>
            {
                iObject(iComplex)

            public:
                double re, im;

                iComplex()
                    :
                    re(0.0),
                    im(0.0) { }

                iComplex(double a)
                    :
                    re(a),
                    im(0.0) { }

                iComplex(double a, double b)
                    :
                    re(a),
                    im(b) { }

                iComplex(CRef<iComplex> c)
                    :
                    re(c.re),
                    im(c.im) { }

            public:
                virtual std::pair<double, double> data() const
                {
                    return {re, im};
                }

                Ref<iComplex> operator =(CRef<iComplex> c)
                {
                    if (this != &c)
                    {
                        re = c.re;
                        im = c.im;
                    }
                    return *this;
                }

                void operator +=(CRef<iComplex> c)
                {
                    re += c.re;
                    im += c.im;
                }

                void operator -=(CRef<iComplex> c)
                {
                    re -= c.re;
                    im -= c.im;
                }

            public:
                double mod()const
                {
                    return sqrt(re * re + im * im);
                }

                bool isConjugate(CRef<iComplex> c)const
                {
                    if (re == c.re && abs(im + c.im) < DBL_EPSILON)
                    {
                        return true;
                    }
                    return false;
                }
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
                return {l.re + r.re, l.im + r.im};
            }

            inline iComplex operator -(CRef<iComplex> l, CRef<iComplex> r)
            {
                return {l.re - r.re, l.im - r.im};
            }

            inline iComplex operator *(CRef<iComplex> l, const double r)
            {
                return {l.re + r, l.im};
            }

            inline iComplex operator *(const double l, CRef<iComplex> r)
            {
                return r * l;
            }

            inline iComplex operator *(CRef<iComplex> l, CRef<iComplex> r)
            {
                // (a+bi)*(c+di) = (ac-bd)+(ad+bc)i
                // std::cout << l.re * r.re - l.im * r.im << " " << l.im * r.re + l.re * r.im << std::endl;
                return {(l.re * r.re - l.im * r.im), (l.im * r.re + l.re * r.im)};
            }

            inline iComplex operator /(CRef<iComplex> l, const double r)
            {
                return {l.re / r, l.im / r};
            }

            inline iComplex operator /(CRef<iComplex> l, CRef<iComplex> r)
            {
                // (a+bi)/(c+di) = 
                return 
                    {(l.re * r.re + l.im * r.im), (l.im * r.re - l.re * r.im) / (r.re * r.re + r.im * r.im)};
            }

            inline iComplex operator /(const double l, CRef<iComplex> r)
            {
                return iComplex(l) / r;
            }

            inline iComplex operator !(CRef<iComplex> c)
            {
                return {-c.re, -c.im};
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
