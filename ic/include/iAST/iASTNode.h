/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iParser.h
 * @创建时间:2022.7.1.22:26
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once


#include <icore/family/imacrofamily.h>
#include <icore/exception/error.h>
#include <icore/data/text/istring.h>
#include "../family/iicfamily.h"
#include "iASTNodeBasic.h"

SPACE(i)
{
	SPACE(icSystem)
	{
		SPACE(AST)
		{
			enum class iASTNodeType
				:int
			{
				iASTNode,
				iASTGlobalAreaNode,
				iASTStringLiteralNode,
				iATSFloatingLiteralNode,
				iATSIntegerLiteralNode,
				iATSBinaryOperatorNode,
				iATSTernaryOperatorNode,
				iATSUnaryOperatorNode
			};


			class ICAPI iASTNode
				:public iASTNodeBasic
			{
				using istring = _ISTDTEXT istring;
			public:

				_ISTD Ptr<iASTNode> parent;

				iASTNodeType type;

				istring name;

				int line;

				bool additionalNode;

				std::vector<istring> tags;

			private:
			public:

				virtual _CSETVF2(iASTNode, _ISTD Ptr<iASTNode>, Parent, parent);

				virtual _CSETVF2(iASTNode, _ISTD Ptr<iASTNode>, Name, name);

				virtual _ISTD Ptr<iASTNode> setAdditionalNode()
				{
					additionalNode = true;
					return this;
				}

			public:

			public:
				virtual _ISTD Ptr<iASTNode> addTag(_ISTD CRef<istring> tag);

				virtual bool hasTag(_ISTD CRef<istring> tag)const;

				virtual int getTagIndex(_ISTD CRef<istring> tag)const;

				virtual bool removeTag(_ISTD CRef<istring> tag);

				virtual std::vector<istring> getAllTag()const;

			public:

				iASTNode();

				iASTNode(
					_ISTD Ptr<iASTNode> parent,
					iASTNodeType type,
					_ISTD CRef<istring>name,
					int line,
					bool additionalNode,
					std::vector<istring> tags
				);

				virtual ~iASTNode();

			};

		}
	}
}