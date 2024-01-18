/*
 *
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名:iASTStringLiteralNode.h
 * @创建时间:2022.7.21.17:42
 * @创建者:Lovelylavender4
 * -----------------------------------------------------------------------------
 * iASTStringLiteralNode
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
        class ICAPI iASTStringLiteralNode : public iASTNode
        {
        public:
            std::string data;

        public:
            iASTStringLiteralNode();

            iASTStringLiteralNode(std::string data);

            ~iASTStringLiteralNode();

        public:
            [[nodiscard]] std::string get() const noexcept;

            Ptr<iASTStringLiteralNode> set(CRef<std::string> data);
        };
    } // namespace AST
} // namespace icFamily
} // namespace MiracleForest::inline i