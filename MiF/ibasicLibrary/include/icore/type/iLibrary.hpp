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
#include <icore/data/text/istring.hpp>
#include <icore/type/iVersion.hpp>
#include <icore/type/iLevel.hpp>
#include <icore/exception/error.hpp>
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

		class iLibrary
			: public i::core::basic::iBasic<iLibrary>
		{
			using istring = data::text::istring;
			iObject(iLibrary);
		public:
			ECLASS(LibraryType) :int
			{
				unk,
					dll,
					so
			};
		public:

			iLibrary()
				:library({})
			{ }

			iLibrary(Library _library)
				:library(_library)
			{ }

			iLibrary(CRef<istring> libfname)
				:library({ .filename = libfname })
			{ }

			~iLibrary()
			{
				if (library._handle)
				{
					free();
				}
			}

		public:

			_iError load()
			{
				if (!(library.filename == ""))
				{
					library._handle = LoadLibrary(istring::str2wstr(library.filename.data()).data());
					if (!library._handle)
					{
						return _iError::make(iexception::ErrorCode::loadDynamicLinkLibraryFailed, std::source_location::current());
					}
					return _iError::noError();
				}
				else
				{
					return _iError::make(iexception::ErrorCode::loadDynamicLinkLibraryFailed_theTargetLibraryIsCalledEmpty, std::source_location::current());
				}
			}

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

			_iError free()
			{
				if (library._handle)
				{
					FreeLibrary((HMODULE)library._handle);
					return _iError::noError();
				}
				else
				{
					return _iError::make(_iErrorCode::theDynamicLinkLibraryHasBeenFreed, std::source_location::current());
				}
			}

		public:

			Library data() const
			{
				return library;
			}

			Library get() const
			{
				return library;
			}

			void set(Library _library)
			{
				library = _library;
			}

			void setLibrary(Library _library)
			{
				library = _library;
			}


		public:


		public:

		public:
		protected:
		private:
			Library library;
		};//class Library

	}//SPACE(core)
}//SPACE(i)
