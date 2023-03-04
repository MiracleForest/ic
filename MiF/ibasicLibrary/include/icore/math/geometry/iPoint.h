/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @�ļ�����iPoint.hpp
* @����ʱ�䣺2023.1.17.19:50
* @�����ߣ�Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary ��
* -----------------------------------------------------------------------------
* ����㷢����bug�������ȥGithub������(MiracleForest@Outlook.com)���������ǣ�
* ����һ����Ŭ�����ø��õģ�
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