/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSTernaryOperatorNode.h
 * @创建时间:2023.09.03.18:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iATSTernaryOperatorNode
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
#include "iASTNode.h"
#include "../family/iicfamily.h"

SPACE(i)
{
	SPACE(icSystem)
	{
		SPACE(AST)
		{
			class ICAPI iATSTernaryOperatorNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				_ISTD Ptr<iASTNode> left;
				_ISTD Ptr<iASTNode> middle;
				_ISTD Ptr<iASTNode> right;

			public:

				iATSTernaryOperatorNode();

				iATSTernaryOperatorNode(_ISTD Ptr<iASTNode> leftData, _ISTD Ptr<iASTNode> middleData, _ISTD Ptr<iASTNode> rightData);

				~iATSTernaryOperatorNode();

			public:

				[[nodiscard]] _ISTD Ptr<iASTNode> getLeft()const noexcept;
				[[nodiscard]] _ISTD Ptr<iASTNode> getMiddle()const noexcept;
				[[nodiscard]] _ISTD Ptr<iASTNode> getRight()const noexcept;

				_ISTD Ptr<iATSTernaryOperatorNode> setLeft(_ISTD Ptr<iASTNode> leftData);
				_ISTD Ptr<iATSTernaryOperatorNode> setMiddle(_ISTD Ptr<iASTNode> middleData);
				_ISTD Ptr<iATSTernaryOperatorNode> setRight(_ISTD Ptr<iASTNode> rightData);
			};

		}
	}
}