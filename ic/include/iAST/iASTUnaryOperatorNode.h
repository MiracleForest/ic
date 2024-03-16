/*
 *
 * Copyright(C) 2023 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTUnaryOperatorNode.h
 * @创建时间:2023.09.03.18:00
 * @创建者:Windows.h
 * -----------------------------------------------------------------------------
 * iASTUnaryOperatorNode
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
        class ICAPI iASTUnaryOperatorNode : public iASTNode
        {
        public:
            Ptr<iASTNode> data;

        public:
            iASTUnaryOperatorNode();

            iASTUnaryOperatorNode(Ptr<iASTNode> data);

            ~iASTUnaryOperatorNode();

        public:
            [[nodiscard]] Ptr<iASTNode> get() const noexcept;

            Ptr<iASTUnaryOperatorNode> set(Ptr<iASTNode> data);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i