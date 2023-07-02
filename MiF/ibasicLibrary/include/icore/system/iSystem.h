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

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>

#ifdef __WINDOWS__
#define _USE_WINDOWS_H__
#else//^^^^__WINDOWS__^^^^
#include <dlfcn.h>
#include <clocale>
#include <elf.h>
#endif//^^^^!__WINDOWS__^^^^

SPACE(i)
{
	SPACE(core)
	{
		SPACE(System)
		{

			class IAPI iSystem
				: public basic::iBasic<iSystem>
			{
				using istring = data::text::istring;
				iObject(iSystem);
			public:

				iSystem();

				~iSystem();

			public:

				/****
				*
				* @author Lovelylavender4
				* @since 2023.5.27.13:49
				* @brief 判断操作系统是否为64位
				*
				* @return 如果是64位操作系统返回true，否则返回false
				* @warning 此函数只适用于Linux和Windows操作系统
				*
				* @par 示例
				* @code
				* bool result = is64bitOS();
				* if (result == true) {
				* ...
				* }
				* @endcode
				* 
				* @details
				* 根据不同的操作系统调用对应的API进行判断。在Windows下使用IsWow64Process函数，在Linux下使用getauxval函数。
				* @enddetails
				****/
				static bool is64bitOS();

				/****
				* 
				* @author Lovelylavender4
				* @since 2023.5.27.13:42
				* @brief 获取系统语言区域名称
				* @return 包含系统语言区域名称
				*
				* @par 例子:
				* @code
				* istring localeName = getSystemLocaleName();
				* @endcode
				*
				* @details
				* 根据操作系统不同的方式获取系统默认LCID并通过LCID获取默认语言区域名称，
				* 然后将wchar_t数组转化为字符串，将横线替换为下划线，并返回结果。
				* 对于非Windows操作系统，则使用setlocale()来检查当前系统用户设置的本地化信息，
				* 将本地化信息转换为字符串，将横线替换为下划线，并返回结果。
				* @enddetails
				*
				****/
				static istring getSystemLocaleName();

				/****
				* 
				* @author Lovelylavender4
				* @since 2023.5.27.13:42
				* @brief 判断当前系统是否为Wine模拟环境
				*
				* @return 如果是Wine模拟环境则返回 true，否则返回 false
				* 
				****/
				static inline bool isWine();

				static bool isWineEnvironment();

			public:

			public:
			public:
			protected:
			private:

			};//class iSystem


		}//SPACE(System)
	}//SPACE(core)
}//SPACE(i)