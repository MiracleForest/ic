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
#include "iASTTypeNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class iASTImportStatementNode : public iASTNode
        {
        public:
            std::string mModule;
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i