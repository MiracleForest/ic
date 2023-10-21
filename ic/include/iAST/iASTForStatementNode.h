/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTForStatementNode.h
 * @创建时间:2023.10.21.19:43
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTForStatementNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iATSTypeNode.h"
#include "iASTCompoundExpressionNode.h"
#include "iATSVariableDefinitionNode.h"
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
			class ICAPI iASTForStatementNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				 Ptr<iATSVariableDefinitionNode> loopDefineVariable;
				 Ptr<iASTCompoundExpressionNode> loopCondition;
				 Ptr<iASTNode> eachLoopExecute;

			public:

				iASTForStatementNode();

				iASTForStatementNode( Ptr<iATSVariableDefinitionNode> ploopDefineVariable,  Ptr<iASTCompoundExpressionNode> ploopCondition,  Ptr<iASTNode> peachLoopExecute);

				~iASTForStatementNode();

			public:

				[[nodiscard]]  Ptr<iASTNode> getLoopsDefineVariable()const noexcept;
				[[nodiscard]]  Ptr<iASTNode> getLoopCondition()const noexcept;
				[[nodiscard]]  Ptr<iASTNode> getEachLoopExecute()const noexcept;

				 Ptr<iASTForStatementNode> getLoopsDefineVariable( Ptr<iASTNode> ploopDefineVariable);
				 Ptr<iASTForStatementNode> getLoopCondition( Ptr<iASTNode> ploopCondition);
				 Ptr<iASTForStatementNode> getEachLoopExecute( Ptr<iASTNode> peachLoopExecute);

			};

		}
	}
}