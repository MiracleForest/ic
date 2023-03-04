/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：vec4.hpp
* @创建时间：2022.5.22.12:17
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* iVec4类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#pragma warning(disable:4305)

#include <icore/family/imacrofamily.h>
#include <icore/math/iVec3.hpp>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{

			template <typename T>
			class iVec4
				:public basic::iBasicDataType<iVec4<T>, std::tuple<T, T, T, T>>
			{
				using istring = data::text::istring;
				iObject(iVec4);
			public:

				iVec4() : x((T)0), y((T)0), z((T)0), w((T)0)
				{ }

				template <typename U>
				iVec4<T>(iVec4<U> a)
				{
					x = (T)a.x;
					y = (T)a.y;
					z = (T)a.z;
					w = (T)a.w;
				}

				iVec4(iVec2<T> xy, iVec2<T> zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y)
				{ }

				iVec4(iVec3<T> xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
				{ }

				iVec4(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw)
				{ }

				iVec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
				{ }

				iVec4(istring vec, char c = ';', Ptr<iVec4<T>> def = nullptr)
				{
					if (def)
					{
						x = def->x;
						y = def->y;
						z = def->z;
						w = def->w;
					}
					::std::vector<T> result = stringToNumberVector<T>(vec.data(), c);
					const size_t s = result.size();
					if (s > 0) x = result[0];
					if (s > 1) y = result[1];
					if (s > 2) z = result[2];
					if (s > 3) w = result[3];
				}

				iVec4(istring vec, char c = ';', int n = 4, Ptr<iVec4<T>> def = nullptr)
				{
					if (def)
					{
						x = def->x;
						y = def->y;
						z = def->z;
						w = def->w;
					}
					else
					{
						x = (T)0;
						y = (T)0;
						z = (T)0;
						w = (T)0;
					}
					::std::vector<T> result = stringToNumberVector<T>(vec.data(), c);
					const size_t s = result.size();
					if ((int)s != n)
					{
						if (s == 1)
						{
							x = result[0];
							y = result[0];
							z = result[0];
							w = result[0];
						}
						if (s == 2)
						{
							x = result[0];
							y = result[0];
							z = result[1];
							w = result[1];
						}
					}
					else
					{
						if (s > 0) x = result[0];
						if (s > 1) y = result[1];
						if (s > 2) z = result[2];
						if (s > 3) w = result[3];
					}
				}

				~iVec4()
				{ }

			public:

				virtual std::tuple<T, T, T, T> data()const
				{
					return std::make_tuple(x, y, z, w);
				}

			public:


				Ref<T> operator [] (CRef<size_t> i)
				{
					return (&x)[i];
				}


				iVec4<T> offset(CRef<T> vX, CRef<T> vY, CRef<T> vZ, CRef<T> vW) const
				{
					return iVec4<T>(x + vX, y + vY, z + vZ, w + vW);
				}


				void set(CRef<T> vX, CRef<T> vY, CRef<T> vZ, CRef<T> vW)
				{
					x = vX; y = vY; z = vZ; w = vW;
				}


				iVec4<T> operator -() const
				{
					return iVec4<T>(-x, -y, -z, -w);
				}


				iVec4<T> operator !() const
				{
					return iVec4<T>(!x, !y, !z, !w);
				}


				iVec2<T> xy() const
				{
					return iVec2<T>(x, y);
				}


				iVec3<T> xyz() const
				{
					return iVec3<T>(x, y, z);
				}


				iVec2<T> zw() const
				{
					return iVec2<T>(z, w);
				}


				Ref<iVec4<T>> operator ++ ()
				{
					++x;
					++y;
					++z;
					++w;
					return *this;
				}


				Ref<iVec4<T>> operator -- ()
				{
					--x;
					--y;
					--z;
					--w;
					return *this;
				}


				iVec4<T> operator ++ (int)
				{
					iVec4<T> tmp = *this;
					++* this;
					return tmp;
				}


				iVec4<T> operator -- (int)
				{
					iVec4<T> tmp = *this;
					--* this;
					return tmp;
				}


				void operator += (CRef<T> a)
				{
					x += a;
					y += a;
					z += a;
					w += a;
				}


				void operator += (Ref<iVec4<T>> v)
				{
					x += v.x;
					y += v.y;
					z += v.z;
					w += v.w;
				}


				void operator -= (CRef<T> a)
				{
					x -= a;
					y -= a;
					z -= a;
					w -= a;
				}


				void operator -= (Ref<iVec4<T>> v)
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
					w -= v.w;
				}


				bool operator == (CRef<T> a)
				{
					return (x == a) && (y == a) && (z == a) && (w == a);
				}


				bool operator == (Ref<iVec4<T>> v)
				{
					return (x == v.x) &&
						(y == v.y) &&
						(z == v.z) &&
						(w == v.w);
				}


				bool operator != (CRef<T> a)
				{
					return (x != a) || (y != a) || (z != a) || (w != a);
				}


				bool operator != (Ref<iVec4<T>> v)
				{
					return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
				}


				void operator *= (CRef<T> a)
				{
					x *= a;
					y *= a;
					z *= a;
					w *= a;
				}


				void operator *= (Ref<iVec4<T>> v)
				{
					x *= v.x;
					y *= v.y;
					z *= v.z;
					w *= v.w;
				}


				void operator /= (CRef<T> a)
				{
					x /= a;
					y /= a;
					z /= a;
					w /= a;
				}


				void operator /= (Ref<iVec4<T>> v)
				{
					x /= v.x;
					y /= v.y;
					z /= v.z;
					w /= v.w;
				}


				iVec2<T> sizeLBRT() const
				{
					return iVec2<T>(z - x, w - y);
				}


				iVec2<T> pos() const
				{
					return xy();
				}


				iVec2<T> size() const
				{
					return zw();
				}


				T length() const
				{
					return (T)sqrt(lengthSquared());
				}


				T lengthSquared() const
				{
					return x * x + y * y + z * z + w * w;
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
					w *= _invLength;
					return _length;
				}


				iVec4<T> getNormalized() const
				{
					iVec4<T> n = iVec4<T>(x, y, z, w);
					n.normalize();
					return n;
				}


				bool emptyAND() const
				{
					return x == (T)0 &&
						y == (T)0 &&
						z == (T)0 &&
						w == (T)0;
				}


				bool emptyOR() const
				{
					return x == (T)0 ||
						y == (T)0 ||
						z == (T)0 ||
						w == (T)0;
				}


				T sum() const
				{
					return x + y + z + w;
				}


				T sumAbs() const
				{
					return abs<T>(x) +
						abs<T>(y) +
						abs<T>(z) +
						abs<T>(w);
				}


				istring string(char c = ';') const
				{
					return (std::to_string(x) + c +
						std::to_string(y) + c +
						std::to_string(z) + c +
						std::to_string(w));
				}


				T mini() const
				{
					return internalMini<T>(
						x, internalMini<T>(
							y, internalMini<T>(
								z, w)
						)
					);
				}


				T maxi() const
				{
					return internalMaxi<T>(
						x, internalMaxi<T>(
							y, internalMaxi<T>(
								z, w)
						)
					);
				}


			public:
				T x, y, z, w;
			};//class iVec4 


			template <typename T>
			inline Ref<iVec4<T>> operator ++ (Ref<iVec4<T>> v)
			{
				++v;
				return v;
			}


			template <typename T>
			inline Ref<iVec4<T>> operator -- (Ref<iVec4<T>> v)
			{
				--v;
				return v;
			}


			template <typename T>
			inline iVec4<T> operator ++ (Ref<iVec4<T>> v, int)
			{
				iVec4<T> a = v;
				++a;
				return a;
			}


			template <typename T>
			inline iVec4<T> operator -- (Ref<iVec4<T>> v, int)
			{
				iVec4<T> a = v;
				--a;
				return a;
			}


			template <typename T>
			inline iVec4<T> operator + (iVec4<T> v, T f)
			{
				return iVec4<T>(v.x + f,
					v.y + f,
					v.z + f,
					v.w + f);
			}


			template <typename T>
			inline iVec4<T> operator + (iVec4<T> v, iVec4<T> f)
			{
				return iVec4<T>(v.x + f.x,
					v.y + f.y,
					v.z + f.z,
					v.w + f.w);
			}


			template <typename T>
			inline iVec4<T> operator - (iVec4<T> v, T f)
			{
				return iVec4<T>(v.x - f,
					v.y - f,
					v.z - f,
					v.w - f);
			}


			template <typename T>
			inline iVec4<T> operator - (T f, iVec4<T> v)
			{
				return iVec4<T>(f - v.x,
					f - v.y,
					f - v.z,
					f - v.w);
			}


			template <typename T>
			inline iVec4<T> operator - (iVec4<T> v, iVec4<T> f)
			{
				return iVec4<T>(v.x - f.x,
					v.y - f.y,
					v.z - f.z,
					v.w - f.w);
			}


			template <typename T>
			inline iVec4<T> operator * (iVec4<T> v, T f)
			{
				return iVec4<T>(v.x * f,
					v.y * f,
					v.z * f,
					v.w * f);
			}


			template <typename T>
			inline iVec4<T> operator * (iVec4<T> v, iVec4<T> f)
			{
				return iVec4<T>(v.x * f.x,
					v.y * f.y,
					v.z * f.z,
					v.w * f.w
				);
			}


			template <typename T>
			inline iVec4<T> operator / (iVec4<T> v, T f)
			{
				return iVec4<T>(v.x /
					f, v.y /
					f, v.z /
					f, v.w /
					f);
			}


			template <typename T>
			inline iVec4<T> operator / (iVec4<T> v, iVec4<T> f)
			{
				return iVec4<T>(v.x /
					f.x, v.y /
					f.y, v.z /
					f.z, v.w /
					f.w);
			}


			template <typename T>
			inline bool operator < (iVec4<T> v, iVec4<T> f)
			{
				return v.x < f.x &&
					v.y < f.y &&
					v.z < f.z &&
					v.w < f.w;
			}


			template <typename T>
			inline bool operator < (iVec4<T> v, T f)
			{
				return v.x < f &&
					v.y < f &&
					v.z < f &&
					v.w < f;
			}


			template <typename T>
			inline bool operator > (iVec4<T> v, iVec4<T> f)
			{
				return v.x > f.x &&
					v.y > f.y &&
					v.z > f.z &&
					v.w > f.w;
			}


			template <typename T>
			inline bool operator > (iVec4<T> v, T f)
			{
				return v.x > f &&
					v.y > f &&
					v.z > f &&
					v.w > f;
			}


			template <typename T>
			inline bool operator <= (iVec4<T> v, iVec4<T> f)
			{
				return v.x <= f.x &&
					v.y <= f.y &&
					v.z <= f.z &&
					v.w <= f.w;
			}


			template <typename T>
			inline bool operator <= (iVec4<T> v, T f)
			{
				return v.x <= f &&
					v.y <= f &&
					v.z <= f &&
					v.w <= f;
			}


			template <typename T>
			inline bool operator >= (iVec4<T> v, iVec4<T> f)
			{
				return v.x >= f.x &&
					v.y >= f.y &&
					v.z >= f.z &&
					v.w >= f.w;
			}


			template <typename T>
			inline bool operator >= (iVec4<T> v, T f)
			{
				return v.x >= f &&
					v.y >= f &&
					v.z >= f &&
					v.w >= f;
			}


			template <typename T>
			inline bool operator == (iVec4<T> v, iVec4<T> f)
			{
				return f.x == v.x &&
					f.y == v.y &&
					f.z == v.z &&
					f.w == v.w;
			}


			template <typename T>
			inline bool operator != (iVec4<T> v, iVec4<T> f)
			{
				return f.x != v.x ||
					f.y != v.y ||
					f.z != v.z ||
					f.w != v.w;
			}


			template <typename T>
			inline iVec4<T> mini(iVec4<T> a, iVec4<T> b)
			{
				return iVec4<T>(
					mini<T>(a.x, b.x),
					mini<T>(a.y, b.y),
					mini<T>(a.z, b.z),
					mini<T>(a.w, b.w)
				);
			}


			template <typename T>
			inline iVec4<T> maxi(iVec4<T> a, iVec4<T> b)
			{
				return iVec4<T>(
					maxi<T>(a.x, b.x),
					maxi<T>(a.y, b.y),
					maxi<T>(a.z, b.z),
					maxi<T>(a.w, b.w)
				);
			}


			template <typename T>
			inline iVec4<T> floor(iVec4<T> a)
			{
				return iVec4<T>(
					floor<T>(a.x),
					floor<T>(a.y),
					floor<T>(a.z),
					floor<T>(a.w)
				);
			}


			template <typename T>
			inline iVec4<T> ceil(iVec4<T> a)
			{
				return iVec4<T>(
					ceil<T>(a.x),
					ceil<T>(a.y),
					ceil<T>(a.z),
					ceil<T>(a.w)
				);
			}


			template <typename T>
			inline iVec4<T> abs(iVec4<T> a)
			{
				return iVec4<T>(
					abs<T>(a.x),
					abs<T>(a.y),
					abs<T>(a.z),
					abs<T>(a.w));
			}


			template <typename T>
			inline iVec4<T> sign(iVec4<T> a)
			{
				return iVec4<T>(
					a.x < (T)0 ? (T)-1 : (T)1,
					a.y < (T)0 ? (T)-1 : (T)1,
					a.z < (T)0 ? (T)-1 : (T)1,
					a.w < (T)0 ? (T)-1 : (T)1);
			}


			template <typename T>
			inline iVec4<T> sin(iVec4<T> a)
			{
				return iVec4<T>(
					sin<T>(a.x),
					sin<T>(a.y),
					sin<T>(a.z),
					sin<T>(a.w)
				);
			}


			template <typename T>
			inline iVec4<T> cos(iVec4<T> a)
			{
				return iVec4<T>(
					cos<T>(a.x),
					cos<T>(a.y),
					cos<T>(a.z),
					cos<T>(a.w)
				);
			}


			template <typename T>
			inline iVec4<T> tan(iVec4<T> a)
			{
				return iVec4<T>(
					tan<T>(a.x),
					tan<T>(a.y),
					tan<T>(a.z),
					tan<T>(a.w)
				);
			}


			using diVec4 = iVec4<double>;
			using fiVec4 = iVec4<float>;
			using biVec4 = iVec4<bool>;
			using iiVec4 = iVec4<int>;
			using i8iVec4 = iVec4<int8_t>;
			using i16iVec4 = iVec4<int16_t>;
			using iiVec4 = iVec4<int32_t>;
			using i32iVec4 = iVec4<int32_t>;
			using i64iVec4 = iVec4<int64_t>;
			using u8iVec4 = iVec4<uint8_t>;
			using u16iVec4 = iVec4<uint16_t>;
			using uiVec4 = iVec4<uint32_t>;
			using u32iVec4 = iVec4<uint32_t>;
			using u64iVec4 = iVec4<uint64_t>;



			inline bool valid(CRef<fiVec4> a)
			{
				return floatIsValid(a.x) &&
					floatIsValid(a.y) &&
					floatIsValid(a.z) &&
					floatIsValid(a.w);
			}


			inline bool operator == (CRef<fiVec4> v, CRef<fiVec4> f)
			{
				return IS_FLOAT_EQUAL(f.x, v.x) &&
					IS_FLOAT_EQUAL(f.y, v.y) &&
					IS_FLOAT_EQUAL(f.z, v.z) &&
					IS_FLOAT_EQUAL(f.w, v.w);
			}


			inline bool operator != (CRef<fiVec4> v, CRef<fiVec4> f)
			{
				return IS_FLOAT_DIFFERENT(f.x, v.x) ||
					IS_FLOAT_DIFFERENT(f.y, v.y) ||
					IS_FLOAT_DIFFERENT(f.z, v.z) ||
					IS_FLOAT_DIFFERENT(f.w, v.w);
			}

		}//SPACE(math)
	}//SPACE(core)
}//SPACE(i)

#ifdef INCLUDE_NLOHMANN_JSON_HPP_

SPACE(nlohmann)
{

	template<class _T>
	inline void to_json(_ISTD Ref<nlohmann::json> j, _ISTD CRef<_ISTD math::iVec4<_T>> value)
	{
		json buff{
			{"x",value.x },
			{"y",value.y },
			{"z",value.z },
			{"w",value.w }
		};
		j = buff;
	}

	template<class _T>
	inline void from_json(_ISTD CRef<nlohmann::json> j, _ISTD Ref<_ISTD math::iVec4<_T>>value)
	{
		value.x = j["x"].get<_T>();
		value.y = j["y"].get<_T>();
		value.z = j["z"].get<_T>();
		value.w = j["w"].get<_T>();
	}

}

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_