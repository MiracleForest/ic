/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTCompoundExpressionNode.h
 * @创建时间:2023.10.21.19:32
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTCompoundExpressionNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iATSTypeNode.h"
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
			class ICAPI iASTCompoundExpressionNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				Ptr<iASTNode> expression;

			public:

				iASTCompoundExpressionNode();

				iASTCompoundExpressionNode(Ptr<iASTNode> pexpression);

				~iASTCompoundExpressionNode();

			public:

				[[nodiscard]] Ptr<iASTNode> getExpression()const noexcept;

				Ptr<iASTCompoundExpressionNode> setExpression(Ptr<iASTNode> pexpression);

			};

		}
	}
}