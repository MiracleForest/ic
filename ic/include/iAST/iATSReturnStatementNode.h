/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iATSReturnStatementNode.h
 * @创建时间:2023.10.21.16:41
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iATSReturnStatementNode
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
        class ICAPI iATSReturnStatementNode : public iASTNode
        {
        public:
            Ptr<iASTNode> value;

        public:
            iATSReturnStatementNode();

            iATSReturnStatementNode(Ptr<iASTNode> value);

            ~iATSReturnStatementNode();

        public:
            [[nodiscard]] Ptr<iASTNode>  getReturnValue() const noexcept;
            Ptr<iATSReturnStatementNode> setReturnValue(Ptr<iASTNode> pvalue);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i