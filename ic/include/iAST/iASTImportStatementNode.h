/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTImportStatementNode.h
 * @创建时间:2023.10.21.17:13
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTImportStatementNode
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
			class ICAPI iASTImportStatementNode
				:public iASTNode
			{
				using istring = _ISTDTEXT istring;

			public:

				std::vector<istring> parentModuleList;
				istring importModule;
				std::vector<istring> nicknameList;

			public:

				iASTImportStatementNode();

				iASTImportStatementNode(std::vector<istring> pparentModuleList,  CRef<istring> pimportModule, std::vector<istring> pnicknameList);

				~iASTImportStatementNode();

			public:

				 Ptr<iASTImportStatementNode> addNickname( CRef<istring> nickname);

				/*
				* @warning vector<istring>的顺序代表着各级模块的所属关系
				*/
				 Ptr<iASTImportStatementNode> pushBackParentModule( CRef<istring> parentModule);

				[[nodiscard]] istring getImportModule()const noexcept;
				[[nodiscard]] std::vector<istring> getParentModuleList()const noexcept;
				[[nodiscard]] std::vector<istring> getNicknameList()const noexcept;

				 Ptr<iASTImportStatementNode> setParentModuleList(std::vector<istring> pparentModuleList);
				 Ptr<iASTImportStatementNode> setImportModule(CRef<istring> pimportModule);
				 Ptr<iASTImportStatementNode> setNicknameList(std::vector<istring> pnicknameList);

			};

		}
	}
}