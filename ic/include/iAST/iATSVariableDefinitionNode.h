/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSVariableDefinitionNode.h
 * @创建时间:2023.10.21.16:54
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iATSVariableDefinitionNode
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
			class ICAPI iATSVariableDefinitionNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				_ISTD Ptr<iATSTypeNode> type;
				_ISTD Ptr<iASTNode> value;

				istring name;


			public:

				iATSVariableDefinitionNode();

				iATSVariableDefinitionNode(_ISTD Ptr<iATSTypeNode> ptype, _ISTD Ptr<iASTNode> pvalue, _ISTD CRef<istring> pname);

				~iATSVariableDefinitionNode();

			public:

				[[nodiscard]] _ISTD Ptr<iATSTypeNode> getVariableType()const noexcept;
				[[nodiscard]] istring getVariableName()const noexcept;
				[[nodiscard]] _ISTD Ptr<iASTNode> getVariableValue()const noexcept;

				_ISTD Ptr<iATSVariableDefinitionNode> setVariableType(_ISTD Ptr<iATSTypeNode> ptype);
				_ISTD Ptr<iATSVariableDefinitionNode> setVariableName(_ISTD CRef<istring> pname);
				_ISTD Ptr<iATSVariableDefinitionNode> setVariableValue(_ISTD Ptr<iASTNode> pvalue);

			};

		}
	}
}