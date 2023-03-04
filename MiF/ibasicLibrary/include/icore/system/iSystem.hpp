/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iSystem.hpp
* @创建时间：2022.9.15.9:05
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 系统类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#ifdef __WINDOWS__
#define _USE_WINDOWS_H__
#endif

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>
SPACE(i)
{
	SPACE(core)
	{
		SPACE(System)
		{

			class iSystem
				: public basic::iBasic<iSystem>
			{
				using istring = data::text::istring;
				iObject(iSystem);
			public:

				iSystem()
				{ }


				~iSystem()
				{ }

			public:

				static bool is64bitOS()
				{
#ifdef __WINDOWS__
					typedef int(WINAPI* HWOW64)(handle, PBOOL);

					HMODULE hModule = GetModuleHandle(L"kernel32.dll");
					HWOW64 hwow64 = NULL;

					if (hModule == NULL)
						return false;
					else if ((hwow64 = (HWOW64)GetProcAddress(hModule, "IsWow64Process")) == NULL)
						return false;
					else
						return true;
#endif
					// todo 2023-1-3 Linux下待实现
					return true;
				}

				static std::string getSystemLocaleName()
				{
#ifdef __WINDOWS__
					wchar_t buf[256] = { 0 };
					auto lcid = GetSystemDefaultLCID();
					GetSystemDefaultLocaleName(buf, lcid);
					auto str = istring::wstr2str(buf);
					std::replace(str.begin(), str.end(), '-', '_');
					return str;
#endif
					// todo 2023-1-3 Linux下待实现
					return "";
				}

				static inline bool isWine()
				{
#ifdef __WINDOWS__
					HMODULE ntdll = GetModuleHandle(L"ntdll.dll");
					if (!ntdll)
					{
						return false;
					}
					auto rtv = GetProcAddress(ntdll, "wine_get_version");
					if (rtv)
					{
						return true;
					}
					else
					{
						return false;
					}
#endif
					// todo 2023-1-3 Linux下待实现
					return false;
				}

				static bool isWineEnvironment()
				{
					static bool result = isWine();
					return result;
				}

			public:

			public:
			public:
			protected:
			private:

			};//class iSystem


		}//SPACE(System)
	}//SPACE(core)
}//SPACE(i)