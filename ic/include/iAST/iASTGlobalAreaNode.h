/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iParser.h
 * @创建时间:2022.7.1.22:26
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTGlobalAreaNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iASTStringLiteralNode.h"
#include "iATSFloatingLiteralNode.h"
#include "iATSIntegerLiteralNode.h"
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
			class ICAPI iASTGlobalAreaNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;
			private:

				mutable int _childElementsListIndex;

			public:

				std::vector<_ISTD Ptr<iASTNode>> childElementsList;

			public:

				iASTGlobalAreaNode();

				iASTGlobalAreaNode(_ISTD Ptr<iASTNode> childElements);

				iASTGlobalAreaNode(std::vector<_ISTD Ptr<iASTNode>> childElementsList);

				~iASTGlobalAreaNode();

			public:

			public:

				int getCount()const;

				_ISTD Ptr<iASTGlobalAreaNode> setIndex(int index);

				int getIndex()const;

				_ISTD Ptr<iASTGlobalAreaNode> next()const;

				_ISTD Ptr<iASTNode> getNext()const;

				_ISTD Ptr<iASTNode> get()const;

				_ISTD Ptr<iASTGlobalAreaNode> setNext(_ISTD Ptr<iASTNode> node);

				_ISTD Ptr<iASTGlobalAreaNode> set(_ISTD Ptr<iASTNode> node);

				_ISTD Ptr<iASTGlobalAreaNode> add(_ISTD Ptr<iASTNode> node);

				_ISTD Ptr<iASTGlobalAreaNode> remove();

			};

		}
	}
}