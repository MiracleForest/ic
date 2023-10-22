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

				_ISTD Ptr<iATSVariableDefinitionNode> loopDefineVariable;
				_ISTD Ptr<iASTCompoundExpressionNode> loopCondition;
				_ISTD Ptr<iASTNode> eachLoopExecute;

			public:

				iASTForStatementNode();

				iASTForStatementNode(_ISTD Ptr<iATSVariableDefinitionNode> ploopDefineVariable, _ISTD Ptr<iASTCompoundExpressionNode> ploopCondition, _ISTD Ptr<iASTNode> peachLoopExecute);

				~iASTForStatementNode();

			public:

				[[nodiscard]] _ISTD Ptr<iATSVariableDefinitionNode> getLoopDefineVariable()const noexcept;
				[[nodiscard]] _ISTD Ptr<iASTCompoundExpressionNode> getLoopCondition()const noexcept;
				[[nodiscard]] _ISTD Ptr<iASTNode> getEachLoopExecute()const noexcept;

				_ISTD Ptr<iASTForStatementNode> getLoopsDefineVariable(_ISTD Ptr<iATSVariableDefinitionNode> ploopDefineVariable);
				_ISTD Ptr<iASTForStatementNode> getLoopCondition(_ISTD Ptr<iASTCompoundExpressionNode> ploopCondition);
				_ISTD Ptr<iASTForStatementNode> getEachLoopExecute(_ISTD Ptr<iASTNode> peachLoopExecute);

			};

		}
	}
}