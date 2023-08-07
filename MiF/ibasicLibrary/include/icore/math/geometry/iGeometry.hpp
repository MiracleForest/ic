/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iGeometry.hpp
* @创建时间：2023.1.18.15:28
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 几何图形
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

// ReSharper disable All

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.h>
#include <icore/console/iLogger.h>

#include <icore/math/iFraction.hpp>
#include <icore/math/iMath.hpp>

#include "icore/console/iConsole.h"

#pragma once
// 类的预先声明
SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            SPACE(geometry)
            {
                using istring = data::text::istring;
                class iLine;
                class iLineI;
                class iLineF;

                class iPoint;
                class iPointI;
                class iPointF;

                class iTriangle;
                class iRectangle;
                class iRectangleF;
                class iSquare;

                class iPoint3D;
                class iLine3D;
                class iCuboid;
                class iCube;
            }
        }
    }
}

SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            SPACE(geometry)
            {
                // iLine
                enum class iLineEquationMode
                {
                    General,
                    DotOblique,
                    ObliqueCutoff,
                    TwoPoint,
                    Intercept
                };

                class IAPI iLine :
                    public basic::iBasicDataType<iLine, std::tuple<double, double, double>>
                {
                    iObject(iLine)

                public:
                    iLine(double _a, double _b, double _c)
                        :
                        _A(_a),
                        _B(_b),
                        _C(_c)
                    {}

                public:
                    // Ax+By+C=0
                    iLine static fromGeneral(double _a, double _b, double _c);

                    // y-y0=k(x-x0)
                    iLine static fromDotOblique(double x0, double y0, double k);

                    // y=kx+b
                    iLine static fromObliqueCutoff(double k, double b);
                    iLine static fromTwoPoint(double x1, double y1, double x2, double y2);
                    iLine static fromTwoPoint(iPoint a, iPoint b);
                    iLine static fromIntercept(double a, double b);

                public:
                    virtual std::tuple<double, double, double> data() const;

                public:
                    double slope() const;
                    double xIntercept() const;
                    double yIntercept() const;

                    bool canPass(iPoint p);
                    int passQuadrants() const;
                    bool canPassQuadrant(int quadrant) const;

                    double A() const;
                    double B() const;
                    double C() const;


                private:
                    double _A;
                    double _B;
                    double _C;
                };

                // iLineI
                class IAPI iLineI :
                    public basic::iBasicDataType<iLineI, std::pair<int, int>>
                {
                    iObject(iLineI)
                public:
                    iLineI(int _k, int _b)
                        :
                        _K(_k),
                        _B(_b)
                    {}

                public:
                    iLineI static fromDotOblique(int x0, int y0, int k);
                    iLineI static fromObliqueCutoff(int k, int b);
                public:
                    virtual std::pair<int, int> data() const;

                public:
                    [[nodiscard]] iFraction slope() const;
                    [[nodiscard]] iFraction xIntercept() const;
                    [[nodiscard]] iFraction yIntercept() const;

                    bool canPass(iPoint p);
                    int passQuadrants();
                    bool canPassQuadrant(int quadrant);

                    istring toAnalyticExpression(iLineEquationMode m, CRef<istring>, CRef<istring>);
                    istring toLatexAnalyticExpression(iLineEquationMode m);

                private:

                    int _K;
                    int _B;
                };

                // iLineF
                class iLineF :
                    public basic::iBasicDataType<iLineF, std::tuple<iFraction, iFraction, iFraction>>
                {
                    iObject(iLineF)
                public:
                    iLineF(iFraction _a, iFraction _b, iFraction _c)
                        :
                        _A(_a),
                        _B(_b),
                        _C(_c)
                    {}

                public:
                    // Ax+By+C=0
                    iLineF static fromGeneral(CRef<iFraction> _a, CRef<iFraction> _b, CRef<iFraction> _c);

                    // y-y0=k(x-x0)
                    iLineF static fromDotOblique(CRef<iFraction> x0, CRef<iFraction> y0, CRef<iFraction> k);

                    // y=kx+b
                    iLineF static fromObliqueCutoff(CRef<iFraction> k, CRef<iFraction> b);

                    iLineF static fromTwoPoint(CRef<iFraction> x1, CRef<iFraction> y1, CRef<iFraction> x2, CRef<iFraction> y2);
                    iLineF static fromIntercept(CRef<iFraction> a, CRef<iFraction> b);

                public:
                    virtual std::tuple<iFraction, iFraction, iFraction> data() const;

                public:
                    [[nodiscard]] iFraction slope() const;
                    [[nodiscard]] iFraction xIntercept() const;
                    [[nodiscard]] iFraction yIntercept() const;

                    bool canPass(iPointF p);
                    int passQuadrants();
                    bool canPassQuadrant(int quadrant);

                    istring toAnalyticExpression(iLineEquationMode m, CRef<istring>, CRef<istring>);
                    istring toLatexAnalyticExpression(iLineEquationMode m);

                private:

                    iFraction _A;
                    iFraction _B;
                    iFraction _C;
                };

                // iPoint
                class iPoint :
                    public basic::iBasicDataType<iPoint, std::pair<double, double>>
                {
                    iObject(iPoint)
                public:
                    iPoint()
                        :
                        _x(0),
                        _y(0)
                    {}

                    iPoint(double a, double b)
                        :
                        _x(a),
                        _y(b)
                    {}

                public:
                    virtual std::pair<double, double> data() const;

                public:
                    bool isOnLine(iLine l);

                    friend std::ostream& operator<<(std::ostream& stream, CRef<iPoint> p);

                    double x() const;
                    double y() const;
                private:
                    double _x;
                    double _y;
                };

                class iPointI
                    :public basic::iBasicDataType<iPointI, std::pair<int, int>>
                {
                    iObject(iPointI);

                    iPointI() :_x(0), _y(0) {}
                    iPointI(int a, int b) :_x(a), _y(b) {}
                private:
                    int _x;
                    int _y;
                };

                //iPointF
                class iPointF :
                    public basic::iBasicDataType<iPointF, std::pair<iFraction, iFraction>>
                {
                    iObject(iPointF)
                public:
                    virtual std::pair<iFraction, iFraction> data() const;

                public:
                    iFraction x() const;
                    iFraction y() const;

                private:
                    iFraction _x;
                    iFraction _y;
                };

                // iTriangle
                class iTriangle :
                    public basic::iBasic<iTriangle>
                {
                    iObject(iTriangle)
                public:
                    iTriangle(double a, double b, double c)
                        :
                        _a(a),
                        _b(b),
                        _c(c)
                    {}

                public:
                private:
                    double _a;
                    double _b;
                    double _c;
                };

                // iRectangle
                class iRectangle :
                    public basic::iBasic<iRectangle>
                {
                    iObject(iRectangle)
                public:
                    /*
                    * @param w 宽度
                    * @param h 高度
                    * @param x 左下角顶点的x坐标
                    * @param y 左下角顶点的y坐标
                    */
                    iRectangle(double w, double h, double x = 0, double y = 0)
                        :
                        _w(w),
                        _h(h),
                        _x(x),
                        _y(y)
                    {}

                private:
                    double _w;
                    double _h;
                    double _x;
                    double _y;
                };

                // iRectangleF
                class iRectangleF :
                    public basic::iBasic<iRectangleF>
                {
                    iObject(iRectangleF)

                public:
                    /*
                    * @param w 宽度
                    * @param h 高度
                    * @param x 左下角顶点的x坐标
                    * @param y 左下角顶点的y坐标
                    */
                    iRectangleF(iFraction w, iFraction h, iFraction x = 0, iFraction y = 0)
                        :
                        _w(w),
                        _h(h),
                        _x(x),
                        _y(y)
                    {}

                public:
                    static iRectangleF fromTwoPoints(iPointF a, iPointF b);

                public:
                    iLineF topSide() const;
                    iLineF bottomSide() const;
                    iLineF leftSide() const;
                    iLineF rightSide() const;

                private:
                    iFraction _w;
                    iFraction _h;
                    iFraction _x;
                    iFraction _y;
                };

                // iSquare
                class iSquare :
                    public basic::iBasic<iSquare>
                {
                    iObject(iSquare)
                };

                // iPoint3D
                class iPoint3D :
                    public basic::iBasicDataType<iPoint3D, std::tuple<double, double, double>>
                {
                    iObject(iPoint3D)
                };

                // iLine3D
                class iLine3D :
                    public basic::iBasicDataType<iLine3D, std::tuple<double, double, double, double>>
                {
                    iObject(iLine3D)
                };

                // iCuboid
                class iCuboid :
                    public basic::iBasicDataType<iCuboid, std::tuple<double, double, double>>
                {
                    iObject(iCuboid)
                };

                // iCube
                class iCube :
                    public basic::iBasicDataType<iCube, double>
                {
                    iObject(iCube)
                };

                iPoint intersection(iLine l1, iLine l2);

            }
        }
    }
}

// iLine
SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            // iLine
            SPACE(geometry)
            {
                inline std::tuple<double, double, double> iLine::data() const
                {
                    return { _A, _B, _C };
                }

                inline iLine iLine::fromGeneral(double _a, double _b, double _c)
                {
                    return { _a, _b, _c };
                }

                inline iLine iLine::fromDotOblique(double x0, double y0, double k)
                {
                    return { k, -1, y0 - k * x0 };
                }

                inline iLine iLine::fromObliqueCutoff(double k, double b)
                {
                    return { k, -1, b };
                }

                inline iLine iLine::fromTwoPoint(double x1, double y1, double x2, double y2)
                {
                    return { y2 - y1, x1 - x2, x2 * y1 - x1 * y2 };
                }

                inline iLine iLine::fromTwoPoint(iPoint a, iPoint b)
                {
                    return iLine::fromTwoPoint(a.x(), a.y(), b.x(), b.y());
                }

                inline iLine iLine::fromIntercept(double a, double b)
                {
                    return { b, a, -a * b };
                }

                inline double iLine::slope() const
                {
                    return (-_A / _B);
                }

                inline double iLine::xIntercept() const
                {
                    return (-_C / _A);
                }

                inline double iLine::yIntercept() const
                {
                    return (-_C / _B);
                }

                inline int iLine::passQuadrants() const
                {
                    if (_C == 0)
                    {
                        return ((_A * _B) > 0) ? ((1 << 2) | (1 << 4)) : ((_A * _B) < 0) ? ((1 << 1) | (1 << 3)) : 0;
                    }
                    if (_B == 0)
                    {
                        return (_C < 0) ? ((1 << 1) | (1 << 4)) : ((1 << 2) | (1 << 3));
                    }
                    if (_A == 0)
                    {
                        return (_C < 0) ? ((1 << 1) | (1 << 2)) : ((1 << 3) | (1 << 4));
                    }
                    double xi = xIntercept();
                    double yi = yIntercept();
                    return ((xi > 0) && (yi > 0))
                        ? ((1 << 1) | (1 << 2) | (1 << 4))
                        : ((xi > 0) && (yi < 0))
                        ? ((1 << 1) | (1 << 3) | (1 << 4))
                        : ((xi < 0) && (yi > 0))
                        ? ((1 << 1) | (1 << 2) | (1 << 3))
                        : ((xi < 0) && (yi < 0))
                        ? ((1 << 2) | (1 << 3) | (1 << 4))
                        : 0;
                }

                inline bool iLine::canPassQuadrant(int quadrant) const
                {
                    return passQuadrants() & (1 << quadrant);
                }
                inline double iLine::A() const
                {
                    return this->_A;
                }
                inline double iLine::B() const
                {
                    return this->_B;
                }
                inline double iLine::C() const
                {
                    return this->_C;
                }
            }

            // iLineI
            namespace geometry
            {
                inline iLineI iLineI::fromDotOblique(int x0, int y0, int k)
                {
                    return { k,y0 - k * x0 };
                }

                inline iLineI iLineI::fromObliqueCutoff(int k, int b)
                {
                    return { k,b };
                }
/*
                inline iFraction iLineI::slope() const
                {}

                inline iFraction iLineI::xIntercept() const
                {}

                inline iFraction iLineI::yIntercept() const
                {}

                inline bool iLineI::canPass(iPoint p)
                {}

                inline int iLineI::passQuadrants()
                {}

                inline bool iLineI::canPassQuadrant(int quadrant)
                {}

                inline istring iLineI::toAnalyticExpression(iLineEquationMode m, CRef<istring>, CRef<istring>)
                {}

                inline istring iLineI::toLatexAnalyticExpression(iLineEquationMode m)
                {}
*/
                inline std::pair<int, int> iLineI::data() const
                {
                    return { _K,_B, };
                }
            }

            // iLineF
            SPACE(geometry)
            {
                inline std::tuple<iFraction, iFraction, iFraction> iLineF::data() const
                {
                    return { _A, _B, _C };
                }

                inline iFraction iLineF::slope() const
                {
                    return (-_A / _B);
                }

                inline iFraction iLineF::xIntercept() const
                {
                    return (-_C / _A);
                }

                inline iFraction iLineF::yIntercept() const
                {
                    return (-_C / _B);
                }

                inline iLineF iLineF::fromGeneral(CRef<iFraction> _a, CRef<iFraction> _b, CRef<iFraction> _c)
                {
                    return { _a, _b, _c };
                }

                inline iLineF iLineF::fromDotOblique(CRef<iFraction> x0, CRef<iFraction> y0, CRef<iFraction> k)
                {
                    return { k, -1, y0 - k * x0 };
                }

                inline iLineF iLineF::fromObliqueCutoff(CRef<iFraction> k, CRef<iFraction> b)
                {
                    return { k, -1, b };
                }

                inline iLineF iLineF::fromTwoPoint(CRef<iFraction> x1, CRef<iFraction> y1, CRef<iFraction> x2, CRef<iFraction> y2)
                {
                    return { y2 - y1, x1 - x2, x2 * y1 - x1 * y2 };
                }

                inline iLineF iLineF::fromIntercept(CRef<iFraction> a, CRef<iFraction> b)
                {
                    return { b, a, -a * b };
                }

                inline istring remove1(istring s, bool withOperator = false)
                {
                    if (withOperator)
                    {
                        if (s == istring("+1"))
                        {
                            return "+";
                        } else if (s == istring("-1"))
                        {
                            return "-";
                        } else
                        {
                            return s;
                        }
                    } else
                    {
                        if (s == istring("1"))
                        {
                            return "";
                        } else if (s == istring("-1"))
                        {
                            return "-";
                        } else
                        {
                            return s;
                        }
                    }
                }
                inline istring remove0(istring s)
                {
                    if (s == istring("+0") || s == istring("-0") || s == istring("0"))
                    {
                        return "";
                    } else return s;
                }
                inline istring iLineF::toAnalyticExpression(iLineEquationMode m = iLineEquationMode::General,
                    CRef<istring> dependentVariable = "y",
                    CRef<istring> independentVariable = "x")
                {
                    io::iLogger logger("iLine");

                    if (m == iLineEquationMode::General)
                    {
                        int denominatorA = this->_A.getDenominator();
                        int denominatorB = this->_B.getDenominator();
                        int denominatorC = this->_C.getDenominator();
                        int denominatorAB = denominatorA * denominatorB / gcd(denominatorA, denominatorB);
                        int denominatorMax = denominatorAB * denominatorC / gcd(denominatorAB, denominatorC);

                        istring str("");

                        // a
                        istring a = (_A * denominatorMax).toStdString();
                        logger.info("a: {}", a);

                        str += remove1(a);
                        str += independentVariable;

                        // b
                        istring b = (_B * denominatorMax).toStdStringWithOperator();
                        logger.info("b: {}", b);
                        str += remove1(b, true);
                        str += dependentVariable;

                        // c
                        istring c = (_C * denominatorMax).toStdStringWithOperator();
                        logger.info("c: {}", c);
                        str += remove0(c);
                        return str + "=0";
                    } else
                        return "";
                }

                inline istring iLineF::toLatexAnalyticExpression(iLineEquationMode m)
                {
                    return "";
                }
            }

            // iPoint
            SPACE(geometry)
            {
                inline std::pair<double, double> iPoint::data() const
                {
                    return { _x, _y };
                }

                inline std::ostream& operator<<(std::ostream & stream, CRef<iPoint> p)
                {
                    stream << "(" << p._x << "," << p._y << ")" << std::flush;
                    return stream;
                }
                inline bool iPoint::isOnLine(iLine l)
                {
                    return this->_x * l.A() + this->_y * l.B() + l.C() == 0;
                }
                inline double iPoint::x() const
                {
                    return _x;
                }
                inline double iPoint::y() const
                {
                    return _y;
                }
            }

            // iPointF
            SPACE(geometry)
            {
                inline std::pair<iFraction, iFraction> iPointF::data() const
                {
                    return { _x, _y };
                }

                inline iFraction iPointF::x() const
                {
                    return _x;
                }

                inline iFraction iPointF::y() const
                {
                    return _y;
                }
            }

            // iRectangleF
            SPACE(geometry)
            {
                inline iLineF iRectangleF::topSide() const
                {
                    return iLineF::fromGeneral(-(_h + _y), 0, 0);
                }

                inline iLineF iRectangleF::bottomSide() const
                {
                    return iLineF::fromGeneral(-_y, 0, 0);
                }

                inline iLineF iRectangleF::leftSide() const
                {
                    return iLineF::fromGeneral(0, -_x, 0);
                }

                inline iLineF iRectangleF::rightSide() const
                {
                    return iLineF::fromGeneral(0, -(_x + _w), 0);
                }

                inline iPoint intersection(iLine l1, iLine l2)
                {
                    return { (l2.C() * l1.B() - l1.C() * l2.B()) / (l1.A() * l2.B() - l2.A() * l1.B()) ,(l2.C() * l1.B() - l1.C() * l2.B()) / (l1.A() * l2.B() - l2.A() * l1.B()) };
                }


                inline iRectangleF iRectangleF::fromTwoPoints(iPointF a, iPointF b)
                {
                    iFraction x1 = a.x();
                    iFraction y1 = a.y();
                    iFraction x2 = b.x();
                    iFraction y2 = b.y();
                    iFraction xMin = x1 < x2 ? x1 : x2;
                    iFraction yMin = y1 < y2 ? y1 : y2;
                    iFraction xMax = x1 > x2 ? x1 : x2;
                    iFraction yMax = y1 > y2 ? y1 : y2;
                    return iRectangleF({ xMax - xMin, yMax - yMin, xMin, yMin });
                }
            }
        }
    }
}

