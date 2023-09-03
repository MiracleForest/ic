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


#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.h>
#include <icore/console/iLogger.h>

#include <icore/math/iFraction.h>
#include <icore/math/iMath.hpp>

#include "icore/console/iConsole.h"
#include "icore/math/iComplex.h"

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

SPACE(i::core::math::geometry)
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

    class IAPI

        iLine : public basic::iBasicDataType<iLine, std::tuple<double, double, double>>
    {
        iObject(iLine)

    public:

        iLine(double _a, double _b, double _c);

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
    class IAPI
        iLineI : public basic::iBasicDataType <iLineI, std::pair<int, int>>
    {
        iObject(iLineI)
    public:

        iLineI(int _k, int _b);

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

        istring toAnalyticExpression(iLineEquationMode m, CRef <istring>, CRef <istring>);

        istring toLatexAnalyticExpression(iLineEquationMode m);

    private:
        int _K;
        int _B;
    };

    // iLineF
    class IAPI

        iLineF : public basic::iBasicDataType <iLineF, std::tuple<iFraction, iFraction, iFraction>>
    {
        iObject(iLineF)
    public:
        iLineF(iFraction
            _a,
            iFraction _b, iFraction
            _c);

    public:

        // Ax+By+C=0
        iLineF static fromGeneral(CRef <iFraction> _a, CRef <iFraction> _b, CRef <iFraction> _c);

        // y-y0=k(x-x0)
        iLineF static fromDotOblique(CRef <iFraction> x0, CRef <iFraction> y0, CRef <iFraction> k);

        // y=kx+b
        iLineF static fromObliqueCutoff(CRef <iFraction> k, CRef <iFraction> b);

        iLineF static fromTwoPoint(CRef <iFraction> x1, CRef <iFraction> y1, CRef <iFraction> x2, CRef <iFraction> y2);

        iLineF static fromIntercept(CRef <iFraction> a, CRef <iFraction> b);

    public:

        virtual std::tuple<iFraction, iFraction, iFraction> data() const;

    public:

        [[nodiscard]] iFraction slope() const;

        [[nodiscard]] iFraction xIntercept() const;

        [[nodiscard]] iFraction yIntercept() const;

        bool canPass(iPointF p);

        int passQuadrants();

        bool canPassQuadrant(int quadrant);

        istring toAnalyticExpression(iLineEquationMode m = iLineEquationMode::General,
            CRef <istring> dependentVariable = "y",
            CRef <istring> independentVariable = "x");

        istring toLatexAnalyticExpression(iLineEquationMode m);

    private:
        iFraction _A;
        iFraction _B;
        iFraction _C;
    };

    // iPoint
    class IAPI

        iPoint : public basic::iBasicDataType <iPoint, std::pair<double, double>>
    {
        iObject(iPoint)
    public:

        iPoint();

        iPoint(double a, double b);

        iPoint(iComplex
            c);

    public:

        virtual std::pair<double, double> data() const;

    public:

        bool isOnLine(iLine l) const;

        double x() const;

        double y() const;

    private:
        double _x;
        double _y;
    };

    class IAPI

        iPointI
        : public basic::iBasicDataType <iPointI, std::pair<int, int>>
    {
        iObject(iPointI);

        iPointI();

        iPointI(int a, int b);

    private:
        int _x;
        int _y;
    };

    // iPointF
    class IAPI

        iPointF : public basic::iBasicDataType <iPointF, std::pair<iFraction, iFraction>>
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
    class IAPI

        iTriangle : public basic::iBasic <iTriangle>
    {
        iObject(iTriangle)
    public:

        iTriangle(double a, double b, double c)
            : _a(a),
            _b(b),
            _c(c)
        {}

    private:
        double _a;
        double _b;
        double _c;
    };

    // iRectangle
    class IAPI

        iRectangle : public basic::iBasic <iRectangle>
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
            : _w(w),
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
    class IAPI

        iRectangleF : public basic::iBasic <iRectangleF>
    {
        iObject(iRectangleF)

    public:
        /*
         * @param w 宽度
         * @param h 高度
         * @param x 左下角顶点的x坐标
         * @param y 左下角顶点的y坐标
         */
        iRectangleF(iFraction
            w,
            iFraction h, iFraction
            x = 0, iFraction
            y = 0
        )
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
    class IAPI

        iSquare : public basic::iBasic <iSquare>
    {
        iObject(iSquare)
    };

    // iPoint3D
    class IAPI

        iPoint3D : public basic::iBasicDataType <iPoint3D, std::tuple<double, double, double>>
    {
        iObject(iPoint3D)
    };

    // iLine3D
    class IAPI

        iLine3D : public basic::iBasicDataType <iLine3D, std::tuple<double, double, double, double>>
    {
        iObject(iLine3D)
    };

    // iCuboid
    class IAPI

        iCuboid : public basic::iBasicDataType <iCuboid, std::tuple<double, double, double>>
    {
        iObject(iCuboid)
    };

    // iCube
    class IAPI

        iCube : public basic::iBasicDataType<iCube, double>
    {
        iObject(iCube)
    };

    iPoint intersection(iLine l1, iLine l2);

}