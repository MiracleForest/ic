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
#include <icore/basic/iBasicDataType.h>
#include <icore/data/text/iJson.h>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(data)
		{
			SPACE(text)
			{

				class IAPI iChar :
					public basic::iBasicDataType<iChar, char>
				{
					iObject(iChar)
				public:

					iChar();

					iChar(char data);

					iChar(CPtr<char> data);

					iChar(CRef<iChar> ichar);

					iChar(CRef<std::string> str);

					~iChar();

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

					static bool isNum(CRef<iChar> ichar);

				public:

					bool isNum()const;

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

					Ref<iChar> operator+=(CRef<iChar> ichar)
					{
						_data += ichar.data();
						return *this;
					}

					Ref<iChar> operator-=(CRef<iChar> ichar)
					{
						_data -= ichar.data();
						return *this;
					}

					Ref<iChar> operator*=(CRef<iChar> ichar)
					{
						_data *= ichar.data();
						return *this;
					}

					Ref<iChar> operator/=(CRef<iChar> ichar)
					{
						_data /= ichar.data();
						return *this;
					}

					Ref<iChar> operator^=(CRef<iChar> ichar)
					{
						_data ^= ichar.data();
						return *this;
					}

					bool operator!=(CRef<iChar> ichar)
					{
						return (_data != ichar.data());
					}

					Ref<iChar> operator&=(CRef<iChar> ichar)
					{
						_data &= ichar.data();
						return *this;
					}

					Ref<iChar> operator|=(CRef<iChar> ichar)
					{
						_data |= ichar.data();
						return *this;
					}

					Ref<iChar> operator%=(CRef<iChar> ichar)
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
