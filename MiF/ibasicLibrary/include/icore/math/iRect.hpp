/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iRect.hpp
* @创建时间：2022.5.23.13:07
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 矩形类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.hpp>
#include <icore/math/iVec4.hpp>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{

			template <typename T>
			class iRect
				:public basic::iBasic<iRect>
			{
				iObject(iRect);
			public:

				iRect()
				{
					setRect((T)0, (T)0, (T)0, (T)0);
				}
				iRect(T vX, T vY, T vW, T vH)
				{
					setRect(vX, vY, vW, vH);
				}
				iRect(Vec2<T> xy, Vec2<T> zw)
				{
					setRect(xy.x, xy.y, zw.x, zw.y);
				}

				~iRect()
				{ }

			public:

				void setRect(Vec2<T> xy, Vec2<T> zw)
				{
					setRect(xy.x, xy.y, zw.x, zw.y);
				}


				void setRect(T vX, T vY, T vW, T vH)
				{
					x = vX;
					y = vY;
					w = vW;
					h = vH;
					left = vX;
					right = vX + vW;
					top = vY + vH;
					bottom = vY;
				}


				Vec2<T> rightBottom() const
				{
					return Vec2<T>(right, bottom);
				}


				Vec2<T> rightTop() const
				{
					return Vec2<T>(right, top);
				}


				Vec2<T> leftBottom() const
				{
					return Vec2<T>(left, bottom);
				}


				Vec2<T> leftTop() const
				{
					return Vec2<T>(left, top);
				}


				Vec2<T> center() const
				{
					return Vec2<T>((left + right) / (T)2, (top + bottom) / (T)2);
				}


				Ptr<Vec2<T>> vertices()
				{
					Ptr <Vec2<T>> buf = new Vec2<T>[4];
					buf[0] = leftBottom();
					buf[1] = leftTop();
					buf[2] = rightTop();
					buf[3] = rightBottom();
					return buf;
				}


				Ptr<Vec2<T>> texCoords(T scaleX, T scaleY)
				{
					Ptr<Vec2<T>> buf = new Vec2<T>[4];
					buf[0] = Vec2<T>((T)0, (T)0);
					buf[1] = Vec2<T>((T)scaleX, (T)0);
					buf[2] = Vec2<T>(scaleX, scaleY);
					buf[3] = Vec2<T>((T)0, scaleY);
					return buf;
				}


				void setWidth(T vw)
				{
					w = vw;
				}


				void setHeight(T vh)
				{
					h = vh;
				}


				void snackLeft(T vleft)
				{
					x = vleft;
					w -= vleft;
					left = x;
				}


				void snackRight(T vright)
				{
					w -= vright;
					right = w + x;
				}


				void snackTop(T vtop)
				{
					h -= vtop;
					top = h + y;
				}


				void snackBottom(T vbottom)
				{
					y = vbottom;
					h -= vbottom;
					bottom = y;
				}


				bool isContainPoint(Vec2<T> pt)
				{
					if (pt.x > left)
						if (pt.x < right)
							if (pt.y > bottom)
								if (pt.y < top)return true;
					return false;
				}


				bool isIntersectedByLine(Vec2<T> v0, Vec2<T> v1)
				{
					if ((v0.x <= left && v1.x <= left) ||
						(v0.y <= bottom && v1.y <= bottom) ||
						(v0.x >= right && v1.x >= right) ||
						(v0.y >= top && v1.y >= top))
						return false; // Completely outside.
					if (IS_FLOAT_EQUAL(v1.y, v0.y) && IS_FLOAT_EQUAL(v1.x, v0.x)) return true;
					if (IS_FLOAT_DIFFERENT(v1.x, v0.x)) // avoid div by zero
					{
						float _m = (v1.y - v0.y) / (v1.x - v0.x);
						float _y = _m * (left - v0.x) + v0.y;
						if (_y >= bottom && _y <= top) return true;
						_y = _m * (right - v0.x) + v0.y;
						if (_y >= bottom && _y <= top) return true;
						if (IS_FLOAT_DIFFERENT(_m, 0.0f)) // avoid div by zero
						{
							float _x = (bottom - v0.y) / _m + v0.x;
							if (_x >= left && _x <= right) return true;
							_x = (top - v0.y) / _m + v0.x;
							if (_x >= left && _x <= right) return true;
						}
					}
					return false;
				}



				bool isIntersectedByCircle(Vec2<T> vPos, T vRadius)
				{
					T d = maxi<T>(abs<T>(center() - vPos) - size() / (T)2, (T)0).lengthSquared();
					return d < vRadius * vRadius;
				}



				Vec2<T> size()
				{
					return Vec2<T>(w, h);
				}
			public:
				T x, y, w, h;
				T left, right, top, bottom;

			};//class iRect

			typedef iRect<int> iiRect;
			typedef iRect<double> diRect;
			typedef iRect<float> fiRect;



			template <typename T>
			inline iRect<T> floor(CRef<iRect<T>> a)
			{
				return iRect<T>(
					_function::floor<T>(a.x),
					_function::floor<T>(a.y),
					_function::floor<T>(a.w),
					_function::floor<T>(a.h));
			}



			template <typename T>
			inline iRect<T> ceil(CRef<iRect<T>> a)
			{
				return iRect<T>(
					_function::ceil<T>(a.x),
					_function::ceil<T>(a.y),
					_function::ceil<T>(a.w),
					_function::ceil<T>(a.h));
			}



			template <typename T>
			inline bool operator == (iRect<T> v, iRect<T> f)
			{
				return f.x == v.x &&
					f.y == v.y &&
					f.w == v.w &&
					f.h == v.h;
			}



			template <typename T>
			inline bool operator != (iRect<T> v, iRect<T> f)
			{
				return f.x != v.x ||
					f.y != v.y ||
					f.w != v.w ||
					f.h != v.h;
			}


		}//SPACE(math)
	}//SPACE(core)
}//SPACE(i)

