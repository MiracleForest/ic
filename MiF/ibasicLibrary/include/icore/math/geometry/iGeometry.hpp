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
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>

#include <icore/math/iFraction.hpp>

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
                class iLineF;

                class iPoint;
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

                class iLine :
                    public basic::iBasicDataType<iLine, std::tuple<double, double, double>>
                {
                    iObject(iLine)

                public:
                    iLine(double _a, double _b, double _c)
                        :
                        _A(_a),
                        _B(_b),
                        _C(_c)
                    { }

                public:
                    // Ax+By+C=0
                    iLine static fromGeneral(double _a, double _b, double _c);

                    // y-y0=k(x-x0)
                    iLine static fromDotOblique(double x0, double y0, double k);

                    // y=kx+b
                    iLine static fromObliqueCutoff(double k, double b);
                    iLine static fromTwoPoint(double x1, double y1, double x2, double y2);
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

                private:
                    double _A;
                    double _B;
                    double _C;
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
                    { }

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
                    { }

                    iPoint(double a, double b)
                        :
                        _x(a),
                        _y(b)
                    { }

                public:
                    virtual std::pair<double, double> data() const;

                public:
                    bool isOnLine(iLine l);

                    friend std::ostream& operator<<(std::ostream& stream, CRef<iPoint> p);

                private:
                    double _x;
                    double _y;
                };

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
                    { }

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
                    { }

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
                    { }

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
                    return iLine(_a, _b, _c);
                }

                inline iLine iLine::fromDotOblique(double x0, double y0, double k)
                {
                    return iLine(k, -1, y0 - k * x0);
                }

                inline iLine iLine::fromObliqueCutoff(double k, double b)
                {
                    return iLine(k, -1, b);
                }

                inline iLine iLine::fromTwoPoint(double x1, double y1, double x2, double y2)
                {
                    return iLine(y2 - y1, x1 - x2, x2 * y1 - x1 * y2);
                }

                inline iLine iLine::fromIntercept(double a, double b)
                {
                    return iLine(b, a, -a * b);
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
                    return iLineF({ _a, _b, _c });
                }

                inline iLineF iLineF::fromDotOblique(CRef<iFraction> x0, CRef<iFraction> y0, CRef<iFraction> k)
                {
                    return iLineF({ k, -1, y0 - k * x0 });
                }

                inline iLineF iLineF::fromObliqueCutoff(CRef<iFraction> k, CRef<iFraction> b)
                {
                    return iLineF({ k, -1, b });
                }

                inline iLineF iLineF::fromTwoPoint(CRef<iFraction> x1, CRef<iFraction> y1, CRef<iFraction> x2, CRef<iFraction> y2)
                {
                    return iLineF({ y2 - y1, x1 - x2, x2 * y1 - x1 * y2 });
                }

                inline iLineF iLineF::fromIntercept(CRef<iFraction> a, CRef<iFraction> b)
                {
                    return iLineF({ b, a, -a * b });
                }

                inline istring iLineF::toAnalyticExpression(iLineEquationMode m = iLineEquationMode::General,
                    CRef<istring> dependentVariable = "y",
                    CRef<istring> independentVariable = "x")
                {
                    if (m == iLineEquationMode::General)
                    {
                        return istring("") + _A.toStdString() + independentVariable + _B.toStdStringWithOperator() +
                            dependentVariable + _C.toStdStringWithOperator() + "=0";
                    }
                    else
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
