/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iChar.hpp
* @创建时间：2022.12.31.23:01
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
*
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
//#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>
#include <icore/data/text/iJson.hpp>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(data)
		{
			SPACE(text)
			{

				class iChar :
					public basic::iBasicDataType<iChar, char>
				{
					iObject(iChar)
				public:

					iChar() :_data(0)
					{ }

					iChar(char data)
						:_data(data)
					{ }

					iChar(CPtr<char> data)
						:_data(data[0])
					{ }

					iChar(CRef<iChar> ichar)
						:_data(ichar.data())
					{ }

					iChar(CRef<std::string> str)
						:_data(str[0])
					{ }

					~iChar()
					{ }

				public:

				public:

					operator int()
					{
						return _data;
					}

					operator std::string()
					{
						return std::string(1, _data);
					}

				public:

					static bool isNum(CRef<iChar> ichar)
					{
						try
						{
							auto w = std::stod(std::string(1, ichar.data()));
							(void)w;
							return true;
						}
						catch (...)
						{
							return false;
						}
					}

				public:

					bool isNum()const
					{
						try
						{
							auto w = std::stod(std::string(1, this->_data));
							(void)w;
							return true;
						}
						catch (...)
						{
							return false;
						}
					}

				public:

					bool operator<=>(CRef<iChar>) const = default;

					void operator=(CRef<iChar> ichar)
					{
						_data = ichar.data();
					}

					bool operator==(CRef<iChar> ichar)const
					{
						return (_data == ichar.data());
					}

					bool operator>(CRef<iChar> ichar)const
					{
						return (_data > ichar.data());
					}

					bool operator<(CRef<iChar> ichar)const
					{
						return (_data < ichar.data());
					}

					bool operator>=(CRef<iChar> ichar)const
					{
						return (_data >= ichar.data());
					}

					bool operator<=(CRef<iChar> ichar)const
					{
						return (_data <= ichar.data());
					}

					bool operator!=(CRef<iChar> ichar)const
					{
						return (_data != ichar.data());
					}

					iChar operator+(CRef<iChar> ichar)
					{
						return (_data + ichar.data());
					}

					iChar operator-(CRef<iChar> ichar)
					{
						return (_data - ichar.data());
					}

					iChar operator*(CRef<iChar> ichar)
					{
						return (_data * ichar.data());
					}

					iChar operator%(CRef<iChar> ichar)
					{
						return (_data % ichar.data());
					}

					iChar operator/(CRef<iChar> ichar)
					{
						return (_data / ichar.data());
					}

					iChar operator|(CRef<iChar> ichar)
					{
						return (_data | ichar.data());
					}

					iChar operator~()
					{
						return (~_data);
					}

					iChar operator&(CRef<iChar> ichar)
					{
						return (_data & ichar.data());
					}

					iChar& operator+=(CRef<iChar> ichar)
					{
						_data += ichar.data();
						return *this;
					}

					iChar& operator-=(CRef<iChar> ichar)
					{
						_data -= ichar.data();
						return *this;
					}

					iChar& operator*=(CRef<iChar> ichar)
					{
						_data *= ichar.data();
						return *this;
					}

					iChar& operator/=(CRef<iChar> ichar)
					{
						_data /= ichar.data();
						return *this;
					}

					iChar& operator^=(CRef<iChar> ichar)
					{
						_data ^= ichar.data();
						return *this;
					}

					bool operator!=(CRef<iChar> ichar)
					{
						return (_data != ichar.data());
					}

					iChar& operator&=(CRef<iChar> ichar)
					{
						_data &= ichar.data();
						return *this;
					}

					iChar& operator|=(CRef<iChar> ichar)
					{
						_data |= ichar.data();
						return *this;
					}

					iChar& operator%=(CRef<iChar> ichar)
					{
						_data %= ichar.data();
						return *this;
					}

				public:

					char data()const
					{
						return _data;
					}

					void set(char _char)
					{
						_data = _char;
					}

				private:
					char _data;
				};

			}//SPACE(text)
		}//SPACE(data)
	}//SPACE(core)
}//SPACE(i)

SPACE(nlohmann)
{

}
