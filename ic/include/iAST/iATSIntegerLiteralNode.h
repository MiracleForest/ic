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

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include <icore/console/iconsole.h>
#include <icore/console/iLogger.h>
#include <icore/data/text/istring.h>
#include <icore/exception/error.h>
#include <icore/family/imacrofamily.h>

SPACE(i)
{
	SPACE(icSystem)
	{
		SPACE(AST)
		{
			class ICAPI iATSIntegerLiteralNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				_ISTD int64 data;

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