/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iAngle.hpp
* @创建时间：2023.1.10.22:29
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 角
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>
#include <icore/math/iMath.hpp>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iAngle
				:public basic::iBasicDataType<iAngle, double>
			{
				iObject(iAngle);

			public:

				iAngle()
					:_angle(0.0)
				{ }

				/*
				* @param  bool radian: ����
				 */
				iAngle(double r, bool radian = false)
				{
					if (r < 0)
					{
						r = -r;
					}
					while (r >= 360)
					{
						r -= 360;
					}
					_angle = radian ? (r / 180 * MATH_PI) : (r);
				}

				iAngle(CRef<iAngle> a)
					:_angle(a._angle)
				{ }

			public:
				virtual double data() const
				{
					return _angle;
				}

			public:
#ifdef _HAS_CXX20
				inline std::strong_ordering operator<=>(CRef<iAngle> a) const = default;
#endif

			public:
				double radian() const
				{
					return degreesToRadians(_angle);
				}

			private:
				double _angle;
			}; // iAngle

			inline iAngle operator+(CRef<iAngle> l, CRef<iAngle> r)
			{
				double a1 = l.data();
				double a2 = r.data();
				return iAngle(((a1 + a2) >= 360.0) ? (a1 + a2 - 360.0) : (a1 + a2));
			}

			inline iAngle operator-(CRef<iAngle> l, CRef<iAngle> r)
			{
				double a1 = l.data();
				double a2 = r.data();
				return iAngle((a1 < a2) ? (a2 - a1) : (a1 - a2));
			}

			inline iAngle operator*(CRef<iAngle> a, double n)
			{
				if (n < 0)
				{
					n = -n;
				}
				double angle = a.data() * n;
				while (angle >= 360)
				{
					angle -= 360;
				}
				return iAngle(angle);
			}

			inline iAngle operator*(double n, CRef<iAngle> a)
			{
				return a * n;
			}

			inline iAngle operator*(CRef<iAngle> a, int n)
			{
				return a * ((double)1.0f * n);
			}

			inline iAngle operator*(int n, CRef<iAngle> a)
			{
				return a * n;
			}

#ifndef _HAS_CXX20

			inline bool operator ==(CRef<iAngle> l, CRef<iAngle> r)
			{
				return l.data() == r.data();
			}

			inline bool operator !=(CRef<iAngle> l, CRef<iAngle> r)
			{
				return l.data() != r.data();
			}

			inline bool operator > (CRef<iAngle> l, CRef<iAngle> r)
			{
				return l.data() > r.data();
			}

			inline bool operator < (CRef<iAngle> l, CRef<iAngle> r)
			{
				return l.data() < r.data();
			}

			inline bool operator >=(CRef<iAngle> l, CRef<iAngle> r)
			{
				return l.data() >= r.data();
			}

			inline bool operator <=(CRef<iAngle> l, CRef<iAngle> r)
			{
				return l.data() <= r.data();
			}

#endif
		}
	}
}