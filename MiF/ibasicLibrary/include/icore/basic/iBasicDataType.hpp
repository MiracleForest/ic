/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iBasicDataType.hpp
* @创建时间：2022.4.30.11:53
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 所有i数据类的基类
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>
#include <icore/type/type/type.hpp>
#include <icore/type/type/concepts.hpp>
#include <icore/basic/iBasic.hpp>
#include <functional>
#include <new>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(basic)
		{

			template<typename Type, typename dtrType>
			class iBasicDataType : public iBasic<Type>
			{
				virtual dtrType data()const = 0;

			};//class iBasicDataType


		}//SPACE(basic)
	}//SPACE(core)
}//SPACE(i)
