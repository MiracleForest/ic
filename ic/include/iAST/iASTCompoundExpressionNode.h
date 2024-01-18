/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTCompoundExpressionNode.h
 * @创建时间:2023.10.21.19:32
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTCompoundExpressionNode
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 */
#pragma once

#include "../family/iicfamily.h"
#include "iASTNode.h"
#include "iATSTypeNode.h"

namespace MiracleForest::inline i
{
namespace icFamily
{
    namespace AST
    {
        class ICAPI iASTCompoundExpressionNode : public iASTNode
        {
        public:
            Ptr<iASTNode> expression;

        public:
            iASTCompoundExpressionNode();

            iASTCompoundExpressionNode(Ptr<iASTNode> pexpression);

            ~iASTCompoundExpressionNode();

        public:
            [[nodiscard]] Ptr<iASTNode> getExpression() const noexcept;

            Ptr<iASTCompoundExpressionNode> setExpression(Ptr<iASTNode> pexpression);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i