/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：vec3.hpp
* @创建时间：2022.5.20.13:14
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 祝大家520快乐！
* iVec3类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#pragma warning(disable:4305)

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
#include <icore/math/iVec2.hpp>

#include <cmath>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{

			template <typename T>
			class iVec3
				:public basic::iBasicDataType<iVec3<T>, std::tuple<T, T, T>>
			{
				using istring = data::text::istring;
				iObject(iVec3);
			public:

				iVec3() : x((T)0), y((T)0), z((T)0)
				{ }

				template <typename U>
				iVec3<T>(iVec3<U> a)
				{
					x = (T)a.x;
					y = (T)a.y;
					z = (T)a.z;
				}

				iVec3(CRef<T> xyz) : x(xyz), y(xyz), z(xyz)
				{ }

				iVec3(CRef<T> x, CRef<T> y, CRef<T> z) : x(x), y(y), z(z)
				{ }

				iVec3(CRef<iVec2<T>> xy, CRef<T> z) : x(xy.x), y(xy.y), z(z)
				{ }

				iVec3(CRef<istring> vec, CRef<char> c = ';', Ptr<iVec3<T>> def = nullptr)
				{
					if (def)
					{
						x = def->x; y = def->y; z = def->z;
					}
					std::vector<T> result = stringToNumberVector<T>(vec.data(), c);
					const size_t s = result.size();
					if (s > 0) x = result[0];
					if (s > 1) y = result[1];
					if (s > 2) z = result[2];
				}

				~iVec3()
				{ }

			public:

				virtual std::tuple<T, T, T> data()const
				{
					return std::make_tuple(x, y, z);
				}

			public:

				T& operator [] (CRef<size_t> i)
				{
					return (&x)[i];
				}


				iVec3<T> offset(
					CRef<T> vX,
					CRef<T> vY,
					CRef<T> vZ
				) const
				{
					return iVec3<T>(x + vX, y + vY, z + vZ);
				}


				void setXYZ(
					CRef<T> vX,
					CRef<T> vY,
					CRef<T> vZ
				)
				{
					x = vX;
					y = vY;
					z = vZ;
				}


				iVec3<T> operator -() const
				{
					return iVec3<T>(-x, -y, -z);
				}


				iVec3<T> operator !() const
				{
					return iVec3<T>(!x, !y, !z);
				}


				iVec2<T> xy() const
				{
					return iVec2<T>(x, y);
				}


				iVec2<T> xz() const
				{
					return iVec2<T>(x, z);
				}


				iVec2<T> yz() const
				{
					return iVec2<T>(y, z);
				}


				iVec3 yzx() const
				{
					return iVec3<T>(y, z, x);
				}


				Ref<iVec3<T>> operator ++ ()
				{
					++x;
					++y;
					++z;
					return *this;
				}


				Ref<iVec3<T>> operator -- ()
				{
					--x;
					--y;
					--z;
					return *this;
				}


				iVec3<T> operator ++ (int)
				{
					iVec3<T> tmp = *this;
					++* this;
					return tmp;
				}


				iVec3<T> operator -- (int)
				{
					iVec3<T> tmp = *this;
					--* this;
					return tmp;
				}


				void operator += (CRef<T> a)
				{
					x += a;
					y += a;
					z += a;
				}


				void operator += (CRef<iVec3<T>> v)
				{
					x += v.x;
					y += v.y;
					z += v.z;
				}


				void operator -= (CRef<T> a)
				{
					x -= a;
					y -= a;
					z -= a;
				}


				void operator -= (CRef<iVec3<T>> v)
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
				}


				bool operator == (CRef<T> a)
				{
					return (x == a) && (y == a) && (z == a);
				}


				bool operator == (CRef<iVec3<T>> v)
				{
					return (x == v.x) && (y == v.y) && (z == v.z);
				}


				bool operator != (CRef<T> a)
				{
					return (x != a) || (y != a) || (z != a);
				}


				bool operator != (CRef<iVec3<T>> v)
				{
					return (x != v.x) || (y != v.y) || (z != v.z);
				}


				void operator *= (CRef<T> a)
				{
					x *= a;
					y *= a;
					z *= a;
				}


				void operator *= (CRef<iVec3<T>> v)
				{
					x *= v.x;
					y *= v.y;
					z *= v.z;
				}


				void operator /= (CRef<T> a)
				{
					x /= a;
					y /= a;
					z /= a;
				}


				void operator /= (CRef<iVec3<T>> v)
				{
					x /= v.x;
					y /= v.y;
					z /= v.z;
				}


				T length() const
				{
					return (T)sqrt(lengthSquared());
				}


				T lengthSquared() const
				{
					return x * x + y * y + z * z;
				}


				T normalize()
				{
					T _length = length();
					if (_length < (T)1e-5)
					{
						return (T)0;
					}
					T _invLength = (T)1 / _length;
					x *= _invLength;
					y *= _invLength;
					z *= _invLength;
					return _length;
				}


				iVec3<T> GetNormalized() const
				{
					iVec3<T> n = iVec3<T>(x, y, z);
					n.normalize();
					return n;
				}


				T sum() const
				{
					return x + y + z;
				}



				T sumAbs() const
				{
					return abs<T>(x) +
						abs<T>(y) +
						abs<T>(z);
				}


				bool emptyAND() const
				{
					return x == (T)0 && y == (T)0 && z == (T)0;
				}


				bool emptyOR() const
				{
					return x == (T)0 || y == (T)0 || z == (T)0;
				}


				data::text::istring toIstring(CRef<char> c = ';') const
				{
					return (std::to_string(x) + c
						+ std::to_string(y) + c
						+ std::to_string(z));
				}


				T mini() const
				{
					return internalMini<T>(x, internalMini<T>(y, z));
				}


				T maxi() const
				{
					return internalMaxi<T>(x, internalMaxi<T>(y, z));
				}


			public:
				T x, y, z;
			};//class iVec3 

			template <typename T>
			inline Ref<iVec3<T>> operator ++ (Ref<iVec3<T>>v)
			{
				++v;
				return v;
			}


			template <typename T>
			inline Ref<iVec3<T>> operator -- (Ref<iVec3<T>>v)
			{
				--v;
				return v;
			}


			template <typename T>
			inline iVec3<T> operator ++ (Ref<iVec3<T>>v, int)
			{
				iVec3<T> a = v;
				++a;
				return a;
			}


			template <typename T>
			inline iVec3<T> operator -- (Ref<iVec3<T>>v, int)
			{
				iVec3<T> a = v;
				--a;
				return a;
			}


			template <typename T>
			inline iVec3<T> operator + (iVec3<T> v, T f)
			{
				return iVec3<T>(v.x + f, v.y + f, v.z + f);
			}


			template <typename T>
			inline iVec3<T> operator + (iVec3<T> v, iVec3<T> f)
			{
				return iVec3<T>(v.x + f.x, v.y + f.y, v.z + f.z);
			}


			template <typename T>
			inline iVec3<T> operator + (T f, iVec3<T> v)
			{
				return iVec3<T>(f + v.x, f + v.y, f + v.z);
			}


			template <typename T>
			inline iVec3<T> operator - (iVec3<T> v, T f)
			{
				return iVec3<T>(v.x - f, v.y - f, v.z - f);
			}


			template <typename T>
			inline iVec3<T> operator - (iVec3<T> v, iVec3<T> f)
			{
				return iVec3<T>(v.x - f.x, v.y - f.y, v.z - f.z);
			}


			template <typename T>
			inline iVec3<T> operator - (T f, iVec3<T> v)
			{
				return iVec3<T>(f - v.x, f - v.y, f - v.z);
			}


			template <typename T>
			inline iVec3<T> operator * (iVec3<T> v, T f)
			{
				return iVec3<T>(v.x * f, v.y * f, v.z * f);
			}


			template <typename T>
			inline iVec3<T> operator * (iVec3<T> v, iVec3<T> f)
			{
				return iVec3<T>(v.x * f.x, v.y * f.y, v.z * f.z);
			}


			template <typename T>
			inline iVec3<T> operator * (T f, iVec3<T> v)
			{
				return iVec3<T>(f * v.x, f * v.y, f * v.z);
			}


			template <typename T>
			inline iVec3<T> operator / (iVec3<T> v, T f)
			{
				return iVec3<T>(v.x / f, v.y / f, v.z / f);
			}


			template <typename T>
			inline iVec3<T> operator / (T f, iVec3<T> v)
			{
				return iVec3<T>(f / v.x, f / v.y, f / v.z);
			}


			template <typename T>
			inline iVec3<T> operator / (iVec3<T> v, iVec3<T> f)
			{
				return iVec3<T>(v.x / f.x, v.y / f.y, v.z / f.z);
			}


			template <typename T>
			inline bool operator < (iVec3<T> v, iVec3<T> f)
			{
				return v.x < f.x && v.y < f.y && v.z < f.z;
			}


			template <typename T>
			inline bool operator < (iVec3<T> v, T f)
			{
				return v.x < f && v.y < f && v.z < f;
			}


			template <typename T>
			inline bool operator > (iVec3<T> v, iVec3<T> f)
			{
				return v.x > f.x && v.y > f.y && v.z > f.z;
			}


			template <typename T>
			inline bool operator > (iVec3<T> v, T f)
			{
				return v.x > f && v.y > f && v.z > f;
			}


			template <typename T>
			inline bool operator <= (iVec3<T> v, iVec3<T> f)
			{
				return v.x <= f.x && v.y <= f.y && v.z <= f.z;
			}


			template <typename T>
			inline bool operator <= (iVec3<T> v, T f)
			{
				return v.x <= f && v.y <= f && v.z <= f;
			}


			template <typename T>
			inline bool operator >= (iVec3<T> v, iVec3<T> f)
			{
				return v.x >= f.x && v.y >= f.y && v.z >= f.z;
			}


			template <typename T>
			inline bool operator >= (iVec3<T> v, T f)
			{
				return v.x >= f && v.y >= f && v.z >= f;
			}


			template <typename T>
			inline bool operator != (iVec3<T> v, iVec3<T> f)
			{
				return f.x != v.x || f.y != v.y || f.z != v.z;
			}


			template <typename T>
			inline bool operator == (iVec3<T> v, iVec3<T> f)
			{
				return f.x == v.x && f.y == v.y && f.z == v.z;
			}


			template <typename T>
			inline iVec3<T> mini(iVec3<T> a, iVec3<T> b)
			{
				return iVec3<T>(
					mini<T>(a.x, b.x),
					mini<T>(a.y, b.y),
					mini<T>(a.z, b.z));
			}


			template <typename T>
			inline iVec3<T> maxi(iVec3<T> a, iVec3<T> b)
			{
				return iVec3<T>(
					maxi<T>(a.x, b.x),
					maxi<T>(a.y, b.y),
					maxi<T>(a.z, b.z));
			}


			template <typename T>
			inline iVec3<T> floor(iVec3<T> a)
			{
				return iVec3<T>(
					floor<T>(a.x),
					floor<T>(a.y),
					floor<T>(a.z));
			}


			template <typename T>
			inline iVec3<T> ceil(iVec3<T> a)
			{
				return iVec3<T>(
					ceil<T>(a.x),
					ceil<T>(a.y),
					ceil<T>(a.z));
			}


			template <typename T>
			inline iVec2<T> abs(iVec2<T> a)
			{
				return iVec2<T>(abs<T>(a.x),
					abs<T>(a.y));
			}


			template <typename T>
			inline iVec3<T> abs(iVec3<T> a)
			{
				return iVec3<T>(
					abs<T>(a.x),
					abs<T>(a.y),
					abs<T>(a.z));
			}


			template <typename T>
			inline T dotS(iVec3<T> a, iVec3<T> b)
			{
				return a.x * b.x + a.y * b.y + a.z * b.z;
			}


			template <typename T>
			inline iVec3<T> cCross(iVec3<T> a, iVec3<T> b)
			{
				return iVec3<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
			}


			template <typename T>
			inline iVec3<T> cReflect(iVec3<T> I, iVec3<T> N)
			{
				return I - (T)2 * dotS(N, I) * N;
			}


			using diVec3 = iVec3<double>;
			using fiVec3 = iVec3<float>;
			using biVec3 = iVec3<bool>;
			using iiVec3 = iVec3<int>;
			using i8iVec3 = iVec3<int8_t>;
			using i16iVec3 = iVec3<int16_t>;
			using iiVec3 = iVec3<int32_t>;
			using i32iVec3 = iVec3<int32_t>;
			using i64iVec3 = iVec3<int64_t>;
			using u8iVec3 = iVec3<uint8_t>;
			using u16iVec3 = iVec3<uint16_t>;
			using uiVec3 = iVec3<uint32_t>;
			using u32iVec3 = iVec3<uint32_t>;
			using u64iVec3 = iVec3<uint64_t>;


			inline bool valid(CRef<fiVec3> a)
			{
				return floatIsValid(a.x) &&
					floatIsValid(a.y) &&
					floatIsValid(a.z);
			}


			inline bool operator == (CRef<fiVec3> v, CRef<fiVec3> f)
			{
				return IS_FLOAT_EQUAL(f.x, v.x) &&
					IS_FLOAT_EQUAL(f.y, v.y) &&
					IS_FLOAT_EQUAL(f.z, v.z);
			}


			inline bool operator != (CRef<fiVec3> v, CRef<fiVec3> f)
			{
				return IS_FLOAT_DIFFERENT(f.x, v.x) ||
					IS_FLOAT_DIFFERENT(f.y, v.y) ||
					IS_FLOAT_DIFFERENT(f.z, v.z);
			}


		}//SPACE(math)
	}//SPACE(core)
}//SPACE(i)

#ifdef INCLUDE_NLOHMANN_JSON_HPP_

SPACE(nlohmann)
{

	template<class _T>
	inline void to_json(_ISTD Ref<nlohmann::json> j, _ISTD CRef<_ISTD math::iVec3<_T>> value)
	{
		json buff{
			{"x",value.x },
			{"y",value.y },
			{"z",value.z }
		};
		j = buff;
	}

	template<class _T>
	inline void from_json(_ISTD CRef<nlohmann::json> j, _ISTD Ref<_ISTD math::iVec3<_T>>value)
	{
		value.x = j["x"].get<_T>();
		value.y = j["y"].get<_T>();
		value.z = j["z"].get<_T>();
	}

}

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_
