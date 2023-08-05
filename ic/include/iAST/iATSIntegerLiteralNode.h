/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSIntegerLiteralNode.h
 * @创建时间:2022.7.21.17:42
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iATSIntegerLiteralNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/data/text/istring.h>
#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include "iASTNodeBasic.h"
#include "../family/iicfamily.h"

SPACE(i)
{
	SPACE(icSystem)
	{
		SPACE(AST)
		{
			class ICAPI iATSIntegerLiteralNode
				:public iASTNodeBasic
			{
				using istring = _ISTDTEXT istring;

			private:

				_ISTD int64 _data;

			public:

				iATSIntegerLiteralNode();

				iATSIntegerLiteralNode(_ISTD int64 data);

				~iATSIntegerLiteralNode();

			public:

				[[nodiscard]] _ISTD int64 get()const noexcept;

				_ISTD Ptr<iATSIntegerLiteralNode> set(_ISTD int64 data);
			};

		}
	}
}