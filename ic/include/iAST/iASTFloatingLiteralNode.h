/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTFloatingLiteralNode.h
 * @创建时间:2022.7.21.17:42
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTFloatingLiteralNode
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
        class ICAPI iASTFloatingLiteralNode : public iASTNode
        {
        public:
            double data;

        public:
            iASTFloatingLiteralNode();

            iASTFloatingLiteralNode(double data);

            ~iASTFloatingLiteralNode();

        public:
            [[nodiscard]] double get() const noexcept;

            Ptr<iASTFloatingLiteralNode> set(double data);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i