/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTReturnStatementNode.h
 * @创建时间:2023.10.21.16:41
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTReturnStatementNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iASTReturnStatementNode : public iASTNode
        {
        public:
            Ptr<iASTNode> value;

        public:
            iASTReturnStatementNode();

            iASTReturnStatementNode(Ptr<iASTNode> value);

            ~iASTReturnStatementNode();

        public:
            [[nodiscard]] Ptr<iASTNode>  getReturnValue() const noexcept;
            Ptr<iASTReturnStatementNode> setReturnValue(Ptr<iASTNode> pvalue);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i