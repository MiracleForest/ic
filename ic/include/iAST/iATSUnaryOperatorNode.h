/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSUnaryOperatorNode.h
 * @创建时间:2023.09.03.18:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iATSUnaryOperatorNode
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
			class ICAPI iATSUnaryOperatorNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				_ISTD Ptr<iASTNode> data;

			public:

				iATSUnaryOperatorNode();

				iATSUnaryOperatorNode(_ISTD Ptr<iASTNode> data);

				~iATSUnaryOperatorNode();

			public:

				[[nodiscard]] _ISTD Ptr<iASTNode> get()const noexcept;

				_ISTD Ptr<iATSUnaryOperatorNode> set(_ISTD Ptr<iASTNode> data);
			};

		}
	}
}