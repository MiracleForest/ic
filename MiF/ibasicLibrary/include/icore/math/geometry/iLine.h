/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @�ļ�����iPoint.hpp
* @����ʱ�䣺2023.1.17.19:50
* @�����ߣ�Minsecrus
* -----------------------------------------------------------------------------
* iBasicLibrary ֱ��
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
#include "iPoint.h"

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iLine :
				public basic::iBasicDataType<iLine, std::pair<int, int>>
			{
				iObject(iLine);
			public:
				bool canPass(iPoint p);
			private:
				int _A;
				int _B;
				int _C;
			};

		}
	}
}