/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iPoint.hpp
* @创建时间：2023.1.17.19:50
* @创建者：Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary 点
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

#pragma once

#include "../../family/imacrofamily.h"
#include "../../basic/iBasicDatatype.hpp"
#include "../../basic/iBasic.hpp"
#include "../iMath.hpp"

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iLine;
		}
	}
}

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iPoint :
				public basic::iBasicDataType<iPoint, std::pair<int, int>>
			{
				iObject(iPoint);
			public:
				// virtual double distanceFromOrigin() const;
				virtual std::pair<int, int> data() const;
			public:
				bool isOnLine(iLine l);

			private:
				int _x;
				int _y;
			};

		}
	}
}