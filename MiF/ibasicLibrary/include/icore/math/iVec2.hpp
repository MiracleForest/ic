/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：vec2.hpp
* @创建时间：2022.5.20.21:52
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 祝大家520快乐！
* iVec2类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#pragma warning(disable:4305)

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
#include <thread>
#include <icore/math/iMath.hpp>
#include <Windows.h>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{



			template <typename T>
			class iVec2
				:public basic::iBasicDataType<iVec2<T>, std::pair<T, T>>
			{
				using istring = data::text::istring;
				iObject(iVec2);

			public:
				iVec2<T>()
				{
					x = (T)0;
					y = (T)0;
				}

				template <typename U>
				iVec2<T>(CRef<iVec2<U>> a)
				{
					x = (T)a.x;
					y = (T)a.y;
				}

				iVec2<T>(CRef<T> a)
				{
					x = a;
					y = a;
				}

				iVec2<T>(CRef<T> a, CRef<T> b)
				{
					x = a;
					y = b;
				}

				iVec2<T>(CRef<istring> Vec, CRef<char> c = ';', Ptr<iVec2<T>> def = nullptr)
				{
					if (def)
					{
						x = def->x;
						y = def->y;
					}
					::std::vector<T> result = stringToNumberVector<T>(Vec.data(), c);
					const size_t s = result.size();
					if (s > 0) x = result[0];
					if (s > 1) y = result[1];
				}

				~iVec2()
				{ }

			public:

				virtual std::pair<T, T> data()const
				{
					return { x,y };
				}

			public:

				T& operator [] (CRef<size_t> i)
				{
					return (&x)[i];
				}


				iVec2<T> offset(CRef<T> vX, CRef<T> vY) const
				{
					return iVec2<T>(x + vX, y + vY);
				}


				void set(CRef<T> vX, CRef<T> vY)
				{
					x = vX;
					y = vY;
				}


				iVec2<T> operator -() const
				{
					return iVec2<T>(-x, -y);
				}


				iVec2<T> operator !() const
				{
					return iVec2<T>(!x, !y);
				}



				Ref<iVec2<T>> operator ++ ()
				{
					++x; ++y; return *this;
				}



				Ref<iVec2<T>> operator -- ()
				{
					--x; --y; return *this;
				}



				iVec2<T> operator ++ (int)
				{
					iVec2<T> tmp = *this;
					++* this; return tmp;
				}



				iVec2<T> operator -- (int)
				{
					iVec2<T> tmp = *this;
					--* this;
					return tmp;
				}



				void operator += (CRef<T> a)
				{
					x += a; y += a;
				}


				void operator += (CRef<iVec2<T>> v)
				{
					x += v.x;
					y += v.y;
				}


				void operator -= (CRef<T> a)
				{
					x -= a;
					y -= a;
				}


				void operator -= (CRef<iVec2<T>> v)
				{
					x -= v.x;
					y -= v.y;
				}


				bool operator == (CRef<T> a)
				{
					return (x == a) && (y == a);
				}


				bool operator == (CRef<iVec2<T>> v)
				{
					return (x == v.x) && (y == v.y);
				}


				bool operator != (CRef<T> a)
				{
					return (x != a) || (y != a);
				}


				bool operator != (CRef<iVec2<T>> v)
				{
					return (x != v.x) || (y != v.y);
				}


				void operator *= (CRef<T> a)
				{
					x *= a;
					y *= a;
				}


				void operator *= (CRef<iVec2<T>> v)
				{
					x *= v.x;
					y *= v.y;
				}


				void operator /= (CRef<T> a)
				{
					x /= a;
					y /= a;
				}


				void operator /= (CRef<iVec2<T>> v)
				{
					x /= v.x;
					y /= v.y;
				}


				T lengthSquared() const
				{
					return x * x + y * y;
				}


				T length() const
				{
					return (T)sqrt(lengthSquared());
				}


				T normalize()
				{
					T _length = length();
					if (_length < (T)1e-5)
					{
						return (T)0.0;
					}
					T _invLength = (T)1.0 / _length;
					x *= _invLength;
					y *= _invLength;
					return _length;
				}


				iVec2<T> getNormalized() const
				{
					iVec2<T> n = iVec2<T>(x, y);
					n.normalize();
					return n;
				}


				T sum() const
				{
					return x + y;
				}


				T sumAbs() const
				{
					return abs<T>(x) + abs<T>(y);
				}


				bool emptyAND() const
				{
					return x == (T)0 && y == (T)0;
				}


				bool emptyOR() const
				{
					return x == (T)0 || y == (T)0;
				}


				istring string(CRef<char> c = ';') const
				{
					return (std::to_string(x) + c + std::to_string(y));
				}


				template <typename U>
				U ratioXY() const
				{
					if (y != (T)0) return (U)x / (U)y;
					return (U)0;
				}


				template <typename U>
				U ratioYX() const
				{
					if (x != (T)0) return (U)y / (U)x;
					return (U)0;
				}


				T mini() const
				{
					return internalMini<T>(x, y);
				}


				T maxi() const
				{
					return internalMaxi<T>(x, y);
				}

			public:
				T x, y;
			};//class iVec2 

			template <typename T>
			inline Ref<iVec2<T>> operator ++ (Ref<iVec2<T>> v)
			{
				++v;
				return v;
			}


			template <typename T>
			inline Ref<iVec2<T>> operator -- (Ref<iVec2<T>> v)
			{
				--v;
				return v;
			}


			template <typename T>
			inline iVec2<T> operator ++ (Ref<iVec2<T>> v, int)
			{
				iVec2<T> a = v;
				++a;
				return a;
			}


			template <typename T>
			inline iVec2<T> operator -- (Ref<iVec2<T>> v, int)
			{
				iVec2<T> a = v;
				--a;
				return a;
			}


			template <typename T>
			inline iVec2<T> operator + (iVec2<T> v, T f)
			{
				return iVec2<T>(v.x + f, v.y + f);
			}


			template <typename T>
			inline iVec2<T> operator + (T f, iVec2<T> v)
			{
				return iVec2<T>(v.x + f, v.y + f);
			}


			template <typename T>
			inline iVec2<T> operator + (iVec2<T> v, iVec2<T> f)
			{
				return iVec2<T>(v.x + f.x, v.y + f.y);
			}


			template <typename T>
			inline iVec2<T> operator - (iVec2<T> v, T f)
			{
				return iVec2<T>(v.x - f, v.y - f);
			}


			template <typename T>
			inline iVec2<T> operator - (T f, iVec2<T> v)
			{
				return iVec2<T>(f - v.x, f - v.y);
			}


			template <typename T>
			inline iVec2<T> operator - (iVec2<T> v, iVec2<T> f)
			{
				return iVec2<T>(v.x - f.x, v.y - f.y);
			}


			template <typename T>
			inline iVec2<T> operator * (iVec2<T> v, T f)
			{
				return iVec2<T>(v.x * f, v.y * f);
			}


			template <typename T>
			inline iVec2<T> operator * (T f, iVec2<T> v)
			{
				return iVec2<T>(v.x * f, v.y * f);
			}


			template <typename T>
			inline iVec2<T> operator * (iVec2<T> v, iVec2<T> f)
			{
				return iVec2<T>(v.x * f.x, v.y * f.y);
			}


			template <typename T>
			inline iVec2<T> operator / (iVec2<T> v, T f)
			{
				return iVec2<T>(v.x / f, v.y / f);
			}


			template <typename T>
			inline iVec2<T> operator / (T f, iVec2<T> v)
			{
				return iVec2<T>(f / v.x, f / v.y);
			}


			template <typename T>
			inline iVec2<T> operator / (iVec2<T> v, iVec2<T> f)
			{
				return iVec2<T>(v.x / f.x, v.y / f.y);
			}


			template <typename T>
			inline bool operator < (iVec2<T> v, iVec2<T> f)
			{
				return v.x < f.x && v.y < f.y;
			}


			template <typename T>
			inline bool operator < (iVec2<T> v, T f)
			{
				return v.x < f && v.y < f;
			}


			template <typename T>
			inline bool operator > (iVec2<T> v, iVec2<T> f)
			{
				return v.x > f.x && v.y > f.y;
			}


			template <typename T>
			inline bool operator > (iVec2<T> v, T f)
			{
				return v.x > f && v.y > f;
			}


			template <typename T>
			inline bool operator <= (iVec2<T> v, iVec2<T> f)
			{
				return v.x <= f.x && v.y <= f.y;
			}


			template <typename T>
			inline bool operator <= (iVec2<T> v, T f)
			{
				return v.x <= f && v.y <= f;
			}


			template <typename T>
			inline bool operator >= (iVec2<T> v, iVec2<T> f)
			{
				return v.x >= f.x && v.y >= f.y;
			}


			template <typename T>
			inline bool operator >= (iVec2<T> v, T f)
			{
				return v.x >= f && v.y >= f;
			}


			template <typename T>
			inline bool operator != (iVec2<T> v, iVec2<T> f)
			{
				return f.x != v.x || f.y != v.y;
			}


			template <typename T>
			inline bool operator == (iVec2<T> v, iVec2<T> f)
			{
				return f.x == v.x && f.y == v.y;
			}


			template <typename T>
			inline iVec2<T> floor(iVec2<T> a)
			{
				return iVec2<T>(
					floor(a.x),
					floor(a.y));
			}


			template <typename T>
			inline iVec2<T> fract(iVec2<T> a)
			{
				return iVec2<T>(fract(a.x),
					fract(a.y));
			}


			template <typename T>
			inline iVec2<T> ceil(iVec2<T> a)
			{
				return iVec2<T>(ceil(a.x),
					ceil(a.y));
			}


			template <typename T>
			inline iVec2<T> mini(iVec2<T> a, iVec2<T> b)
			{
				return iVec2<T>(mini(a.x, b.x),
					mini(a.y, b.y));
			}


			template <typename T>
			inline iVec2<T> maxi(iVec2<T> a, iVec2<T> b)
			{
				return iVec2<T>(maxi(a.x, b.x),
					maxi(a.y, b.y));
			}


			template <typename T>
			inline T dot(iVec2<T> a, iVec2<T> b)
			{
				return a.x * b.x + a.y * b.y;
			}


			template <typename T>
			inline T det(iVec2<T> a, iVec2<T> b)
			{
				return a.x * b.y - a.y * b.x;
			}


			template <typename T>
			inline iVec2<T> cross(iVec2<T> a, iVec2<T> b)
			{
				return iVec2<T>(
					a.x * b.y - a.y * b.x,
					a.y * b.x - a.x * b.y);
			}


			template <typename T>
			inline iVec2<T> reflect(iVec2<T> I, iVec2<T> N)
			{
				return I - (T)2 * dotS(N, I) * N;
			}


			template <typename T>
			inline iVec2<T> sign(iVec2<T> a)
			{
				return iVec2<T>(a.x < (T)0 ? -(T)1 : (T)1,
					a.y < (T)0 ? (T)-1 : (T)1);
			}


			template <typename T>
			inline iVec2<T> sin(iVec2<T> a)
			{
				return iVec2<T>(sin<T>(a.x),
					sin<T>(a.y));
			}


			template <typename T>
			inline iVec2<T> cos(iVec2<T> a)
			{
				return iVec2<T>(cos<T>(a.x),
					cos<T>(a.y));
			}


			template <typename T>
			inline iVec2<T> tan(iVec2<T> a)
			{
				return iVec2<T>(
					tan<T>(a.x),
					tan<T>(a.y));
			}


			template <typename T>
			inline iVec2<T> atan(iVec2<T> a)
			{
				return iVec2<T>(
					atan<T>(a.x),
					atan<T>(a.y)
				);
			}


			using dvec2 = iVec2<double>;
			using fvec2 = iVec2<float>;
			using bvec2 = iVec2<bool>;
			using i8vec2 = iVec2<int8_t>;
			using i16vec2 = iVec2<int16_t>;
			using ivec2 = iVec2<int32_t>;
			using i32vec2 = iVec2<int32_t>;
			using i64vec2 = iVec2<int64_t>;
			using u8vec2 = iVec2<uint8_t>;
			using u16vec2 = iVec2<uint16_t>;
			using uvec2 = iVec2<uint32_t>;
			using u32vec2 = iVec2<uint32_t>;
			using u64vec2 = iVec2<uint64_t>;


			inline fvec2 convert(CRef<ivec2> v)
			{
				return fvec2(
					(float)v.x,
					(float)v.y
				);
			}


			inline ivec2 convert(CRef<fvec2> v)
			{
				return ivec2(
					(int)v.x,
					(int)v.y);
			}


			inline bool valid(CRef<fvec2> a)
			{
				return floatIsValid(a.x) &&
					floatIsValid(a.y);
			}


			inline bool operator == (CRef<fvec2> v, CRef<fvec2> f)
			{
				return (IS_FLOAT_EQUAL(f.x, v.x) &&
					IS_FLOAT_EQUAL(f.y, v.y));
			}

			inline bool operator != (CRef<fvec2> v, CRef<fvec2> f)
			{
				return (
					IS_FLOAT_DIFFERENT(f.x, v.x) ||
					IS_FLOAT_DIFFERENT(f.y, v.y)
					);
			}

			template <typename T>
			inline T prototypeRadAngleFromiVec2(iVec2<T> vec)
			{
				T angle = 0.0f;
				if (vec.lengthSquared() > T(0) && vec.x != T(0))
				{
					angle = atan<T>(vec.y / vec.x);
				}
				return angle;
			}

			inline float radAngleFromiVec2(CRef<fvec2> vec)
			{
				return prototypeRadAngleFromiVec2(vec);
			}

			inline double radAngleFromiVec2(CRef<dvec2> vec)
			{
				return prototypeRadAngleFromiVec2(vec);
			}


		}//SPACE(math)
	}//SPACE(core) 
}//SPACE(i)

#ifdef INCLUDE_NLOHMANN_JSON_HPP_

SPACE(nlohmann)
{

	template<class _T>
	inline void to_json(_ISTD Ref<nlohmann::json> j, _ISTD CRef<_ISTD math::iVec2<_T>> value)
	{
		json buff{
			{"x",value.x },
			{"y",value.y },
		};
		j = buff;
	}

	template<class _T>
	inline void from_json(_ISTD CRef<nlohmann::json> j, _ISTD Ref<_ISTD math::iVec2<_T>>value)
	{
		value.x = j["x"].get<_T>();
		value.y = j["y"].get<_T>();
	}

}

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_


