/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iFraction.hpp
* @创建时间：2023.1.10.22:29
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 分数类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

// ReSharper disable All
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>
#include <icore/data/text/istring.hpp>
#include <icore/math/iMath.hpp>


SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iFraction
				:public basic::iBasicDataType<iFraction, double>
			{

				using istring = data::text::istring;
				iObject(iFraction)

			public:

				iFraction() = default;

				iFraction(int i)
					:_numerator(i), _denominator(1)
				{ }

				iFraction(int a, int b)
					:_numerator(a / gcd(a, b)), _denominator(b / gcd(a, b))
				{
					if (_numerator > 0 && _denominator < 0)
					{
						_numerator = -_numerator;
						_denominator = -_denominator;
					}
				}

				iFraction(CRef<iFraction> f)
					:_numerator(f._numerator), _denominator(f._denominator)
				{ }

				iFraction(istring str)
				{
					std::list<std::string> nums = str.split2List("/");
					if (nums.size() == 1)
					{
						int num = 0;
						std::string s = *nums.begin();
						std::istringstream stream(s);
						stream >> num;
						_numerator = num;
						_denominator = 1;
					}
					else
					{
						int num = 0, den = 0;
						std::string s1 = *nums.begin();
						std::string s2 = *(++nums.begin());
						std::istringstream streamNum(s1);
						std::istringstream streamDen(s2);
						streamNum >> num;
						streamDen >> den;
						_numerator = num;
						_denominator = den;
					}
				}

			public:

				int getNumerator() const
				{
					return _numerator;
				}

				int getDenominator() const
				{
					return _denominator;
				}

				bool isNegative() const
				{
					return (this->_numerator < 0);
				}

			public:

				virtual double data() const
				{
					return _numerator / static_cast<double>(_denominator);
				}

			public:

				iFraction operator+(CRef<iFraction> f) const
				{
					return iFraction(this->_numerator * f._denominator + f._numerator * this->_denominator, this->_denominator * f._denominator);
				}

				iFraction operator-(CRef<iFraction> f) const
				{
					return iFraction(this->_numerator * f._denominator - f._numerator * this->_denominator, this->_denominator * f._denominator);
				}

				iFraction operator*(CRef<iFraction> f) const
				{
					return iFraction(this->_numerator * f._numerator, this->_denominator * f._denominator);
				}

				iFraction operator/(CRef<iFraction> f) const
				{
					return iFraction(this->_numerator * f._denominator, this->_denominator * f._numerator);
				}

				iFraction operator+(int n) const
				{
					return iFraction(this->_numerator + this->_denominator * n, this->_denominator);
				}

				iFraction operator-(int n) const
				{
					return iFraction(this->_numerator - this->_denominator * n, this->_denominator);
				}

				iFraction operator-() const
				{
					return iFraction(-this->_numerator, this->_denominator);
				}

				static llong exponentiationBySquaring4Int(int a, int b)
				{
					return (b == 1) ? a : (b == 2) ? (a * a) : (b & 1) ? (exponentiationBySquaring4Int(a * a, b / 2)) : (exponentiationBySquaring4Int(a * a, (b - 1) / 2) * a);
				}

				iFraction operator^(int n)
				{
					return iFraction(iFraction::exponentiationBySquaring4Int(this->_numerator, n), iFraction::exponentiationBySquaring4Int(this->_denominator, n));
				}

				bool operator<=>(CRef<iFraction> c)const;

				std::string toStdString()const
				{
					std::string s("");
					s.append(istring::toStdString(this->_numerator));
					if (this->_denominator != 1)
					{
						s.append("/");
						s.append(istring::toStdString(this->_denominator));
					}
					return s;
				}

				std::string toStdStringWithOperator()const
				{
					std::string s;
					if (!this->isNegative())
					{
						s = "+";
					}
					s.append(this->toStdString());
					return s;
				}

				friend std::ostream& operator<<(std::ostream& stream, CRef<iFraction> f)
				{
					stream << f._numerator << std::flush;
					if (f._denominator != 1)
					{
						stream << "/" << f._denominator << std::flush;
					}
					return stream;
				}

			private:
				int _numerator;
				int _denominator;
			};

		}
	}
}