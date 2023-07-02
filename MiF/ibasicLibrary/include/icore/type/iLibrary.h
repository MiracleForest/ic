/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：library.hpp
* @创建时间：2022.7.15.12:12
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i动态库
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>
#include <icore/type/iVersion.h>
#include <icore/type/iLevel.h>
#include <icore/exception/error.h>
#include <functional>
#include <vector>
#include <map>


SPACE(i)
{
	SPACE(core)
	{


		struct Library
		{
			using istring = data::text::istring;

			istring filename = "";//库文件名
			istring name = "";//库名
			istring path = "";//库文件路径
			iVersion version = {};//版本
			handle _handle = nullptr;//句柄
			istring dscription = "";//描述
			type::iLevel _level = 0;// 等级
			std::map<int, std::pair<istring, istring>> others = { };//其他
		};

		class IAPI iLibrary
			: public i::core::basic::iBasic<iLibrary>
		{
			using istring = data::text::istring;
			iObject(iLibrary);
		public:
			enum class LibraryType :int
			{
				unk,
				dll,
				so
			};
		public:

			iLibrary();

			iLibrary(Library _library);

			iLibrary(CRef<istring> libfname);

			~iLibrary();

		public:

			_iError load();

			template <typename ReturnType = void, typename... Args>
			ReturnType call(CRef<istring> functionSymbol, Args... args)
			{
				void* address = GetProcAddress((HMODULE)library._handle, functionSymbol.cStr());
				if (!address)
				{
					return ReturnType();
				}
				return reinterpret_cast<ReturnType(*)(Args...)>(address)(std::forward<Args>(args)...);
			}

			_iError free();

		public:

			Library data() const;

			Library get() const;

			void set(Library _library);

			void setLibrary(Library _library);

		public:
		protected:
		private:
			Library library;
		};//class Library

	}//SPACE(core)
}//SPACE(i)
