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
#include <icore/basic/iBasicDataType.h>
#include <icore/math/iMath.hpp>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class IAPI iAngle
				:public basic::iBasicDataType<iAngle, double>
			{
				iObject(iAngle);

			public:

				iAngle();

				/*
				* @param  bool radian: ����
				 */
				iAngle(double r, bool radian = false);

				iAngle(CRef<iAngle> a);

			public:
				virtual double data() const;

			public:
#ifdef _HAS_CXX20
				inline std::strong_ordering operator<=>(CRef<iAngle> a) const = default;
#endif

			public:
				double radian() const;

			private:
				double _angle;
			}; // iAngle

			inline iAngle operator+(CRef<iAngle> l, CRef<iAngle> r);

			inline iAngle operator-(CRef<iAngle> l, CRef<iAngle> r);

			inline iAngle operator*(CRef<iAngle> a, double n);

			inline iAngle operator*(double n, CRef<iAngle> a);

			inline iAngle operator*(CRef<iAngle> a, int n);

			inline iAngle operator*(int n, CRef<iAngle> a);

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