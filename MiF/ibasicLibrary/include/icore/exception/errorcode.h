/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：errorcode.hpp
* @创建时间：2022.5.19.13:12
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i错误代码
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#include <icore/family/imacrofamily.h>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(iexception)
		{

			enum class ErrorCode
				: int
			{
				/************ -1 ~ -999 ************/
				unkError = -1,
				createErrorFailed = -3,


				/*^^^^^^^^^^^   -1 ~ -999   ^^^^^^^^^^^*/
				/////////////////////////////////////////
				/************ -1000 ~ -1099 ************/
				loadDynamicLinkLibraryFailed = -1000,
				loadDynamicLinkLibraryFailed_theTargetLibraryIsCalledEmpty = -1001,
				theDynamicLinkLibraryHasBeenFreed = -1002,


				/*^^^^^^^^^^^ -1000 ~ -1099 ^^^^^^^^^^^*/
				/////////////////////////////////////////
				/************ -1100 ~ -1199 ************/
				theIllegalInput = -1100,
				theIllegalFormatString = -1101,


				/*^^^^^^^^^^^ -1100 ~ -1199 ^^^^^^^^^^^*/
				/////////////////////////////////////////
				/************ -1200 ~ -1199 ************/
				failedToSetConsoleTitle = -1200,


				/*^^^^^^^^^^^ -1200 ~ -1299 ^^^^^^^^^^^*/
				/////////////////////////////////////////
				/************ -1300 ~ -1399 ************/
				failedToCreateFile = -1300,
				failedToRemoveFile = -1301

				/*^^^^^^^^^^^ -1300 ~ -1399 ^^^^^^^^^^^*/


			};//ECLASS(ErrorCode)

		}//SPACE(iexception)
	}//SPACE(core)
}//SPACE(i)


