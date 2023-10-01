/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSTypeNode.h
 * @创建时间:2023.10.01.16:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iATSTypeNode
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

			class ICAPI iATSTypeNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

				enum class TypeNodeType
					:int
				{
					keyword,
					identifier
				};

			public:
				TypeNodeType type;
				istring value;

			public:

				iATSTypeNode();

				iATSTypeNode(TypeNodeType typeData, istring valueData);

				~iATSTypeNode();

			public:

				[[nodiscard]] TypeNodeType getType()const noexcept;
				[[nodiscard]] istring getValue()const noexcept;

				_ISTD Ptr<iATSTypeNode> setType(TypeNodeType typeData);
				_ISTD Ptr<iATSTypeNode> setValue(istring valueData);
			};

		}
	}
}