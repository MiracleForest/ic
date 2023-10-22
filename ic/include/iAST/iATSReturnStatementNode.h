/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSReturnStatementNode.h
 * @创建时间:2023.10.21.16:41
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iATSReturnStatementNode
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
	SPACE(icFamily)
	{
		SPACE(AST)
		{
			class ICAPI iATSReturnStatementNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				_ISTD Ptr<iASTNode> value;

			public:

				iATSReturnStatementNode();

				iATSReturnStatementNode(_ISTD Ptr<iASTNode> value);

				~iATSReturnStatementNode();

			public:

				[[nodiscard]] _ISTD Ptr<iASTNode> getReturnValue()const noexcept;
				_ISTD Ptr<iATSReturnStatementNode> setReturnValue(_ISTD Ptr<iASTNode> pvalue);

			};

		}
	}
}