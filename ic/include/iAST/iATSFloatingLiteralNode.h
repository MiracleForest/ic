/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSFloatingLiteralNode.h
 * @创建时间:2022.7.21.17:42
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iATSFloatingLiteralNode
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
			class ICAPI iATSFloatingLiteralNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				double data;

			public:

				iATSFloatingLiteralNode();

				iATSFloatingLiteralNode(double data);

				~iATSFloatingLiteralNode();

			public:

				[[nodiscard]] double get()const noexcept;

				_ISTD Ptr<iATSFloatingLiteralNode> set(double data);

			};

		}
	}
}