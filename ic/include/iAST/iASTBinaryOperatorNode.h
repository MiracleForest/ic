/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTBinaryOperatorNode.h
 * @创建时间:2023.09.03.18:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iASTBinaryOperatorNode
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
        class ICAPI iASTBinaryOperatorNode : public iASTNode
        {
        public:
            Ptr<iASTNode> left;
            Ptr<iASTNode> right;

        public:
            iASTBinaryOperatorNode();

            iASTBinaryOperatorNode(Ptr<iASTNode> leftData, Ptr<iASTNode> rightData);

            ~iASTBinaryOperatorNode();

        public:
            [[nodiscard]] Ptr<iASTNode> getLeft() const noexcept;
            [[nodiscard]] Ptr<iASTNode> getRight() const noexcept;

            Ptr<iASTBinaryOperatorNode> setLeft(Ptr<iASTNode> leftData);
            Ptr<iASTBinaryOperatorNode> setRight(Ptr<iASTNode> rightData);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i