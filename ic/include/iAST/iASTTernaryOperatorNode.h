/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTTernaryOperatorNode.h
 * @创建时间:2023.09.03.18:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iASTTernaryOperatorNode
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
        class ICAPI iASTTernaryOperatorNode : public iASTNode
        {
        public:
            Ptr<iASTNode> left;
            Ptr<iASTNode> middle;
            Ptr<iASTNode> right;

        public:
            iASTTernaryOperatorNode();

            iASTTernaryOperatorNode(
                Ptr<iASTNode> leftData,
                Ptr<iASTNode> middleData,
                Ptr<iASTNode> rightData
            );

            ~iASTTernaryOperatorNode();

        public:
            [[nodiscard]] Ptr<iASTNode> getLeft() const noexcept;
            [[nodiscard]] Ptr<iASTNode> getMiddle() const noexcept;
            [[nodiscard]] Ptr<iASTNode> getRight() const noexcept;

            Ptr<iASTTernaryOperatorNode> setLeft(Ptr<iASTNode> leftData);
            Ptr<iASTTernaryOperatorNode> setMiddle(Ptr<iASTNode> middleData);
            Ptr<iASTTernaryOperatorNode> setRight(Ptr<iASTNode> rightData);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i