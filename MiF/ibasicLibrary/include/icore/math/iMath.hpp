/*
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iMath.hpp
* @创建时间：2022.5.22.11:54
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 定义了一些关于数学的零散函数
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#pragma warning(disable:4244)

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
#include <math.h>
#include <numeric>
#include <numbers>



SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{

			constexpr static double MATH_PI = 3.141592653589793;
			constexpr static double MATH_E = 2.718281828459045;

			/****
			* @author Lovelylavender4
			* @since 2022.6.21.13:41
			* @brief 这个函数用来确保一个浮点数不是NaN或无穷大。
			*
			* @param f 浮点数
			* @retval 真或假
			*
			* @par 模板
			* @code
			* floatIsValid(aFloatNumber);
			* @endcode
			*
			* @details
			* 这个函数用来确保一个浮点数不是NaN或无穷大。
			* @enddetails
			****/
			inline bool floatIsValid(float x)
			{
				const union
				{
					float f;
					int32_t i;
				} v = { x };
				return (v.i & 0x7f800000) != 0x7f800000;
			}


			template <typename T>
			inline T round(CRef<T> v)
			{
				return (T)(std::round((double)v));
			}


			template <typename T>
			inline T floor(CRef<T> v)
			{
				return (T)(std::floor((double)v));
			}


			template <typename T>
			inline T ceil(CRef<T> v)
			{
				return (T)(std::ceil((double)v));
			}


			template <typename T>
			inline T fract(CRef<T> v)
			{
				return v - floor<T>(v);
			}


			template <typename T>
			inline T cos(CRef<T> v)
			{
				return std::cos(v);
			}


			template <typename T>
			inline T acos(CRef<T> v)
			{
				return std::acos(v);
			}


			template <typename T>
			inline T sin(CRef<T> v)
			{
				return std::sin(v);
			}


			template <typename T>
			inline T asin(CRef<T> v)
			{
				return std::asin(v);
			}


			template <typename T>
			inline T tan(CRef<T> v)
			{
				return std::tan(v);
			}


			template <typename T>
			inline T atan(CRef<T> v)
			{
				return std::atan(v);
			}


			template <typename T>
			inline T mini(CRef<T> a, CRef<T> b)
			{
				return a < b ? a : b;
			}


			template <typename T>
			inline T maxi(CRef<T> a, CRef<T> b)
			{
				return a > b ? a : b;
			}


			template <typename T>
			inline T internalMini(CRef<T> a, CRef<T> b)
			{
				return a < b ? a : b;
			}


			template <typename T>
			inline T internalMaxi(CRef<T> a, CRef<T> b)
			{
				return a > b ? a : b;
			}


			template <typename T>
			inline T clamp(CRef<T> n)
			{
				return n >= T(0) && n <= T(1) ? n : T(n > T(0));
			}


			template <typename T>
			inline T clamp(CRef<T> n, CRef<T> b)
			{
				return n >= T(0) && n <= b ? n : T(n > T(0)) * b;
			}


			template <typename T>
			inline T clamp(CRef<T> n, CRef<T> a, CRef<T> b)
			{
				return n >= a && n <= b ? n : n < a ? a : b;
			}


			template <typename T>
			inline T abs(CRef<T> a)
			{
				return a < 0 ? a * (T)-1 : a;
			}


			template <typename T>
			inline T sign(CRef<T> a)
			{
				return a < 0 ? (T)-1 : (T)1;
			}


			template <typename T>
			inline T step(CRef<T> a, CRef<T> b)
			{
				return b < a ? (T)0 : (T)1;
			}


			template <typename T>
			inline T mod(CRef<T> v, CRef<T> l)
			{
				return std::modf(v, l);
			}


			template <typename T>
			inline T invMix(CRef<T> i, CRef<T> s, CRef<T> r)
			{
				return (r - i) / (s - i);
			}


			template <typename T>
			inline T lerp(CRef<T> a, CRef<T> b, CRef<T> t)
			{
				return a * (1.0f - t) + b * t;
			}


			template <typename T>
			inline T eerp(CRef<T> a, CRef<T> b, CRef<T> t)
			{
				if (a == (T)0) return T(0);
				return pow(a * (b / a), t);
			}


			template <typename T>
			inline T mix(CRef<T> a, CRef<T> b, CRef<T> t)
			{
				return lerp(a, b, t);
			}


			template <typename T>
			inline T stringToNumber(CRef<std::string> text)
			{
				T value = (T)0;
				std::stringstream ss(text);
				ss >> value;
				return value;
			}


			template <typename T>
			inline std::vector<T> stringToNumberVector(CRef<std::string> text, char delimiter)
			{
				std::vector<T> arr;
				std::string::size_type start = 0;
				std::string::size_type end = text.find(delimiter, start);
				while (end != std::string::npos)
				{
					std::string token = text.substr(start, end - start);
					arr.emplace_back(stringToNumber<T>(token));
					start = end + 1;
					end = text.find(delimiter, start);
				}
				arr.emplace_back(stringToNumber<T>(text.substr(start).c_str()));
				return arr;
			}

			/****
			* @author Lovelylavender4
			* @since 2022.8.29.19:14
			* @brief 找到最小的值x >= a，使x % k == 0。
			*
			* @param a
			* @param k
			*
			****/
			inline int roundUp(int a, int k)
			{
				return ((a + k - 1) / k) * k;
			}

			/****
			* @author Lovelylavender4
			* @since 2022.8.29.19:13
			* @brief 计算a和b的最大公除数
			*
			* @param f
			*
			****/
			template<typename T>
			inline static T gcd(T a, T b)
			{
				T c = a % b;
				while (c != 0)
				{
					a = b;
					b = c;
					c = a % b;
				}
				return b;
			}


			inline int binary2Num(CRef<std::vector<double>> vector_in)
			{
				int value_out = 0;
				for (int i = 0; i < static_cast<int>(vector_in.size()); ++i)
				{
					value_out += vector_in.at(i) * std::pow(2, i);
				}
				return value_out;
			}

			inline double average(CRef<std::vector<double>> vector_in)
			{
				return std::accumulate(vector_in.begin(), vector_in.end(), 0.0) / static_cast<double>(vector_in.size());
			}

			inline double modulus(const double value_in, const double modulus, const bool normalize)
			{
				double value_out = std::fmod(value_in, modulus);
				if (normalize && value_out < 0.0)
				{
					value_out += modulus;
				}
				return value_out;
			}

			inline double distanceAngular(const double pos_1, const double pos_2, const double modulus1)
			{
				double value_out = (modulus1 * 1.5) + (pos_2 - pos_1);
				value_out = modulus(value_out, modulus1, true) - (modulus1 / 2.0);
				return value_out;
			}

			inline double distanceLinear(CRef<std::vector<double>> pos_1, CRef<std::vector<double>> pos_2)
			{
				if (pos_1.size() != pos_2.size())
				{
					return std::numeric_limits<double>::quiet_NaN();
				}
				double value_out = 0.0;
				for (int i = 0; i < static_cast<int>(pos_1.size()); ++i)
				{
					value_out += std::pow(pos_2.at(i) - pos_1.at(i), 2.0);
				}
				return std::sqrt(value_out);
			}

			inline double mathNearestAngle(double pos_target, const double pos_current, const double modulus)
			{
				pos_target = i::core::math::modulus(pos_target, modulus, false) + (modulus * std::round(pos_current / modulus));
				while (pos_target - pos_current < -1.0 * modulus / 2.0)
				{
					pos_target += modulus;
				}
				while (pos_target - pos_current > modulus / 2.0)
				{
					pos_target -= modulus;
				}
				return pos_target;
			}

			inline double pi()
			{
				return static_cast<double>(atan(1.0) * 4.0);
			}

			inline double standardDeviation(CRef<std::vector<double>> vector)
			{
				if (vector.empty())
				{
					return 0.0;
				}

				double sample_mean = average(vector);

				std::vector<double> vector_diff(vector.size());
				std::transform(vector.begin(), vector.end(), vector_diff.begin(), [sample_mean](double x)
					{
						return x - sample_mean;
					});

				double square_sum = std::inner_product(vector_diff.begin(), vector_diff.end(), vector_diff.begin(), 0.0);
				return std::sqrt(square_sum / (vector.size() - (vector.size() >= 2 ? 1 : 0)));
			}

			inline double toDegree(const double radian)
			{
				return static_cast<double>(radian * 180.0 / pi());
			}

			inline double toRadian(const double degree)
			{
				return static_cast<double>(degree * pi() / 180.0);
			}

			inline std::vector<bool> toBinary(int value)
			{
				std::vector<bool> vector_out;
				while (value > 0.0)
				{
					vector_out.push_back(modulus(value, 2.0, true) > 0.0);
					if (vector_out.back())
					{
						--value;
					}
					value /= 2.0;
				}
				return vector_out;
			}

			inline constexpr float degreesToRadians(float degrees)
			{
				return degrees * float(std::numbers::pi / 180);
			}

			inline constexpr double degreesToRadians(double degrees)
			{
				return degrees * (std::numbers::pi / 180);
			}

			inline constexpr long double degreesToRadians(long double degrees)
			{
				return degrees * (std::numbers::pi / 180);
			}

			template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
			inline constexpr double degreesToRadians(T degrees)
			{
				return degreesToRadians(static_cast<double>(degrees));
			}

			inline constexpr float radiansToDegrees(float radians)
			{
				return radians * float(180 / std::numbers::pi);
			}

			inline constexpr double radiansToDegrees(double radians)
			{
				return radians * (180 / std::numbers::pi);
			}

			inline constexpr long double radiansToDegrees(long double radians)
			{
				return radians * (180 / std::numbers::pi);
			}

			inline void swapInts(Ref<int> a, Ref<int>b)
			{
				a ^= b ^= a ^= b;
			}

		}//SPACE(math)
	}//SPACE(core)
}//SPACE(i)
